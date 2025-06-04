#include "maison.h"
#include "textured_cube.h"
#include "textured_cone.h"
#include "textured_cylinder.h"
#include "textured_prism.h"
#include "textured_sphere.h"
#include <glm/gtc/matrix_transform.hpp>

// Création d'une maison composée de formes texturées (sol, murs, portes, toit, etc.)
// La maison est retournée sous forme d'un Node contenant tous les sous-éléments hiérarchisés.

Node* create_maison(
    Shader* texture_shader,               
    Shader* texture2_shader,              
    Texture* lampion_text,                
    std::vector<Texture*> sol_textures,   
    std::vector<Texture*> mur_textures,   
    std::vector<Texture*> porte_textures, 
    std::vector<Texture*> plafond_textures,
    std::vector<Texture*> toit_textures   
) {
    // Transformation globale de la maison (positionnée légèrement au-dessus du sol, déplacée sur Z)
    glm::mat4 maison_mat = glm::translate(glm::mat4(1.0f), glm::vec3(7.0f, -0.5f, 19.0f));

    Node* maison = new Node(maison_mat); // Racine de la maison

    // --- SOL ---
    Shape* sol = new TexturedCube(texture2_shader, sol_textures, 10.0f, 1.0f, 6.0f);
    glm::mat4 sol_mat = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -4.0f, 0.0f));
    Node* sol_node = new Node(sol_mat);
    sol_node->add(sol);
    maison->add(sol_node);

    // --- MURS LATÉRAUX (gauche et droite) ---
    Shape* mur1 = new TexturedCube(texture2_shader, mur_textures, 0.4f, 5.0f, 6.0f); // mur gauche
    glm::mat4 mur1_mat = glm::translate(glm::mat4(1.0f), glm::vec3(-4.8f, -1.0f, 0.0f));
    Node* mur1_node = new Node(mur1_mat);
    mur1_node->add(mur1);
    maison->add(mur1_node);

    Shape* mur2 = new TexturedCube(texture2_shader, mur_textures, 0.4f, 5.0f, 6.0f); // mur droit
    glm::mat4 mur2_mat = glm::translate(glm::mat4(1.0f), glm::vec3(4.8f, -1.0f, 0.0f));
    Node* mur2_node = new Node(mur2_mat);
    mur2_node->add(mur2);
    maison->add(mur2_node);

    // --- MUR ARRIÈRE (longueur plus grande, rotation à 90°) ---
    Shape* mur3 = new TexturedCube(texture2_shader, mur_textures, 0.4f, 5.0f, 10.0f);
    glm::mat4 mur3_mat = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -1.0f, 2.8f))
        * glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    Node* mur3_node = new Node(mur3_mat);
    mur3_node->add(mur3);
    maison->add(mur3_node);

    // --- PORTES AVANT (deux portes séparées) ---
    Shape* porte1 = new TexturedCube(texture2_shader, porte_textures, 0.1f, 5.0f, 3.3f);
    glm::mat4 porte1_mat = glm::translate(glm::mat4(1.0f), glm::vec3(-2.9f, -1.0f, -2.95f))
        * glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    Node* porte1_node = new Node(porte1_mat);
    porte1_node->add(porte1);
    maison->add(porte1_node);

    Shape* porte2 = new TexturedCube(texture2_shader, porte_textures, 0.1f, 5.0f, 3.3f);
    glm::mat4 porte2_mat = glm::translate(glm::mat4(1.0f), glm::vec3(2.9f, -1.0f, -2.95f))
        * glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    Node* porte2_node = new Node(porte2_mat);
    porte2_node->add(porte2);
    maison->add(porte2_node);

    // --- PLAFOND ---
    Shape* plafond = new TexturedCube(texture2_shader, plafond_textures, 10.0f, 0.2f, 6.0f);
    glm::mat4 plafond_mat = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 1.5f, 0.0f));
    Node* plafond_node = new Node(plafond_mat);
    plafond_node->add(plafond);
    maison->add(plafond_node);

    // --- TOIT PRINCIPAL (prisme triangulaire, rotations nécessaires) ---
    Shape* toit = new TexturedPrism(texture2_shader, toit_textures, 10.0f, 10.5f, 3.0f);
    glm::mat4 toit_mat = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 2.95f, 0.0f))
        * glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f))
        * glm::rotate(glm::mat4(1.0f), glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f))
        * glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    Node* toit_node = new Node(toit_mat);
    toit_node->add(toit);
    maison->add(toit_node);

    // --- PETITS TOITS LATÉRAUX (gauche et droite) ---
    Shape* toit2 = new TexturedPrism(texture2_shader, toit_textures, 3.0f, 6.0f, 1.2f);
    glm::mat4 toit2_mat = glm::translate(glm::mat4(1.0f), glm::vec3(-5.0f, 2.1f, 0.0f))
        * glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f))
        * glm::rotate(glm::mat4(1.0f), glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    Node* toit2_node = new Node(toit2_mat);
    toit2_node->add(toit2);
    maison->add(toit2_node);

    Shape* toit3 = new TexturedPrism(texture2_shader, toit_textures, 3.0f, 6.0f, 1.2f);
    glm::mat4 toit3_mat = glm::translate(glm::mat4(1.0f), glm::vec3(5.0f, 2.1f, 0.0f))
        * glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f))
        * glm::rotate(glm::mat4(1.0f), glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    Node* toit3_node = new Node(toit3_mat);
    toit3_node->add(toit3);
    maison->add(toit3_node);

    // --- LAMPION (cylindre suspendu décoratif) ---
    Shape* lampion = new TexturedCylinder(texture_shader, lampion_text, 0.8f, 0.3f, 48);
    glm::mat4 lampion_mat = glm::translate(glm::mat4(1.0f), glm::vec3(4.3f, 0.5f, 2.3f))
        * glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f))
        * glm::rotate(glm::mat4(1.0f), glm::radians(60.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    Node* lampion_node = new Node(lampion_mat);
    lampion_node->add(lampion);
    maison->add(lampion_node);

    Shape* lampion2 = new TexturedCylinder(texture_shader, lampion_text, 0.8f, 0.3f, 48);
    glm::mat4 lampion2_mat = glm::translate(glm::mat4(1.0f), glm::vec3(-4.3f, 0.5f, 2.3f))
        * glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f))
        * glm::rotate(glm::mat4(1.0f), glm::radians(105.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    Node* lampion2_node = new Node(lampion2_mat);
    lampion2_node->add(lampion2);
    maison->add(lampion2_node);

    // Retourne le node racine contenant toute la maison
    return maison;
}
