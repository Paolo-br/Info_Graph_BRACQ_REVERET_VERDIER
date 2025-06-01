#pragma once

#include "shape.h"
#include "shader.h"
#include <vector>
#include <glm/glm.hpp>

class Sphere : public Shape {
public:
    Sphere(Shader* shader_program_, float radius, int sector_count, int stack_count );

    virtual void draw(glm::mat4& model, glm::mat4& view, glm::mat4& projection);

    void key_handler(int key);

protected:
    void buildVertices();
    void buildIndices();

    std::vector<glm::vec3> vertices;
    std::vector<glm::vec3> normals;
    std::vector<glm::vec2> texCoords;
    std::vector<unsigned int> indices;

    float radius;
    int sector_count;
    int stack_count;

    unsigned int num_indices;

    GLuint VAO;
    GLuint buffers[3];
};
