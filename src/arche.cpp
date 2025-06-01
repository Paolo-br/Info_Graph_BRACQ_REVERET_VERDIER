#include "arche.h"
#include "lighting_cylinder.h"
#include "lighting_cube.h"
#include <glm/gtc/matrix_transform.hpp>

// Fonction qui construit une arche composée de cylindres et de cubes, avec transformations
Node* create_arche(Shader* phong_shader) {
    // Matrice de transformation principale de l'arche : positionnée et agrandie
    glm::mat4 arche_mat = glm::translate(glm::mat4(1.0f), glm::vec3(7.0f, 0.0f, 3.0f)) // Position dans la scène
        * glm::scale(glm::mat4(1.0f), glm::vec3(2.50f, 2.50f, 2.50f)) // Mise à l’échelle
        * glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f)); // Rotation (inutile ici)

    Node* arche = new Node(arche_mat); // Création du nœud racine

    // === Poteau gauche ===
    // Cylindre vertical rouge
    Shape* poteauGauche = new LightingCylinder(phong_shader, glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f), glm::vec3(1.0f, 0.0f, 0.0f), 2.5f, 0.2f, 48);
    glm::mat4 poteauGauche_mat = glm::translate(glm::mat4(1.0f), glm::vec3(1.0f, 0.0f, 0.0f)) // Translation à droite
        * glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f)); // Redresse le cylindre
    Node* poteauGauche_node = new Node(poteauGauche_mat);
    poteauGauche_node->add(poteauGauche);
    arche->add(poteauGauche_node);

    // === Pied gauche ===
    // Petit cylindre à la base
    Shape* piedGauche = new LightingCylinder(phong_shader, glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f), glm::vec3(0.15f), 0.5f, 0.25f, 48);
    glm::mat4 piedGauche_mat = glm::translate(glm::mat4(1.0f), glm::vec3(1.0f, -1.5f, 0.0f))
        * glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    Node* piedGauche_node = new Node(piedGauche_mat);
    piedGauche_node->add(piedGauche);
    arche->add(piedGauche_node);

    // === Socle gauche ===
    // Cube plat servant de base
    Shape* socleGauche = new LightingCube(phong_shader, glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f), glm::vec3(0.15f), 0.6f, 0.2f, 0.6f);
    glm::mat4 socleGauche_mat = glm::translate(glm::mat4(1.0f), glm::vec3(1.0f, -1.85f, 0.0f));
    Node* socleGauche_node = new Node(socleGauche_mat);
    socleGauche_node->add(socleGauche);
    arche->add(socleGauche_node);

    // === Poteau droit ===
    // Même logique que le poteau gauche, mais symétrique
    Shape* poteauDroit = new LightingCylinder(phong_shader, glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f), glm::vec3(1.0f, 0.0f, 0.0f), 2.5f, 0.2f, 48);
    glm::mat4 poteauDroit_mat = glm::translate(glm::mat4(1.0f), glm::vec3(-1.0f, 0.0f, 0.0f))
        * glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    Node* poteauDroit_node = new Node(poteauDroit_mat);
    poteauDroit_node->add(poteauDroit);
    arche->add(poteauDroit_node);

    // === Pied droit ===
    Shape* piedDroit = new LightingCylinder(phong_shader, glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f), glm::vec3(0.15f), 0.5f, 0.25f, 48);
    glm::mat4 piedDroit_mat = glm::translate(glm::mat4(1.0f), glm::vec3(-1.0f, -1.5f, 0.0f))
        * glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    Node* piedDroit_node = new Node(piedDroit_mat);
    piedDroit_node->add(piedDroit);
    arche->add(piedDroit_node);

    // === Socle droit ===
    Shape* socleDroit = new LightingCube(phong_shader, glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f), glm::vec3(0.15f), 0.6f, 0.2f, 0.6f);
    glm::mat4 socleDroit_mat = glm::translate(glm::mat4(1.0f), glm::vec3(-1.0f, -1.85f, 0.0f));
    Node* socleDroit_node = new Node(socleDroit_mat);
    socleDroit_node->add(socleDroit);
    arche->add(socleDroit_node);

    // === Haut 1 : barre rouge inclinée ===
    Shape* haut = new LightingCube(phong_shader, glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f), glm::vec3(1.0f, 0.0f, 0.0f), 4.0f, 0.25f, 0.25f);
    glm::mat4 haut_mat = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 1.25f, 0.0f))
        * glm::rotate(glm::mat4(1.0f), glm::radians(45.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    Node* haut_node = new Node(haut_mat);
    haut_node->add(haut);
    arche->add(haut_node);

    // === Haut 2 : barre rouge courte ===
    Shape* haut2 = new LightingCube(phong_shader, glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f), glm::vec3(1.0f, 0.0f, 0.0f), 3.0f, 0.2f, 0.2f);
    glm::mat4 haut2_mat = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.5f, 0.0f))
        * glm::rotate(glm::mat4(1.0f), glm::radians(45.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    Node* haut2_node = new Node(haut2_mat);
    haut2_node->add(haut2);
    arche->add(haut2_node);

    // === Haut 3 : barre noire horizontale ===
    Shape* haut3 = new LightingCube(phong_shader, glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f), glm::vec3(0.15f), 4.5f, 0.25f, 0.4f);
    glm::mat4 haut3_mat = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 1.3f, 0.0f));
    Node* haut3_node = new Node(haut3_mat);
    haut3_node->add(haut3);
    arche->add(haut3_node);

    // === Haut 4 : petit carré central rouge ===
    Shape* haut4 = new LightingCube(phong_shader, glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f), glm::vec3(1.0f, 0.0f, 0.0f), 0.2f, 0.65f, 0.1f);
    glm::mat4 haut4_mat = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.75f, 0.0f));
    Node* haut4_node = new Node(haut4_mat);
    haut4_node->add(haut4);
    arche->add(haut4_node);

    // Retourne le nœud racine contenant toute la structure
    return arche;
}
