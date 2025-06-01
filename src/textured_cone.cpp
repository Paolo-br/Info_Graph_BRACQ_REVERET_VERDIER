#include "textured_cone.h"

TexturedCone::TexturedCone(Shader* shader_program, Texture* texture, float height, float top_radius, float bottom_radius, int slices, bool inside, bool outside)
    : Cone(shader_program, height, top_radius, bottom_radius, slices, inside, outside),
      texture(texture)
{
    
    loc_diffuse_map = glGetUniformLocation(this->shader_program_,  "diffuse_map");
}

void TexturedCone::draw(glm::mat4& model, glm::mat4& view, glm::mat4& projection)
{
    glUseProgram(this->shader_program_);
    
    
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture->getGLid());
    glUniform1i(loc_diffuse_map, 0); 

 
    Cone::draw(model, view, projection);
}
