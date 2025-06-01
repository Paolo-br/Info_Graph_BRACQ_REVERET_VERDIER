#ifndef PYRAMID_H
#define PYRAMID_H

#include "shape.h"
#include "shader.h"
#include <GL/glew.h>

class Pyramid : public Shape {
public:
    Pyramid(Shader* shader_program, float base_size, float height);
    virtual ~Pyramid();

    virtual void draw(glm::mat4& model, glm::mat4& view, glm::mat4& projection);
    void key_handler(int key);

protected:
    GLuint VAO;
    GLuint VBO[4];  // 0: positions, 1: normals, 2: texcoords, 3: indices
    unsigned int num_indices;

    float base_size;
    float height;
};

#endif
