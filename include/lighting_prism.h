#ifndef LIGHTING_PRISM_H
#define LIGHTING_PRISM_H

#include <glm/glm.hpp>
#include "shader.h"
#include "prism.h"

class LightingPrism : public Prism {
public:
    LightingPrism(Shader* shader_program,
                  glm::vec3 light_position,
                  glm::vec3 light_color,
                  glm::vec3 object_color,
                  float size_x, float size_y, float size_z);

    virtual void draw(glm::mat4& model, glm::mat4& view, glm::mat4& projection) override;

private:
    glm::vec3 light_position;
    glm::vec3 light_color;
    glm::vec3 object_color;

    // uniform locations
    GLint light_pos_loc;
    GLint light_color_loc;
    GLint object_color_loc;
};

#endif // LIGHTING_PRISM_H
