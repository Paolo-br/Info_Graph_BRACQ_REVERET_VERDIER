#include "cone.h"
#include <glm/glm.hpp>
#include "shader.h"

#ifndef LIGHTING_CONE_H
#define LIGHTING_CONE_H

class LightingCone : public Cone {
public:
    LightingCone(Shader* shader_program,glm::vec3 light_position,glm::vec3 light_color,glm::vec3 object_color, float height, float top_radius, float bottom_radius, int slices, bool inside = false, bool outside = true);

    void draw(glm::mat4& model, glm::mat4& view, glm::mat4& projection) override;

private:
    glm::vec3 light_position;
    glm::vec3 light_color;
    glm::vec3 object_color;

    GLint light_pos_loc;
    GLint light_color_loc;
    GLint object_color_loc;
};
#endif 