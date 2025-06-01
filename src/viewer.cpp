#include "viewer.h"

#include <iostream>
#include <glm/glm.hpp>
#include "glm/ext.hpp"
#include <glm/gtc/matrix_transform.hpp>

/// Constructeur : initialise GLFW, crée la fenêtre et configure OpenGL
Viewer::Viewer(int width, int height)
{
    // Initialisation de GLFW (gestionnaire de fenêtres et contexte OpenGL)
    if (!glfwInit())
    {
        std::cerr << "Échec de l'initialisation de GLFW" << std::endl;
        glfwTerminate();
    }

    // Configuration des hints GLFW pour créer un contexte OpenGL 3.3 Core Profile
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);  // fenêtre non redimensionnable

    // Création de la fenêtre
    win = glfwCreateWindow(width, height, "Viewer", NULL, NULL);
    if (win == NULL) {
        std::cerr << "Échec de la création de la fenêtre" << std::endl;
        glfwTerminate();
    }

    // Rendre le contexte OpenGL courant pour cette fenêtre
    glfwMakeContextCurrent(win);

    // Initialisation de GLEW (gestionnaire des extensions OpenGL)
    if (glewInit() != GLEW_OK)
    {
        std::cerr << "Échec de l'initialisation de GLEW" << std::endl;
        glfwTerminate();
    }

    // Associer l'instance Viewer à la fenêtre GLFW pour accéder aux callbacks
    glfwSetWindowUserPointer(win, this);

    // Enregistrement des callbacks d'événements (clavier, souris)
    glfwSetKeyCallback(win, key_callback_static);
    glfwSetCursorPosCallback(win, cursor_position_callback_static);

    // Masquer le curseur pour contrôle de caméra style FPS
    glfwSetInputMode(win, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // Afficher des informations sur le contexte OpenGL
    std::cout << glGetString(GL_VERSION) << ", GLSL "
        << glGetString(GL_SHADING_LANGUAGE_VERSION) << ", Renderer "
        << glGetString(GL_RENDERER) << std::endl;

    // Configuration initiale de OpenGL
    glClearColor(0.1f, 0.1f, 0.1f, 0.1f);  // couleur de fond
    glEnable(GL_DEPTH_TEST);                // activation du test de profondeur
    glDepthFunc(GL_LESS);                   // mode de test de profondeur

    // Initialisation de la scène racine (node de la scène)
    scene_root = new Node();

    // Initialisation des variables liées à la souris
    firstMouse = true;
    yaw = -90.0f;  
    pitch = 0.0f;

    // Initialisation position caméra
    camera_pos = glm::vec3(7.0f, -2.0f, 19.0f);
    camera_up = glm::vec3(0.0f, 1.0f, 0.0f);
    camera_front = glm::vec3(0.0f, 0.0f, -1.0f);

    // Initialiser état des touches
    std::fill(std::begin(keys), std::end(keys), false);


}

/// Callback statique appelé par GLFW quand la souris bouge
void Viewer::cursor_position_callback_static(GLFWwindow* window, double xpos, double ypos)
{
    // Récupération de l'instance Viewer associée à la fenêtre
    Viewer* viewer = static_cast<Viewer*>(glfwGetWindowUserPointer(window));
    viewer->on_mouse_move(xpos, ypos);
}

