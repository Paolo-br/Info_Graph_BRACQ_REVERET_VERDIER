#include "textured_cylinder.h"

TexturedCylinder::TexturedCylinder(Shader* shader_program, Texture* texture, float height, float radius, int slices)
    : Cylinder(shader_program, height, radius, slices), texture(texture)
{
    loc_diffuse_map = glGetUniformLocation(this->shader_program_, "diffuse_map");
}

void TexturedCylinder::draw(glm::mat4& model, glm::mat4& view, glm::mat4& projection) {
    // Utiliser le programme de shader
    glUseProgram(this->shader_program_);

    // Activer et lier la texture
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture->getGLid());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // u
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); // v
    // Envoyer la texture au shader
    glUniform1i(loc_diffuse_map, 0);

    Cylinder::draw(model, view, projection);

    glBindTexture(GL_TEXTURE_2D, 0);

    glUseProgram(0);
}
