#ifndef PRISM_H
#define PRISM_H

#include "shape.h"
#include "shader.h"
#include <GL/glew.h>

class Prism : public Shape {
public:
    Prism(Shader* shader_program, float size_x, float size_y, float size_z);

    void draw(glm::mat4& model, glm::mat4& view, glm::mat4& projection) override;
    void key_handler(int key);

    virtual ~Prism();

protected:
    GLuint VAO;
    GLuint VBO[4]; // position, normal, texCoord, indices
    unsigned int num_indices;
    
    std::vector<unsigned int> face_counts;   
    std::vector<unsigned int> face_offsets;
};

#endif