/// Gestion du mouvement de la souris (mise à jour des angles yaw et pitch)
void Viewer::on_mouse_move(double xpos, double ypos)
{
    if (firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float sensitivity = 0.1f;  // sensibilité de la souris
    float xoffset = (xpos - lastX) * sensitivity;
    float yoffset = (lastY - ypos) * sensitivity; // y inversé car l'axe y va vers le bas dans la fenêtre

    lastX = xpos;
    lastY = ypos;

    yaw += xoffset;
    pitch += yoffset;

    // Limitation de l'angle pitch pour éviter le retournement
    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;
}

/// Boucle principale de rendu
void Viewer::run()
{
    float start_time = 0.0f;  // temps initial 

    // Tant que la fenêtre n'est pas fermée
    while (!glfwWindowShouldClose(win))
    {
        // Effacer le buffer couleur et profondeur
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Matrice modèle identité (pas de transformation pour l'instant)
        glm::mat4 model = glm::mat4(1.0f);

        process_input();

        // Calcul de la direction de la caméra selon yaw et pitch
        glm::vec3 direction;
        direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        direction.y = sin(glm::radians(pitch));
        direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
        camera_front = glm::normalize(direction);


         
        camera_up = glm::vec3(0.0f, 1.0f, 0.0f);
        glm::mat4 view = glm::lookAt(camera_pos, camera_pos + camera_front, camera_up);

        // Projection perspective avec champ de vision 45°, ratio 1, plans proche et lointain
        glm::mat4 projection = glm::perspective(glm::radians(45.0f), 1.0f, 0.1f, 50.0f);

        animated_nodes[0]->setTransform(glm::translate(glm::mat4(1.0f), glm::vec3(-9.0f, -2.0f, 9.0f))
        *glm::rotate(glm::mat4(1.0f), glm::radians((start_time/4)*90.0f), glm::vec3(0.0f, 1.0f, 0.0f))
        *glm::scale(glm::mat4(1.0f), glm::vec3(2.0f, 2.0f, 2.0f)));

        // Incrémenter le temps 
        start_time += 0.01f;

        // Dessiner la scène à partir de la racine
        scene_root->draw(model, view, projection);

        // Gestion des événements (clavier, souris, etc.)
        glfwPollEvents();

        // Échange des buffers pour afficher la nouvelle image
        glfwSwapBuffers(win);
    }

    // Fermeture et nettoyage de GLFW
    glfwTerminate();
}

void Viewer::key_callback_static(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    Viewer* viewer = static_cast<Viewer*>(glfwGetWindowUserPointer(window));

    if (key >= 0 && key < 1024)
    {
        if (action == GLFW_PRESS)
            viewer->keys[key] = true;
        else if (action == GLFW_RELEASE)
            viewer->keys[key] = false;
    }

    // Fermeture avec Échap ou Q
    if (key == GLFW_KEY_ESCAPE || key == GLFW_KEY_Q)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

void Viewer::process_input()
{
    glm::vec3 right = glm::normalize(glm::cross(camera_front, camera_up));
    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);

    // Vecteur front horizontal : on ignore l'altitude (y)
    glm::vec3 horizontal_front = glm::normalize(glm::vec3(camera_front.x, 0.0f, camera_front.z));

    // Avancer/reculer (Z/W et S ou Flèches Haut/Bas) – sur le plan horizontal uniquement
    if (keys[GLFW_KEY_W] || keys[GLFW_KEY_Z] || keys[GLFW_KEY_UP])
        camera_pos += camera_speed * horizontal_front;
    if (keys[GLFW_KEY_S] || keys[GLFW_KEY_DOWN])
        camera_pos -= camera_speed * horizontal_front;

    // Gauche/droite (Q/A et D ou Flèches)
    if (keys[GLFW_KEY_A] || keys[GLFW_KEY_Q] || keys[GLFW_KEY_LEFT])
        camera_pos -= right * camera_speed;
    if (keys[GLFW_KEY_D] || keys[GLFW_KEY_RIGHT])
        camera_pos += right * camera_speed;

    // Monter / descendre (espace / shift)
    if (keys[GLFW_KEY_SPACE])
        camera_pos += camera_speed * up;
    if (keys[GLFW_KEY_LEFT_SHIFT])
        camera_pos -= camera_speed * up;
}


void Viewer::on_key(int key)
{
    if (key == GLFW_KEY_ESCAPE)
    {
        glfwSetWindowShouldClose(win, GLFW_TRUE);
    }

  
}