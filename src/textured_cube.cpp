#include "textured_cube.h"
#include <GL/glew.h>
#include <iostream>


TexturedCube::TexturedCube(Shader* shader_program,
    const std::vector<Texture*>& textures,
    float size_x, float size_y, float size_z)
    : Cube(shader_program, size_x, size_y, size_z), textures_(textures)
{
   
    loc_diffuse_map = glGetUniformLocation(this->shader_program_, "diffuse_map");

   
    if (loc_diffuse_map == -1) {
        std::cerr << "Erreur : uniform 'diffuse_map' non trouvé dans le shader." << std::endl;
    }

    
    if (textures.size() != 6) {
        std::cerr << "Erreur : Le cube doit avoir 6 textures, une pour chaque face." << std::endl;
        return;
    }
}


void TexturedCube::draw(glm::mat4& model, glm::mat4& view, glm::mat4& projection)
{
    
    glUseProgram(this->shader_program_);

    
    glBindVertexArray(VAO);

    glUniformMatrix4fv(glGetUniformLocation(shader_program_, "model"), 1, GL_FALSE, &model[0][0]);
    glUniformMatrix4fv(glGetUniformLocation(shader_program_, "view"), 1, GL_FALSE, &view[0][0]);
    glUniformMatrix4fv(glGetUniformLocation(shader_program_, "projection"), 1, GL_FALSE, &projection[0][0]);

    int indices_per_face = 6; // Chaque face du cube est composée de 2 triangles, soit 6 indices

    // Parcours des 6 faces du cube
    for (int i = 0; i < 6; ++i) {
        // Active l'unité de texture 0
        glActiveTexture(GL_TEXTURE0);
        // Lie la texture correspondante à la face i
        glBindTexture(GL_TEXTURE_2D, textures_[i]->getGLid());
        // Associe l'uniform "diffuse_map" à l'unité de texture 0
        glUniform1i(loc_diffuse_map, 0);

        // Dessine les triangles de la face i en utilisant les indices correspondants
        glDrawElements(GL_TRIANGLES, indices_per_face, GL_UNSIGNED_INT,
            (void*)(i * indices_per_face * sizeof(unsigned int)));
    }

    glBindVertexArray(0);
    glUseProgram(0);
}

TexturedCube::~TexturedCube() {
}
