#include "lighting_sphere.h"

LightingSphere::LightingSphere(Shader* shader_program, glm::vec3 light_position, glm::vec3 light_color, glm::vec3 object_color, float radius, int sector_count, int stack_count)
    : Sphere(shader_program, radius, sector_count, stack_count),
    light_position(light_position),
    light_color(light_color),
    object_color(object_color)
{
    
    light_pos_loc = glGetUniformLocation(this->shader_program_, "lightPos");
    light_color_loc = glGetUniformLocation(this->shader_program_, "lightColor");
    object_color_loc = glGetUniformLocation(this->shader_program_, "objectColor");
}

void LightingSphere::draw(glm::mat4& model, glm::mat4& view, glm::mat4& projection)
{
    glUniform3fv(light_pos_loc, 1, glm::value_ptr(light_position));
    glUniform3fv(light_color_loc, 1, glm::value_ptr(light_color));
    glUniform3fv(object_color_loc, 1, glm::value_ptr(object_color));

    Sphere::draw(model, view, projection);
}
