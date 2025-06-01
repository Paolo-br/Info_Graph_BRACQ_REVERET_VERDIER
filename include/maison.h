#include "node.h"
#include "shader.h"
#include "texture.h"

Node* create_maison(Shader* texture_shader, Shader* texture2_shader,Texture* lampion_text, std::vector<Texture*> sol_textures,std::vector<Texture*> mur_textures,std::vector<Texture*> porte_textures,std::vector<Texture*> plafond_textures,std::vector<Texture*> toit_textures);