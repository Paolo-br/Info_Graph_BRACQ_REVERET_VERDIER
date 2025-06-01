#ifndef VIEWER_H
#define VIEWER_H

#include <vector>
#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "shader.h"
#include "node.h"
#include <glm/glm.hpp>

class Viewer {
public:
    Viewer(int width = 1280, int height = 960);
    void run();
    void on_key(int key);  // Gère les touches ponctuelles

    Node* scene_root;
    std::vector<Node*> animated_nodes;

    // Caméra
    glm::vec3 camera_pos;
    glm::vec3 camera_front;
    glm::vec3 camera_up;

    bool keys[1024];         // Suivi des touches pressées
    float camera_speed = 0.05f;

private:
    GLFWwindow* win;

    // Input callbacks
    static void key_callback_static(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void cursor_position_callback_static(GLFWwindow* window, double xpos, double ypos);
    void on_mouse_move(double xpos, double ypos);
    void process_input();  

    // Contrôle caméra via souris
    float yaw = 90.0f;       // Orientation initiale vers -Z
    float pitch = 0.0f;
    double lastX = 640.0;    // Moitié de la largeur
    double lastY = 480.0;    // Moitié de la hauteur
    bool firstMouse = true;
};

#endif // VIEWER_H
