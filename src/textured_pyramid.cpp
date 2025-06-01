#include "textured_pyramid.h"
#include <iostream>


TexturedPyramid::TexturedPyramid(Shader* shader_program,
    const std::vector<Texture*>& textures,
    float base_size, float height)
    : Pyramid(shader_program, base_size, height), textures(textures)
{
    if (textures.size() < 5) {
        std::cerr << "Warning: moins de 5 textures (1 base + 4 côtés). Certaines faces seront non texturées." << std::endl;
    }

    
    loc_diffuse_map = glGetUniformLocation(this->shader_program_, "diffuse_map");
}
void TexturedPyramid::draw(glm::mat4& model, glm::mat4& view, glm::mat4& projection)
{
    glUseProgram(this->shader_program_);

    glBindVertexArray(VAO);

    glUniformMatrix4fv(glGetUniformLocation(shader_program_, "model"), 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(glGetUniformLocation(shader_program_, "view"), 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(glGetUniformLocation(shader_program_, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

    // Matrice des normales pour les calculs d’éclairage
    glm::mat3 normalMatrix = glm::transpose(glm::inverse(glm::mat3(view * model)));
    glUniformMatrix3fv(glGetUniformLocation(shader_program_, "normalMatrix"), 1, GL_FALSE, glm::value_ptr(normalMatrix));

    // Dessin des 5 faces (1 base + 4 faces latérales)
    int offset = 0;
    for (int i = 0; i < 5; ++i)
    {
        if (i < textures.size() && textures[i]) {
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, textures[i]->getGLid());
            glUniform1i(loc_diffuse_map, 0);
        }

        // Détermine combien d'indices sont nécessaires :
        // Base : 6 indices (2 triangles), faces : 3 indices (1 triangle chacune)
        int index_count = (i == 0) ? 6 : 3;

        glDrawElements(GL_TRIANGLES, index_count, GL_UNSIGNED_INT, (void*)(offset * sizeof(unsigned int)));

        offset += index_count;
    }

    glBindVertexArray(0);
    glUseProgram(0);
}

TexturedPyramid::~TexturedPyramid()
{

}
