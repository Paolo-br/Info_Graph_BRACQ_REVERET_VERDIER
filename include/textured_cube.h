#ifndef TEXTURED_CUBE_H
#define TEXTURED_CUBE_H

#include "cube.h"
#include "texture.h"
#include <vector>
#include <glm/glm.hpp>

class TexturedCube : public Cube {
public:
    TexturedCube(Shader* shader_program, 
                 const std::vector<Texture*>& textures, 
                 float size_x, float size_y, float size_z);
    
    void draw(glm::mat4& model, glm::mat4& view, glm::mat4& projection) override;
    ~TexturedCube();

private:
    GLuint loc_diffuse_map;  
    std::vector<Texture*> textures_;  // Vecteur de 6 textures (une par face)
};

#endif // TEXTURED_CUBE_H