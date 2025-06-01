#include "lighting_cylinder.h"

LightingCylinder::LightingCylinder(Shader *shader_program, glm::vec3 light_position, glm::vec3 light_color, glm::vec3 object_color, float height, float radius, int slices):
    Cylinder(shader_program, height, radius, slices),
    light_position(light_position),
    light_color(light_color),
    object_color(object_color)
{
    light_pos_loc = glGetUniformLocation(this->shader_program_, "lightPos");
    light_color_loc = glGetUniformLocation(this->shader_program_, "lightColor");
    object_color_loc = glGetUniformLocation(this->shader_program_, "objectColor");
}

void LightingCylinder::draw(glm::mat4& model, glm::mat4& view, glm::mat4& projection) {
    
    glUniform3fv(light_pos_loc, 1, glm::value_ptr(light_position));
    glUniform3fv(light_color_loc, 1, glm::value_ptr(light_color));
    glUniform3fv(object_color_loc, 1, glm::value_ptr(object_color));


    Cylinder::draw(model, view, projection);


}
