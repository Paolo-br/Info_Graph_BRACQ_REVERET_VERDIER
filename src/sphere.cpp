#include "sphere.h"
#include <GL/glew.h>
#include <cmath>

// Définition de PI si non défini
#define M_PI 3.1415

// Constructeur de la sphère
Sphere::Sphere(Shader* shader_program_, float radius, int sector_count, int stack_count) :
    Shape(shader_program_), radius(radius), sector_count(sector_count), stack_count(stack_count)
{
    // Construction de la géométrie (sommets, normales, textures)
    buildVertices();
    buildIndices();

    // Création du Vertex Array Object
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // Génération des Vertex Buffer Objects (positions, normales, UV, indices)
    glGenBuffers(4, &buffers[0]);

    // Attribut 0 : position des sommets
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    // Attribut 1 : normales pour l’éclairage
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, buffers[1]);
    glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3), &normals[0], GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    // Attribut 2 : coordonnées de texture
    glEnableVertexAttribArray(2);
    glBindBuffer(GL_ARRAY_BUFFER, buffers[2]);
    glBufferData(GL_ARRAY_BUFFER, texCoords.size() * sizeof(glm::vec2), texCoords.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

    // Buffer d’indices pour le dessin par glDrawElements
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[3]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

    // Nombre total d’indices pour le dessin
    num_indices = static_cast<unsigned int>(indices.size());
}

// Méthode de dessin de la sphère
void Sphere::draw(glm::mat4& model, glm::mat4& view, glm::mat4& projection)
{
    glUseProgram(this->shader_program_);      // Utilisation du shader
    glBindVertexArray(VAO);                   // Activation du VAO
    Shape::draw(model, view, projection);     // Transformation et uniformes
    glDrawElements(GL_TRIANGLES, num_indices, GL_UNSIGNED_INT, nullptr); // Dessin de la sphère
}

// Génère les sommets, normales et coordonnées UV de la sphère
void Sphere::buildVertices()
{
    // Nettoyage des anciens vecteurs
    vertices.clear();
    normals.clear();
    texCoords.clear();

    float x = 0.0f, y = 0.0f, z = 0.0f, s, t;

    // Pas angulaire entre secteurs (longitude) et stacks (latitude)
    float sector_step = 2.0f * M_PI / sector_count;
    float stack_step = M_PI / stack_count;

    // Boucle sur chaque stack (de haut en bas)
    for (int i = 0; i <= stack_count; i++) {
        float stack_angle = M_PI / 2.0f - i * stack_step; // Angle de latitude
        float xy = radius * std::cos(stack_angle);        // Rayon horizontal (cercle courant)
        z = radius * std::sin(stack_angle);               // Hauteur actuelle

        // Boucle sur chaque secteur (autour de la sphère)
        for (int j = 0; j <= sector_count; j++) {
            float sector_angle = j * sector_step;         // Angle de longitude
            x = xy * std::cos(sector_angle);
            y = xy * std::sin(sector_angle);

            glm::vec3 vertex(x, y, z);                    // Coordonnée 3D du point
            glm::vec3 normal = glm::normalize(vertex);    // Normale : vecteur unitaire depuis centre
            vertices.push_back(vertex);                   // Ajout du sommet
            normals.push_back(normal);                    // Ajout de la normale

            // Coordonnées de texture (s = longitude, t = latitude)
            s = (float)j / sector_count;
            t = (float)i / stack_count;
            texCoords.push_back(glm::vec2(s, t));
        }
    }
}

// Génère les indices pour relier les sommets en triangles
void Sphere::buildIndices()
{
    indices.clear();
    int k1, k2;

    // Parcours de chaque stack
    for (int i = 0; i < stack_count; i++) {
        k1 = i * (sector_count + 1);         // Début de la stack courante
        k2 = k1 + sector_count + 1;          // Début de la stack suivante

        // Parcours des secteurs de la stack
        for (int j = 0; j < sector_count; j++, k1++, k2++) {
            // Triangle supérieur (sauf sur le pôle nord)
            if (i != 0) {
                indices.push_back(k1);
                indices.push_back(k2);
                indices.push_back(k1 + 1);
            }

            // Triangle inférieur (sauf sur le pôle sud)
            if (i != (stack_count - 1)) {
                indices.push_back(k1 + 1);
                indices.push_back(k2);
                indices.push_back(k2 + 1);
            }
        }
    }
}

// Méthode vide pour gestion d'entrées clavier 
void Sphere::key_handler(int key) {
    return;
}
