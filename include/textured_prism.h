#ifndef TEXTURED_PRISM_H
#define TEXTURED_PRISM_H

#include "prism.h"
#include "texture.h"
#include <vector>

class TexturedPrism : public Prism {
public:
    TexturedPrism(Shader* shader_program,
                  const std::vector<Texture*>& textures,
                  float size_x, float size_y, float size_z);

    void draw(glm::mat4& model, glm::mat4& view, glm::mat4& projection) override;

    virtual ~TexturedPrism();

private:
    GLuint loc_diffuse_map;
    std::vector<Texture*> textures;
};

#endif // TEXTURED_PRISM_H
