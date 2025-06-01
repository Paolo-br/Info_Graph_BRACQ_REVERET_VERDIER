#ifndef CUBE_H
#define CUBE_H

#include "shape.h"
#include "shader.h"
#include <GL/glew.h>

class Cube : public Shape {
public:
    // Constructeur qui prend un shader et les tailles du cube
    Cube(Shader* shader_program, float size_x, float size_y, float size_z);

    // Fonction de dessin
    void draw(glm::mat4& model, glm::mat4& view, glm::mat4& projection);

    // Gestion des touches clavier (non utilisée ici mais héritée de Drawable)
    void key_handler(int key);

    // Destructeur
    virtual ~Cube();

protected:
    GLuint VAO;              // Vertex Array Object
    GLuint VBO[4];           // Vertex Buffer Objects (positions, normales, indices)
    unsigned int num_indices;
};

#endif
