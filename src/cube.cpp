#include "cube.h"
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "cube.h"
#include <glm/glm.hpp>
#include <vector>

// Constructeur du cube (ou pavé)
// Paramètres : taille selon les axes x, y et z
Cube::Cube(Shader* shader_program, float size_x, float size_y, float size_z)
    : Shape(shader_program) // Appel au constructeur de Shape (classe de base)
{
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec3> normals;
    std::vector<unsigned int> indices;
    std::vector<glm::vec2> texCoords;

    // Calcul de la moitié des dimensions
    float hx = size_x / 2.0f;
    float hy = size_y / 2.0f;
    float hz = size_z / 2.0f;

    // Définition des 8 sommets du cube
    glm::vec3 p0(-hx, -hy, -hz);
    glm::vec3 p1(hx, -hy, -hz);
    glm::vec3 p2(hx, hy, -hz);
    glm::vec3 p3(-hx, hy, -hz);
    glm::vec3 p4(-hx, -hy, hz);
    glm::vec3 p5(hx, -hy, hz);
    glm::vec3 p6(hx, hy, hz);
    glm::vec3 p7(-hx, hy, hz);

    // Définition des 6 faces du cube (chacune composée de 2 triangles)
    struct Face {
        glm::vec3 v0, v1, v2, v3;  // 4 sommets de la face
        glm::vec3 normal;          // normale associée à cette face
    };

    // Chaque face est décrite dans le sens horaire pour le rendu
    std::vector<Face> faces = {
        { p0, p1, p2, p3, glm::vec3(0,  0, -1) }, // arrière
        { p5, p4, p7, p6, glm::vec3(0,  0,  1) }, // avant
        { p4, p0, p3, p7, glm::vec3(-1,  0,  0) }, // gauche
        { p1, p5, p6, p2, glm::vec3(1,  0,  0) }, // droite
        { p3, p2, p6, p7, glm::vec3(0,  1,  0) }, // haut
        { p4, p5, p1, p0, glm::vec3(0, -1,  0) }  // bas
    };

    // Création des vertex, normales, indices et coordonnées de texture
    for (int i = 0; i < faces.size(); ++i) {
        auto& face = faces[i];
        unsigned int start = vertices.size();

        // Ajout des 4 sommets avec la même normale
        vertices.push_back(face.v0); normals.push_back(face.normal);
        vertices.push_back(face.v1); normals.push_back(face.normal);
        vertices.push_back(face.v2); normals.push_back(face.normal);
        vertices.push_back(face.v3); normals.push_back(face.normal);

        // Création de deux triangles par face
        indices.push_back(start);
        indices.push_back(start + 1);
        indices.push_back(start + 2);
        indices.push_back(start);
        indices.push_back(start + 2);
        indices.push_back(start + 3);

        // Coordonnées de texture (mapping simple carré)
        texCoords.push_back(glm::vec2(0.0f, 0.0f));
        texCoords.push_back(glm::vec2(1.0f, 0.0f));
        texCoords.push_back(glm::vec2(1.0f, 1.0f));
        texCoords.push_back(glm::vec2(0.0f, 1.0f));
    }

    // --- Initialisation OpenGL ---

    glGenVertexArrays(1, &VAO); // Création du Vertex Array Object
    glBindVertexArray(VAO);     // Activation

    glGenBuffers(4, &VBO[0]);   // Génération de 4 VBO : position, normale, texCoord, indices

    // Positions (attrib location 0)
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), vertices.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    // Normales (attrib location 1)
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
    glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3), normals.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    // Coordonnées de texture (attrib location 2)
    glEnableVertexAttribArray(2);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[2]);
    glBufferData(GL_ARRAY_BUFFER, texCoords.size() * sizeof(glm::vec2), texCoords.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

    // Indices
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VBO[3]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

    // Stockage du nombre d'indices pour le rendu
    num_indices = static_cast<unsigned int>(indices.size());
}

// Fonction de dessin appelée à chaque frame
void Cube::draw(glm::mat4& model, glm::mat4& view, glm::mat4& projection)
{
    glUseProgram(this->shader_program_);   // Utilisation du shader
    glBindVertexArray(VAO);                // Activation du VAO

    Shape::draw(model, view, projection);  // Transmet les matrices au shader (via Shape)

    glDrawElements(GL_TRIANGLES, num_indices, GL_UNSIGNED_INT, nullptr); // Rendu par triangles
}

// Destructeur : libère les ressources OpenGL
Cube::~Cube() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(4, &VBO[0]);
}

// Fonction de gestion des entrées clavier (actuellement vide)
void Cube::key_handler(int key) {
    return;
}
