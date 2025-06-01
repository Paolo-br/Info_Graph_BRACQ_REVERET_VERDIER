#ifndef TEXTURED_CONE_H
#define TEXTURED_CONE_H

#include "cone.h"
#include "texture.h"

class TexturedCone : public Cone {
public:
    TexturedCone(Shader* shader_program, Texture* texture, float height, float top_radius, float bottom_radius, int slices, bool inside = false, bool outside = true);

    void draw(glm::mat4& model, glm::mat4& view, glm::mat4& projection) override;

private:
    GLuint loc_diffuse_map;
    Texture* texture;
};

#endif // TEXTURED_CONE_H
