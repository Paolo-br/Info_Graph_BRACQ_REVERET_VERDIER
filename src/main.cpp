#include "viewer.h"
#include "shader.h"
#include "texture.h"
#include "node.h"

// Objets texturés
#include "textured_sphere.h"
#include "textured_cylinder.h"
#include "textured_prism.h"
#include "textured_cone.h"
#include "textured_cube.h"
#include "textured_pyramid.h"

// Objets avec éclairage
#include "lighting_sphere.h"
#include "lighting_cylinder.h"
#include "lighting_cube.h"
#include "lighting_cone.h"
#include "lighting_prism.h"

// Structures personnalisées
#include "arche.h"
#include "statue.h"
#include "maison.h"
#include "temple.h"

#include <string>

#ifndef SHADER_DIR
#error "SHADER_DIR not defined"
#endif

#ifndef TEXTURE_DIR
#error "TEXTURE_DIR not defined"
#endif

// -----------------------------------------------------------------------
// Ce projet a été réalisé par BRACQ Paolo, REVERET Pablo et VERDIER Gabor
// -----------------------------------------------------------------------

int main()
{
    // Créer le viewer (fenêtre + boucle de rendu)
    Viewer viewer;

    // Définir les répertoires
    std::string shader_dir = SHADER_DIR;
    std::string texture_dir = TEXTURE_DIR;

    // -------------------------------
    // Initialisation des shaders
    // -------------------------------
    Shader* phong_shader = new Shader(shader_dir + "phong.vert", shader_dir + "phong.frag");
    Shader* texture_shader = new Shader(shader_dir + "phong2.vert", shader_dir + "phong2.frag");
    Shader* maison_shader = new Shader(shader_dir + "phong2.vert", shader_dir + "phong2.frag");
    Shader* texture2_shader = new Shader(shader_dir + "texture.vert", shader_dir + "texture.frag");
    Shader* skybox_shader = new Shader(shader_dir + "skybox.vert", shader_dir + "skybox.frag");


    // -------------------------------
    // Chargement des textures
    // -------------------------------
    // Textures pour objets
    Texture* stone1 = new Texture(texture_dir + "stone.jpg");
    Texture* stone2 = new Texture(texture_dir + "stone.jpg");
	Texture* parquet = new Texture(texture_dir + "sol.jpg");
	Texture* muret = new Texture(texture_dir + "muret.jpg");
	Texture* cloison = new Texture(texture_dir + "mur.png");
	Texture* baie = new Texture(texture_dir + "porte.png");
	Texture* carreau = new Texture(texture_dir + "plafond.png");
	Texture* tuile = new Texture(texture_dir + "toit.png");
	Texture* charpente = new Texture(texture_dir + "bois.jpg");
	Texture* lampion_text = new Texture(texture_dir + "lampion.png");
	Texture* tuile_temple = new Texture(texture_dir + "tuile.png");
	Texture* mur_temple = new Texture(texture_dir + "mur_temple.png");
	Texture* porte_temple = new Texture(texture_dir + "porte_temple.png");
	Texture* charpente2 = new Texture(texture_dir + "charpente2.png");
	Texture* dalle1 = new Texture(texture_dir + "dalle1.png");
	Texture* dalle2 = new Texture(texture_dir + "dalle2.png");
	Texture* marches = new Texture(texture_dir + "escalier.png");
    Texture* gravier = new Texture(texture_dir + "gravier.png");

    // Textures pour skybox (cube map)
    Texture* back = new Texture(texture_dir + "back2.png");
    Texture* front = new Texture(texture_dir + "front2.png");
    Texture* top = new Texture(texture_dir + "top2.png");
    Texture* bottom = new Texture(texture_dir + "bottom2.png");
    Texture* right = new Texture(texture_dir + "right.png");
    Texture* left = new Texture(texture_dir + "left.png");
	


    std::vector<Texture*> skybox_textures = { back, front, right, left, top, bottom };
    std::vector<Texture*> object_textures = { stone1, stone1, stone1, stone1, stone1, stone1 };
    std::vector<Texture*> sol_textures = { muret, muret, muret, muret, parquet, muret };
    std::vector<Texture*> mur_textures = { muret, muret, cloison, cloison, muret, muret };
    std::vector<Texture*> porte_textures = { muret, muret, baie, baie, muret, muret };
    std::vector<Texture*> plafond_textures = { muret, muret, muret, muret, muret, carreau };
    std::vector<Texture*> toit_textures = { charpente,charpente, muret, tuile, tuile };
	std::vector<Texture*> coin_textures = { charpente2,tuile_temple, tuile_temple, tuile_temple, tuile_temple };
	std::vector<Texture*> toit_temple_textures = { charpente2,charpente2, charpente2, tuile_temple, tuile_temple };
	std::vector<Texture*> mur_temple_textures = { porte_temple, porte_temple, mur_temple, mur_temple, muret, muret };
	std::vector<Texture*> dernier_etage_textures = { mur_temple, mur_temple, mur_temple, mur_temple, muret, muret };
	std::vector<Texture*> dalle_textures = { dalle1, dalle1, dalle1, dalle1, dalle2, dalle2 };
	std::vector<Texture*> escalier_texture = { dalle1,dalle1, dalle1, dalle1, marches };
    std::vector<Texture*> allee_texture = { gravier,gravier, gravier, gravier, gravier,gravier };

    // -------------------------------
    // Configuration du shader d'éclairage
    // -------------------------------
    glUseProgram(texture_shader->get_id());  // Activation du shader

    glm::vec3 lightPos = glm::vec3(1.0f, 1.0f, 1.0f);
    glm::vec3 viewPos = glm::vec3(0.0f, 2.0f, 10.0f);
    glm::vec3 ambientColor = glm::vec3(0.1f, 0.1f, 0.1f); 
    glm::vec3 specularColor = glm::vec3(1.0f, 0.3f, 0.3f);

    glUniform3fv(glGetUniformLocation(texture_shader->get_id(), "lightPos"), 1, glm::value_ptr(lightPos));
    glUniform3fv(glGetUniformLocation(texture_shader->get_id(), "viewPos"), 1, glm::value_ptr(viewPos));
    glUniform3fv(glGetUniformLocation(texture_shader->get_id(), "ambientColor"), 1, glm::value_ptr(ambientColor));
    glUniform3fv(glGetUniformLocation(texture_shader->get_id(), "specularColor"), 1, glm::value_ptr(specularColor));

    // -------------------------------
    // Création des objets de la scène
    // -------------------------------

    // Arche et statue personnalisées (assemblage de formes)
    Node* arche = create_arche(phong_shader);
    Node* statue = create_statue(texture_shader, texture2_shader, stone1, stone2, object_textures);
    Node* maison = create_maison(texture_shader, texture2_shader, lampion_text, sol_textures, mur_textures, porte_textures, plafond_textures, toit_textures);
    Node* temple = create_temple(texture2_shader, dalle_textures, escalier_texture, dernier_etage_textures, mur_temple_textures, toit_temple_textures, coin_textures);
    
    // Skybox : cube géant texturé sur chaque face

    Shape* skybox = new TexturedCube(skybox_shader, skybox_textures, 30.0f, 25.0f, 50.0f);
    glm::mat4 skybox_mat = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 7.7f, 0.0f));
    Node* skybox_node = new Node(skybox_mat);
    skybox_node->add(skybox);

    glm::mat4 decor_mat = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
    Node* decor = new Node(decor_mat);

    Shape* allee1 = new TexturedCube(texture2_shader, allee_texture, 4.0f, 0.1f, 15.0f);
    glm::mat4 allee1_mat = glm::translate(glm::mat4(1.0f), glm::vec3(7.0f, -4.7f, 9.0f));
    Node* allee1_node = new Node(allee1_mat);
    allee1_node->add(allee1);
    decor->add(allee1_node);

    Shape* allee2 = new TexturedCube(texture2_shader, allee_texture, 4.0f, 0.1f, 19.0f);
    glm::mat4 allee2_mat = glm::translate(glm::mat4(1.0f), glm::vec3(7.0f, -4.7f, -7.5f));
    Node* allee2_node = new Node(allee2_mat);
    allee2_node->add(allee2);
    decor->add(allee2_node);


    Shape* allee3 = new TexturedCube(texture2_shader, allee_texture, 4.0f, 0.1f, 10.0f);
    glm::mat4 allee3_mat = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -4.7f, 9.0f))
        * glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    Node* allee3_node = new Node(allee3_mat);
    allee3_node->add(allee3);
    decor->add(allee3_node);

    Shape* allee4 = new TexturedCube(texture2_shader, allee_texture, 4.0f, 0.1f, 8.0f);
    glm::mat4 allee4_mat = glm::translate(glm::mat4(1.0f), glm::vec3(1.0f, -4.7f, -15.0f))
        * glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    Node* allee4_node = new Node(allee4_mat);
    allee4_node->add(allee4);
    decor->add(allee4_node);

    Shape* socle = new  TexturedCylinder(texture2_shader, gravier, 0.1f, 4.0f, 48);
    glm::mat4 socle_mat = glm::translate(glm::mat4(1.0f), glm::vec3(-8.5f, -4.7f, 9.0f))
        * glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 1.0f, 1.0f))
        * glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    Node* socle_node = new Node(socle_mat);
    socle_node->add(socle);
    decor->add(socle_node);

    // Cr�er le n�ud principal de herbe
    glm::mat4 herbe_mat = glm::translate(glm::mat4(1.0f), glm::vec3(-4.5f, -4.2f, 11.0f))
        * glm::scale(glm::mat4(1.0f), glm::vec3(4.0f, 4.0f, 4.0f))
        * glm::rotate(glm::mat4(1.0f), glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    Node* herbe = new Node(herbe_mat);

    glm::mat4 herbeg_mat = glm::translate(glm::mat4(1.0f), glm::vec3(-4.5f, -4.2f, 7.0f))
        * glm::scale(glm::mat4(1.0f), glm::vec3(4.0f, 4.0f, 4.0f))
        * glm::rotate(glm::mat4(1.0f), glm::radians(-45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    Node* herbeg = new Node(herbeg_mat);

    Shape* herbe1 = new LightingCylinder(phong_shader, glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.1f, 0.65f, 0.1f), 0.3f, 0.01f, 48);
    glm::mat4 herbe1_mat = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f))
        * glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 1.0f, 1.0f))
        * glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    Node* herbe1_node = new Node(herbe1_mat);
    herbe1_node->add(herbe1);
    herbe->add(herbe1_node);
    herbeg->add(herbe1_node);

    Shape* herbe2 = new LightingCylinder(phong_shader, glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.1f, 0.65f, 0.1f), 0.2f, 0.01f, 48);
    glm::mat4 herbe2_mat = glm::translate(glm::mat4(1.0f), glm::vec3(-0.02f, -0.04f, 0.0f))
        * glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 1.0f, 1.0f))
        * glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f))
        * glm::rotate(glm::mat4(1.0f), glm::radians(10.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    Node* herbe2_node = new Node(herbe2_mat);
    herbe2_node->add(herbe2);
    herbe->add(herbe2_node);
    herbeg->add(herbe2_node);

    Shape* herbe3 = new LightingCylinder(phong_shader, glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.1f, 0.65f, 0.1f), 0.15f, 0.01f, 48);
    glm::mat4 herbe3_mat = glm::translate(glm::mat4(1.0f), glm::vec3(0.02f, -0.05f, 0.0f))
        * glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 1.0f, 1.0f))
        * glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f))
        * glm::rotate(glm::mat4(1.0f), glm::radians(-10.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    Node* herbe3_node = new Node(herbe3_mat);
    herbe3_node->add(herbe3);
    herbe->add(herbe3_node);
    herbeg->add(herbe3_node);

    decor->add(herbe);
    decor->add(herbeg);

    viewer.animated_nodes.push_back(statue);

    // -------------------------------
    // Ajout des objets à la scène
    // -------------------------------
    viewer.scene_root->add(arche);
    viewer.scene_root->add(maison);
    viewer.scene_root->add(statue);
    viewer.scene_root->add(skybox_node);
	viewer.scene_root->add(temple);
    viewer.scene_root->add(decor);


    // -------------------------------
    // Lancement du rendu
    // -------------------------------
    viewer.run();


    return 0;
}
