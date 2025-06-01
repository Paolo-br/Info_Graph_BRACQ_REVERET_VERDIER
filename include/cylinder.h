#pragma once

#include "shape.h"
#include <vector>

class Cylinder : public Shape {
public:
    Cylinder(Shader *shader_program, float height, float radius, int slices);
    void draw(glm::mat4& model, glm::mat4& view, glm::mat4& projection);

private:
    unsigned int num_indices;
    GLuint VAO;
    GLuint buffers[2];
};
