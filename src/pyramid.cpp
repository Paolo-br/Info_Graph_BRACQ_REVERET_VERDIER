#include "pyramid.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>

Pyramid::Pyramid(Shader* shader_program, float base_size, float height)
    : Shape(shader_program), base_size(base_size), height(height)
{
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec3> normals;
    std::vector<glm::vec2> texCoords;
    std::vector<unsigned int> indices;

    float half = base_size / 2.0f;

    // Points de la base
    glm::vec3 p0(-half, 0.0f, -half);
    glm::vec3 p1(half, 0.0f, -half);
    glm::vec3 p2(half, 0.0f, half);
    glm::vec3 p3(-half, 0.0f, half);
    glm::vec3 top(0.0f, height, 0.0f);

    auto add_face = [&](glm::vec3 a, glm::vec3 b, glm::vec3 c, glm::vec3 normal) {
        unsigned int start = vertices.size();
        vertices.push_back(a); normals.push_back(normal); texCoords.emplace_back(0.0f, 0.0f);
        vertices.push_back(b); normals.push_back(normal); texCoords.emplace_back(1.0f, 0.0f);
        vertices.push_back(c); normals.push_back(normal); texCoords.emplace_back(0.5f, 1.0f);
        indices.push_back(start);
        indices.push_back(start + 1);
        indices.push_back(start + 2);
        };

    auto add_base = [&](glm::vec3 a, glm::vec3 b, glm::vec3 c, glm::vec3 d) {
        unsigned int start = vertices.size();
        glm::vec3 normal(0.0f, -1.0f, 0.0f);
        vertices.push_back(a); normals.push_back(normal); texCoords.emplace_back(0.0f, 0.0f);
        vertices.push_back(b); normals.push_back(normal); texCoords.emplace_back(1.0f, 0.0f);
        vertices.push_back(c); normals.push_back(normal); texCoords.emplace_back(1.0f, 1.0f);
        vertices.push_back(d); normals.push_back(normal); texCoords.emplace_back(0.0f, 1.0f);
        indices.push_back(start);
        indices.push_back(start + 1);
        indices.push_back(start + 2);
        indices.push_back(start);
        indices.push_back(start + 2);
        indices.push_back(start + 3);
        };

    // Base
    add_base(p0, p1, p2, p3);

    // Faces
    add_face(p0, p1, top, glm::normalize(glm::cross(top - p1, p0 - p1)));
    add_face(p1, p2, top, glm::normalize(glm::cross(top - p2, p1 - p2)));
    add_face(p2, p3, top, glm::normalize(glm::cross(top - p3, p2 - p3)));
    add_face(p3, p0, top, glm::normalize(glm::cross(top - p0, p3 - p0)));

    // OpenGL
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    glGenBuffers(4, VBO);

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), vertices.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
    glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3), normals.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    glEnableVertexAttribArray(2);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[2]);
    glBufferData(GL_ARRAY_BUFFER, texCoords.size() * sizeof(glm::vec2), texCoords.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VBO[3]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

    num_indices = static_cast<unsigned int>(indices.size());
}

void Pyramid::draw(glm::mat4& model, glm::mat4& view, glm::mat4& projection) {
    glUseProgram(this->shader_program_);
    glBindVertexArray(VAO);
    Shape::draw(model, view, projection);
    glDrawElements(GL_TRIANGLES, num_indices, GL_UNSIGNED_INT, nullptr);
}

Pyramid::~Pyramid() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(4, VBO);
}

void Pyramid::key_handler(int key) { return; }
