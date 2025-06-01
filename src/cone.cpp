#include "cone.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/constants.hpp>
#include <vector>
#include <cmath>

// Constructeur du cône
Cone::Cone(Shader* shader_program, float height, float top_radius, float bottom_radius, int slices, bool inside, bool outside)
    : Shape(shader_program) // Appel au constructeur de la classe de base Shape
{
    // Vecteurs pour stocker les données de géométrie
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec3> normals;
    std::vector<glm::vec2> texCoords;
    std::vector<unsigned int> indices;

    float halfHeight = height / 2.0f; // Moitié de la hauteur du cône
    float sectorStep = 2.0f * glm::pi<float>() / slices; // Angle entre deux tranches (en radians)

    float zTop = +halfHeight;   // Position en Z du sommet supérieur
    float zBottom = -halfHeight; // Position en Z de la base

    // Génération des vertex pour les côtés du cône
    for (int i = 0; i <= slices; ++i) {
        float theta = i * sectorStep;
        float cosT = cos(theta);
        float sinT = sin(theta);

        // Point sur le cercle supérieur
        glm::vec3 topVertex = glm::vec3(cosT * top_radius, sinT * top_radius, zTop);
        // Point correspondant sur le cercle inférieur
        glm::vec3 bottomVertex = glm::vec3(cosT * bottom_radius, sinT * bottom_radius, zBottom);
        // Approximation de la normale pour la surface latérale
        glm::vec3 dir = glm::normalize(glm::vec3(cosT, sinT, 0.8f));

        // Ajout des points, normales et coordonnées de texture
        vertices.push_back(topVertex);
        normals.push_back(dir);
        texCoords.push_back(glm::vec2((float)i / slices, 1.0f)); // Coordonnée haut

        vertices.push_back(bottomVertex);
        normals.push_back(dir);
        texCoords.push_back(glm::vec2((float)i / slices, 0.0f)); // Coordonnée bas
    }

    // Construction des triangles pour les faces latérales
    for (int i = 0; i < slices; ++i) {
        int top1 = i * 2;
        int bottom1 = top1 + 1;
        int top2 = top1 + 2;
        int bottom2 = top1 + 3;

        // Faces extérieures
        if (outside) {
            indices.push_back(top1);
            indices.push_back(bottom1);
            indices.push_back(top2);

            indices.push_back(bottom2);
            indices.push_back(top2);
            indices.push_back(bottom1);
        }

        // Faces intérieures (si on veut voir le cône depuis l'intérieur)
        if (inside) {
            indices.push_back(top2);
            indices.push_back(bottom1);
            indices.push_back(top1);

            indices.push_back(bottom1);
            indices.push_back(top2);
            indices.push_back(bottom2);
        }
    }

    // --- Initialisation OpenGL ---

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    glGenBuffers(4, buffers); // 4 buffers : positions, normales, texCoords, indices

    // VERTICES
    glEnableVertexAttribArray(0); // Attribut 0 = position
    glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), vertices.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    // NORMALS
    glEnableVertexAttribArray(1); // Attribut 1 = normales
    glBindBuffer(GL_ARRAY_BUFFER, buffers[1]);
    glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3), normals.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    // TEXCOORDS
    glEnableVertexAttribArray(2); // Attribut 2 = coordonnées de texture
    glBindBuffer(GL_ARRAY_BUFFER, buffers[2]);
    glBufferData(GL_ARRAY_BUFFER, texCoords.size() * sizeof(glm::vec2), texCoords.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

    // INDICES
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[3]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

    // Nombre total d’indices utilisés pour le rendu
    num_indices = static_cast<unsigned int>(indices.size());
}

// Méthode de rendu du cône
void Cone::draw(glm::mat4& model, glm::mat4& view, glm::mat4& projection)
{
    glUseProgram(this->shader_program_); // Activation du shader
    glBindVertexArray(VAO);              // Liaison du VAO
    Shape::draw(model, view, projection); // Passage des matrices uniformes
    glDrawElements(GL_TRIANGLES, num_indices, GL_UNSIGNED_INT, nullptr); // Rendu avec indices
}
