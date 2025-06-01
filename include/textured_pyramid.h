#ifndef TEXTURED_PYRAMID_H
#define TEXTURED_PYRAMID_H

#include "pyramid.h"
#include "texture.h"
#include <vector>

class TexturedPyramid : public Pyramid {
public:
    TexturedPyramid(Shader* shader_program,
        const std::vector<Texture*>& textures,
        float base_size,
        float height );

    virtual ~TexturedPyramid();
    void draw(glm::mat4& model, glm::mat4& view, glm::mat4& projection) override;

private:
    GLuint loc_diffuse_map;
    std::vector<Texture*> textures;
};

#endif
