#ifndef TEXTURED_CYLINDER_H
#define TEXTURED_CYLINDER_H

#include "cylinder.h"
#include "texture.h"

class TexturedCylinder : public Cylinder {
public:
    TexturedCylinder(Shader* shader_program, Texture* texture, float height, float radius, int slices);

    void draw(glm::mat4& model, glm::mat4& view, glm::mat4& projection) override;

private:
    GLuint loc_diffuse_map;
    Texture* texture;
};

#endif // TEXTURED_CYLINDER_H
