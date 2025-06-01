#include "textured_prism.h"
#include <iostream>

TexturedPrism::TexturedPrism(Shader* shader_program,
    const std::vector<Texture*>& textures,
    float size_x, float size_y, float size_z)
    : Prism(shader_program, size_x, size_y, size_z), textures(textures)
{
    // Vérifie si le nombre de textures est suffisant pour toutes les faces du prisme
    if (textures.size() < face_counts.size()) {
        std::cerr << "Warning: moins de textures que de faces. Les dernières seront non texturées." << std::endl;
    }
    loc_diffuse_map = glGetUniformLocation(this->shader_program_, "diffuse_map");
}


void TexturedPrism::draw(glm::mat4& model, glm::mat4& view, glm::mat4& projection)
{
    glUseProgram(this->shader_program_);

    glBindVertexArray(VAO);

    glUniformMatrix4fv(glGetUniformLocation(shader_program_, "model"), 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(glGetUniformLocation(shader_program_, "view"), 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(glGetUniformLocation(shader_program_, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

    int offset = 0;                  // Offset dans le tableau des indices pour dessiner chaque face
    int face_count = 6;              // Nombre total de faces 
    int triangles_per_face = 2;      // Certaines faces ont 2 triangles (rectangle), d'autres 1 (triangle)

    for (int i = 0; i < textures.size(); ++i)
    {
        glActiveTexture(GL_TEXTURE0);
        
        glBindTexture(GL_TEXTURE_2D, textures[i]->getGLid());

        glUniform1i(loc_diffuse_map, 0);

        // Détermine le nombre d'indices à dessiner selon la face :
        // Les deux premières faces (bases) ont 1 triangle (3 indices), les autres 2 triangles (6 indices)
        int index_count = (i < 2) ? 3 : 6;

        
        glDrawElements(GL_TRIANGLES, index_count, GL_UNSIGNED_INT, (void*)(offset * sizeof(unsigned int)));


        offset += index_count;
    }

    
    glBindVertexArray(0);
    glUseProgram(0);
}


TexturedPrism::~TexturedPrism()
{
}
