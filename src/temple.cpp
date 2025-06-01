#include "temple.h"
#include "textured_cube.h"
#include "textured_cone.h"
#include "textured_cylinder.h"
#include "textured_prism.h"
#include "textured_sphere.h"
#include "textured_pyramid.h"
#include <glm/gtc/matrix_transform.hpp>



Node* create_temple(Shader* texture2_shader, std::vector<Texture*> dalle_textures,std::vector<Texture*> escalier_texture,std::vector<Texture*> dernier_etage_textures,std::vector<Texture*> mur_temple_textures,std::vector<Texture*> toit_temple_textures,std::vector<Texture*> coin_textures)  // Textures pour le toit
{
    glm::mat4 temple_mat = glm::translate(glm::mat4(1.0f), glm::vec3(-10.0f, 5.5f, -15.0f))
        * glm::rotate(glm::mat4(1.0f), glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));

    Node* temple = new Node(temple_mat); // Racine du temple

    Shape* dalle = new TexturedCube(texture2_shader, dalle_textures, 17.0f, 3.0f, 10.0f);
    glm::mat4 dalle_mat = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -9.0f, 0.0f));
    Node* dalle_node = new Node(dalle_mat);
    dalle_node->add(dalle);
    temple->add(dalle_node);

    Shape* escalier = new TexturedPrism(texture2_shader, escalier_texture, 5.0f, 6.0f, 3.0f);
    glm::mat4 escalier_mat = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -9.0f, -5.0f))
        * glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f))
        * glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f))
        * glm::rotate(glm::mat4(1.0f), glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    Node* escalier_node = new Node(escalier_mat);
    escalier_node->add(escalier);
    temple->add(escalier_node);

    // --- PREMIER ETAGE ---
    Shape* premieretage = new TexturedCube(texture2_shader, mur_temple_textures,13.0f, 5.0f, 6.0f);
    glm::mat4 premieretage_mat = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -5.0f, 0.0f));
    Node* premieretage_node = new Node(premieretage_mat);
    premieretage_node->add(premieretage);
    temple->add(premieretage_node);

    // --- TOIT 1 (côté gauche) ---
    Shape* toit1 = new TexturedPrism(texture2_shader, toit_temple_textures, 3.0f, 6.0f, 1.2f);
    glm::mat4 toit1_mat = glm::translate(glm::mat4(1.0f), glm::vec3(6.5f, -2.1f, 0.0f))
        * glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f))
        * glm::rotate(glm::mat4(1.0f), glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));

    Node* toit1_node = new Node(toit1_mat);
    toit1_node->add(toit1);
    temple->add(toit1_node);

    Shape* coin1 = new TexturedPyramid(texture2_shader, coin_textures, 3.0f, 1.2f);
    glm::mat4 coin1_mat = glm::translate(glm::mat4(1.0f), glm::vec3(6.5f, -2.7f,-3.0f))
        * glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

    Node* coin1_node = new Node(coin1_mat);
    coin1_node->add(coin1);
    temple->add(coin1_node);


    // --- TOIT 2 (côté droit) ---
    Shape* toit2 = new TexturedPrism(texture2_shader, toit_temple_textures, 3.0f, 6.0f, 1.2f);
    glm::mat4 toit2_mat = glm::translate(glm::mat4(1.0f), glm::vec3(-6.5f, -2.1f, 0.0f))
        * glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f))
        * glm::rotate(glm::mat4(1.0f), glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));

    Node* toit2_node = new Node(toit2_mat);
    toit2_node->add(toit2);
    temple->add(toit2_node);

    Shape* coin2 = new TexturedPyramid(texture2_shader, coin_textures, 3.0f, 1.2f);
    glm::mat4 coin2_mat = glm::translate(glm::mat4(1.0f), glm::vec3(-6.5f, -2.7f, -3.0f))
        * glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

    Node* coin2_node = new Node(coin2_mat);
    coin2_node->add(coin2);
    temple->add(coin2_node);

    // --- TOIT 3 (côté avant) ---
    Shape* toit3 = new TexturedPrism(texture2_shader, toit_temple_textures,3.0f, 13.0f, 1.2f);
    glm::mat4 toit3_mat = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -2.1f, 3.0f))
        * glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f))
        * glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f))
        * glm::rotate(glm::mat4(1.0f), glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));

    Node* toit3_node = new Node(toit3_mat);
    toit3_node->add(toit3);
    temple->add(toit3_node);

    Shape* coin3 = new TexturedPyramid(texture2_shader, coin_textures, 3.0f, 1.2f);
    glm::mat4 coin3_mat = glm::translate(glm::mat4(1.0f), glm::vec3(6.5f, -2.7f, 3.0f))
        * glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

    Node* coin3_node = new Node(coin3_mat);
    coin3_node->add(coin3);
    temple->add(coin3_node);

    // --- TOIT 4 (côté arrière) ---
    Shape* toit4 = new TexturedPrism(texture2_shader, toit_temple_textures,3.0f, 13.0f, 1.2f);
    glm::mat4 toit4_mat = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -2.1f, -3.0f))
        * glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f))
        * glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f))
        * glm::rotate(glm::mat4(1.0f), glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));

    Node* toit4_node = new Node(toit4_mat);
    toit4_node->add(toit4);
    temple->add(toit4_node);

    Shape* coin4 = new TexturedPyramid(texture2_shader, coin_textures, 3.0f, 1.2f);
    glm::mat4 coin4_mat = glm::translate(glm::mat4(1.0f), glm::vec3(-6.5f, -2.7f, 3.0f))
        * glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

    Node* coin4_node = new Node(coin4_mat);
    coin4_node->add(coin4);
    temple->add(coin4_node);

    // --- DEUXIEME ETAGE ---
    // Je me suis pas cassé les pieds, j'ai fais x0.7 chaque dimension
    Shape* deuxiemeetage = new TexturedCube(texture2_shader, mur_temple_textures,9.1f, 3.5f, 4.2f);
    glm::mat4 deuxiemeetage_mat = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -0.7f, 0.0f));
    Node* deuxiemeetage_node = new Node(deuxiemeetage_mat);
    deuxiemeetage_node->add(deuxiemeetage);
    temple->add(deuxiemeetage_node);

    // --- TOIT 5 (côté gauche 2) ---
    // J'ai changé que la longueur
    Shape* toit5 = new TexturedPrism(texture2_shader, toit_temple_textures,3.0f, 4.2f, 1.2f);
    glm::mat4 toit5_mat = glm::translate(glm::mat4(1.0f), glm::vec3(4.55f, 1.45f, 0.0f))
        * glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f))
        * glm::rotate(glm::mat4(1.0f), glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));

    Node* toit5_node = new Node(toit5_mat);
    toit5_node->add(toit5);
    temple->add(toit5_node);

    Shape* coin5 = new TexturedPyramid(texture2_shader, coin_textures, 3.0f, 1.2f);
    glm::mat4 coin5_mat = glm::translate(glm::mat4(1.0f), glm::vec3(4.55f, 0.85f, 2.1f))
        * glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

    Node* coin5_node = new Node(coin5_mat);
    coin5_node->add(coin5);
    temple->add(coin5_node);

    // --- TOIT 6 (côté droit 2) ---
    Shape* toit6 = new TexturedPrism(texture2_shader, toit_temple_textures, 3.0f, 4.2f, 1.2f);
    glm::mat4 toit6_mat = glm::translate(glm::mat4(1.0f), glm::vec3(-4.55f, 1.45f, 0.0f))
        * glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f))
        * glm::rotate(glm::mat4(1.0f), glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));

    Node* toit6_node = new Node(toit6_mat);
    toit6_node->add(toit6);
    temple->add(toit6_node);

    Shape* coin6 = new TexturedPyramid(texture2_shader, coin_textures, 3.0f, 1.2f);
    glm::mat4 coin6_mat = glm::translate(glm::mat4(1.0f), glm::vec3(-4.55f, 0.85f, 2.1f))
        * glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

    Node* coin6_node = new Node(coin6_mat);
    coin6_node->add(coin6);
    temple->add(coin6_node);


    // --- TOIT 7 (côté avant 2) ---
    Shape* toit7 = new TexturedPrism(texture2_shader, toit_temple_textures,3.0f, 9.1f, 1.2f);
    glm::mat4 toit7_mat = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 1.45f, -2.1f))
        * glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f))
        * glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f))
        * glm::rotate(glm::mat4(1.0f), glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));

    Node* toit7_node = new Node(toit7_mat);
    toit7_node->add(toit7);
    temple->add(toit7_node);

    Shape* coin7 = new TexturedPyramid(texture2_shader, coin_textures, 3.0f, 1.2f);
    glm::mat4 coin7_mat = glm::translate(glm::mat4(1.0f), glm::vec3(-4.55f, 0.85f, -2.1f))
        * glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

    Node* coin7_node = new Node(coin7_mat);
    coin7_node->add(coin7);
    temple->add(coin7_node);

    // --- TOIT 8 (côté arrière 2) ---
    Shape* toit8 = new TexturedPrism(texture2_shader, toit_temple_textures, 3.0f, 9.1f, 1.2f);
    glm::mat4 toit8_mat = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 1.45f, 2.1f))
        * glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f))
        * glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f))
        * glm::rotate(glm::mat4(1.0f), glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));

    Node* toit8_node = new Node(toit8_mat);
    toit8_node->add(toit8);
    temple->add(toit8_node);

    Shape* coin8 = new TexturedPyramid(texture2_shader, coin_textures, 3.0f, 1.2f);
    glm::mat4 coin8_mat = glm::translate(glm::mat4(1.0f), glm::vec3(4.55f, 0.85f, -2.1f))
        * glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

    Node* coin8_node = new Node(coin8_mat);
    coin8_node->add(coin8);
    temple->add(coin8_node);


    //Troisième étage
    Shape* troisiemeetage = new TexturedCube(texture2_shader, dernier_etage_textures, 2.5f, 2.5f, 2.5f);
    glm::mat4 troisiemeetage_mat = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 2.25f, 0.0f));
    Node* troisiemeetage_node = new Node(troisiemeetage_mat);
    troisiemeetage_node->add(troisiemeetage);
    temple->add(troisiemeetage_node);
        
    Shape* top_ult = new TexturedPyramid(texture2_shader, coin_textures, 3.5f, 1.5f);
    glm::mat4 top_ult_mat = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 3.5f, 0.0f))
        * glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

    Node* top_ult_node = new Node(top_ult_mat);
    top_ult_node->add(top_ult);
    temple->add(top_ult_node);


    return temple;
}
