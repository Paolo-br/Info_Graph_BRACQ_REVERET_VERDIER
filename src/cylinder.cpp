#include "cylinder.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

Cylinder::Cylinder(Shader* shader_program, float height, float radius, int slices)
    : Shape(shader_program)
{
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec3> normals;
    std::vector<glm::vec2> texCoords;
    std::vector<unsigned int> indices;

    float halfHeight = height / 2.0f;
    float sectorStep = 2.0f * glm::pi<float>() / slices;
    float textureRepeat = height / radius; // contrôle combien de fois la texture est répétée sur la hauteur

    // === Side vertices ===
    for (int i = 0; i <= slices; ++i) {
        float theta = i * sectorStep;
        float x = radius * cos(theta);
        float y = radius * sin(theta);
        glm::vec3 normal = glm::normalize(glm::vec3(x, y, 0.0f));
        float u = static_cast<float>(i) / slices;

        // top vertex
        vertices.push_back(glm::vec3(x, y, +halfHeight));
        normals.push_back(normal);
        texCoords.push_back(glm::vec2(u, 1.0f));

        // bottom vertex
        vertices.push_back(glm::vec3(x, y, -halfHeight));
        normals.push_back(normal);
        texCoords.push_back(glm::vec2(u, 0.0f));
    }

    // === Side indices ===
    for (int i = 0; i < slices; ++i) {
        int k = i * 2;
        indices.push_back(k);
        indices.push_back(k + 1);
        indices.push_back(k + 2);

        indices.push_back(k + 1);
        indices.push_back(k + 3);
        indices.push_back(k + 2);
    }

    // === Top and bottom center points ===
    int topCenterIndex = vertices.size();
    vertices.push_back(glm::vec3(0.0f, 0.0f, +halfHeight));
    normals.push_back(glm::vec3(0.0f, 0.0f, 1.0f));
    texCoords.push_back(glm::vec2(0.5f, 0.5f)); // neutre pour les disques

    int bottomCenterIndex = vertices.size();
    vertices.push_back(glm::vec3(0.0f, 0.0f, -halfHeight));
    normals.push_back(glm::vec3(0.0f, 0.0f, -1.0f));
    texCoords.push_back(glm::vec2(0.5f, 0.5f));

    // === Top/bottom disk triangles ===
    for (int i = 0; i < slices; ++i) {
        int next = (i + 1) % (slices + 1);
        int top = i * 2;
        int bottom = i * 2 + 1;

        // top face
        indices.push_back(top);
        indices.push_back(next * 2);
        indices.push_back(topCenterIndex);

        // bottom face
        indices.push_back(bottomCenterIndex);
        indices.push_back(next * 2 + 1);
        indices.push_back(bottom);
    }

    // === OpenGL buffer setup ===
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    glGenBuffers(4, &buffers[0]);

    // Positions
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), vertices.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    // Normals
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, buffers[1]);
    glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3), normals.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    // Texture Coords
    glEnableVertexAttribArray(2);
    glBindBuffer(GL_ARRAY_BUFFER, buffers[2]);
    glBufferData(GL_ARRAY_BUFFER, texCoords.size() * sizeof(glm::vec2), texCoords.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

    // Indices
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[3]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

    num_indices = static_cast<unsigned int>(indices.size());
}

void Cylinder::draw(glm::mat4& model, glm::mat4& view, glm::mat4& projection)
{
    glUseProgram(this->shader_program_);

    glBindVertexArray(VAO);

    Shape::draw(model, view, projection);

    glDrawElements(GL_TRIANGLES, num_indices, GL_UNSIGNED_INT, nullptr);
}
