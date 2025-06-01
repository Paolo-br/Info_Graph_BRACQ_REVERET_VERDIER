#include "lighting_prism.h"
#include <glm/gtc/type_ptr.hpp>

LightingPrism::LightingPrism(Shader* shader_program,
                             glm::vec3 light_position,
                             glm::vec3 light_color,
                             glm::vec3 object_color,
                             float size_x, float size_y, float size_z)
    : Prism(shader_program, size_x, size_y, size_z),
      light_position(light_position),
      light_color(light_color),
      object_color(object_color)
{
    // Localisation des uniforms dans le shader
    light_pos_loc = glGetUniformLocation(this->shader_program_, "lightPos");
    light_color_loc = glGetUniformLocation(this->shader_program_, "lightColor");
    object_color_loc = glGetUniformLocation(this->shader_program_, "objectColor");
}

void LightingPrism::draw(glm::mat4& model, glm::mat4& view, glm::mat4& projection) {
    // Envoi des valeurs des lumières et de la couleur à utiliser
    glUniform3fv(light_pos_loc, 1, glm::value_ptr(light_position));
    glUniform3fv(light_color_loc, 1, glm::value_ptr(light_color));
    glUniform3fv(object_color_loc, 1, glm::value_ptr(object_color));

    // Appel au dessin de base
    Prism::draw(model, view, projection);
}
