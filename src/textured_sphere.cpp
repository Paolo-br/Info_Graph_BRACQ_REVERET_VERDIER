#include "textured_sphere.h"

TexturedSphere::TexturedSphere(Shader* shader_program, Texture* texture, float radius, int sector_count, int stack_count)
    : Sphere(shader_program, radius, sector_count, stack_count), texture(texture)
{
    loc_diffuse_map = glGetUniformLocation(this->shader_program_, "diffuse_map");
}

void TexturedSphere::draw(glm::mat4& model, glm::mat4& view, glm::mat4& projection) {

    glUseProgram(this->shader_program_);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture->getGLid());

    glUniform1i(loc_diffuse_map, 0);

    Sphere::draw(model, view, projection);

    glBindTexture(GL_TEXTURE_2D, 0);

    glUseProgram(0);

}