#include "shape.h"
#include <vector>

#ifndef CONE_H
#define CONE_H

class Cone : public Shape {
public:
    Cone(Shader* shader_program, float height, float top_radius, float bottom_radius, int slices, bool inside = false, bool outside = true);

    void draw(glm::mat4& model, glm::mat4& view, glm::mat4& projection) override;

private:
    GLuint VAO;
    GLuint buffers[4];
    unsigned int num_indices;
};
#endif