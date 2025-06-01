#include "prism.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>

#include "prism.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>

/// Constructeur du prisme
Prism::Prism(Shader* shader_program, float size_x, float size_y, float size_z)
    : Shape(shader_program) // Appelle le constructeur de la classe de base
{
    // Vecteurs contenant les données géométriques
    std::vector<glm::vec3> vertices;    // Sommets
    std::vector<glm::vec3> normals;     // Normales pour l’éclairage
    std::vector<glm::vec2> texCoords;   // Coordonnées de texture
    std::vector<unsigned int> indices; // Indices pour les triangles

    // Centre géométrique à (0, 0, 0)
     // On recentre la base du prisme autour de l’origine
    float half_x = size_x / 2.0f;
    float half_y = size_y / 2.0f;
    float half_z = size_z / 2.0f;

    // Points de la base (triangle sur XZ)
    glm::vec3 p0(-half_x, -half_y, -half_z);           // bas gauche
    glm::vec3 p1(half_x, -half_y, -half_z);            // bas droite
    glm::vec3 p2(0.0f, -half_y, half_z);               // sommet avant


    glm::vec3 p3 = p0 + glm::vec3(0.0f, size_y, 0.0f);       // Haut de p0
    glm::vec3 p4 = p1 + glm::vec3(0.0f, size_y, 0.0f);       // Haut de p1
    glm::vec3 p5 = p2 + glm::vec3(0.0f, size_y, 0.0f);       // Haut de p2

    // Fonction lambda pour ajouter une face triangulaire
    auto add_face = [&](glm::vec3 a, glm::vec3 b, glm::vec3 c, glm::vec3 normal) {
        unsigned int start = vertices.size(); // Indice de départ
        // Ajout des sommets, normales et coordonnées UV
        vertices.push_back(a); normals.push_back(normal); texCoords.emplace_back(0.0f, 0.0f);
        vertices.push_back(b); normals.push_back(normal); texCoords.emplace_back(1.0f, 0.0f);
        vertices.push_back(c); normals.push_back(normal); texCoords.emplace_back(0.5f, 1.0f);
        // Ajout des indices
        indices.push_back(start);
        indices.push_back(start + 1);
        indices.push_back(start + 2);
        };

    // Fonction lambda pour ajouter une face rectangulaire (deux triangles)
    auto add_rect_face = [&](glm::vec3 a, glm::vec3 b, glm::vec3 c, glm::vec3 d, glm::vec3 normal) {
        unsigned int start = vertices.size();
        // Ajout des 4 coins avec les coordonnées de texture
        vertices.push_back(a); normals.push_back(normal); texCoords.emplace_back(0.0f, 0.0f);
        vertices.push_back(b); normals.push_back(normal); texCoords.emplace_back(1.0f, 0.0f);
        vertices.push_back(c); normals.push_back(normal); texCoords.emplace_back(1.0f, 1.0f);
        vertices.push_back(d); normals.push_back(normal); texCoords.emplace_back(0.0f, 1.0f);
        // Deux triangles
        indices.push_back(start);
        indices.push_back(start + 1);
        indices.push_back(start + 2);
        indices.push_back(start);
        indices.push_back(start + 2);
        indices.push_back(start + 3);
        };

    // ---------- Ajout des faces du prisme ----------

    // Face inférieure (base triangle)
    add_face(p0, p1, p2, glm::vec3(0.0f, -1.0f, 0.0f));

    // Face supérieure (triangle inversé)
    add_face(p3, p5, p4, glm::vec3(0.0f, 1.0f, 0.0f));

    // Face latérale 1 (entre p0/p1/p4/p3)
    glm::vec3 n1 = glm::normalize(glm::cross(p4 - p1, p0 - p1)); // Normale calculée dynamiquement
    add_rect_face(p0, p1, p4, p3, n1);

    // Face latérale 2 (entre p1/p2/p5/p4)
    glm::vec3 n2 = glm::normalize(glm::cross(p5 - p2, p1 - p2));
    add_rect_face(p1, p2, p5, p4, n2);

    // Face latérale 3 (entre p2/p0/p3/p5)
    glm::vec3 n3 = glm::normalize(glm::cross(p3 - p0, p2 - p0));
    add_rect_face(p2, p0, p3, p5, n3);

    // ---------- OpenGL : Création des buffers ----------

    glGenVertexArrays(1, &VAO);       // VAO = Vertex Array Object
    glBindVertexArray(VAO);           // On le rend actif

    glGenBuffers(4, VBO);             // 4 VBOs : positions, normales, texCoords, indices

    // VBO 0 : positions des sommets
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), vertices.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    // VBO 1 : normales
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
    glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3), normals.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    // VBO 2 : coordonnées de texture
    glEnableVertexAttribArray(2);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[2]);
    glBufferData(GL_ARRAY_BUFFER, texCoords.size() * sizeof(glm::vec2), texCoords.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

    // VBO 3 : indices
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VBO[3]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

    // Stockage du nombre d’indices à dessiner
    num_indices = static_cast<unsigned int>(indices.size());
}



void Prism::draw(glm::mat4& model, glm::mat4& view, glm::mat4& projection)
{
    glUseProgram(this->shader_program_);

    glBindVertexArray(VAO);

    Shape::draw(model, view, projection);

    glDrawElements(GL_TRIANGLES, num_indices, GL_UNSIGNED_INT, nullptr);
}

Prism::~Prism()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(4, VBO);
}

void Prism::key_handler(int key)
{
    return;
}
