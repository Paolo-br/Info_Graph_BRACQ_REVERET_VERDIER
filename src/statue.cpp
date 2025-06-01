#include "statue.h"
#include "textured_cube.h"
#include "textured_cone.h"
#include "textured_cylinder.h"
#include "textured_sphere.h"
#include <glm/gtc/matrix_transform.hpp>

// Fonction qui crée et assemble une statue composée de plusieurs formes 3D texturées
Node* create_statue(Shader* texture_shader, Shader* texture2_shader, Texture* cylinderTexture, Texture* sphere, std::vector<Texture*> textures) {
    // Création de la matrice de transformation principale de la statue (position, échelle, rotation)
    glm::mat4 statue_mat = glm::translate(glm::mat4(1.0f), glm::vec3(-8.0f, -2.0f, 9.0f))  // Translation
        * glm::scale(glm::mat4(1.0f), glm::vec3(2.0f, 2.0f, 2.0f))                        // Mise à l’échelle
        * glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));  // Rotation (ici nulle)
    Node* statue = new Node(statue_mat); // Création du nœud racine de la statue

    // -------------------------------------
    // Corps supérieur
    // -------------------------------------

    // Abdomen : forme de cône texturé
    Shape* abdo = new TexturedCone(texture_shader, cylinderTexture, 0.95f, 0.0f, 0.4f, 48, false, true);
    glm::mat4 abdo_mat = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.25f, -1.0f))  // Positionnement de l’abdomen
        * glm::scale(glm::mat4(1.0f), glm::vec3(1.0f))                                  // Échelle uniforme
        * glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f)); // Rotation pour orienter le cône
    Node* abdo_node = new Node(abdo_mat);  // Noeud pour l’abdomen
    abdo_node->add(abdo);                  // Ajout de la forme au nœud
    statue->add(abdo_node);                // Ajout au nœud principal de la statue

    // Chapeau : un cône placé sur la tête
    Shape* chapeau = new TexturedCone(texture_shader, cylinderTexture, 0.5f, 0.0f, 0.6f, 48, false, true);
    glm::mat4 chapeau_mat = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 1.3f, -0.9f))
        * glm::scale(glm::mat4(1.0f), glm::vec3(1.0f))
        * glm::rotate(glm::mat4(1.0f), glm::radians(-60.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    Node* chapeau_node = new Node(chapeau_mat);
    chapeau_node->add(chapeau);
    statue->add(chapeau_node);

    // Pectoraux : cylindres texturés
    Shape* pec = new TexturedCylinder(texture_shader, cylinderTexture, 1.0f, 0.2f, 48);
    glm::mat4 pec_mat = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.8f, -1.0f))
        * glm::scale(glm::mat4(1.0f), glm::vec3(1.0f))
        * glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    Node* pec_node = new Node(pec_mat);
    pec_node->add(pec);
    statue->add(pec_node);

    // Hanche : cylindre texturé
    Shape* hanche = new TexturedCylinder(texture_shader, cylinderTexture, 0.6f, 0.22f, 48);
    glm::mat4 hanche_mat = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -0.05f, -1.0f))
        * glm::scale(glm::mat4(1.0f), glm::vec3(1.0f))
        * glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    Node* hanche_node = new Node(hanche_mat);
    hanche_node->add(hanche);
    statue->add(hanche_node);

    // -------------------------------------
    // Bras droit
    // -------------------------------------

    // Épaule droite : sphère texturée
    Shape* epauled = new TexturedSphere(texture_shader, sphere, 0.20f, 36, 18);
    glm::mat4 epauled_mat = glm::translate(glm::mat4(1.0f), glm::vec3(0.45f, 0.8f, -1.0f))
        * glm::scale(glm::mat4(1.0f), glm::vec3(1.0f))
        * glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    Node* epauled_node = new Node(epauled_mat);
    epauled_node->add(epauled);
    statue->add(epauled_node);

    // Biceps droit : cylindre texturé
    Shape* bicepsd = new TexturedCylinder(texture_shader, cylinderTexture, 0.71f, 0.15f, 48);
    glm::mat4 bicepsd_mat = glm::translate(glm::mat4(1.0f), glm::vec3(0.65f, 0.77f, -0.75f))
        * glm::scale(glm::mat4(1.0f), glm::vec3(1.0f))
        * glm::rotate(glm::mat4(1.0f), glm::radians(30.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    Node* bicepsd_node = new Node(bicepsd_mat);
    bicepsd_node->add(bicepsd);
    statue->add(bicepsd_node);

    // Coude droit : sphère texturée
    Shape* couded = new TexturedSphere(texture_shader, sphere, 0.15f, 36, 18);
    glm::mat4 couded_mat = glm::translate(glm::mat4(1.0f), glm::vec3(0.87f, 0.81f, -0.46f))
        * glm::scale(glm::mat4(1.0f), glm::vec3(1.0f))
        * glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    Node* couded_node = new Node(couded_mat);
    couded_node->add(couded);
    statue->add(couded_node);

    // Avant-bras droit : cylindre texturé
    Shape* brasd = new TexturedCylinder(texture_shader, cylinderTexture, 0.73f, 0.13f, 48);
    glm::mat4 brasd_mat = glm::translate(glm::mat4(1.0f), glm::vec3(0.67f, 1.0f, -0.55f))
        * glm::scale(glm::mat4(1.0f), glm::vec3(1.0f))
        * glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f))
        * glm::rotate(glm::mat4(1.0f), glm::radians(40.0f), glm::vec3(0.0f, 1.0f, 1.0f))
        * glm::rotate(glm::mat4(1.0f), glm::radians(25.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    Node* brasd_node = new Node(brasd_mat);
    brasd_node->add(brasd);
    statue->add(brasd_node);

    // Main droite : sphère texturée
    Shape* maind = new TexturedSphere(texture_shader, sphere, 0.15f, 36, 18);
    glm::mat4 maind_mat = glm::translate(glm::mat4(1.0f), glm::vec3(0.4f, 1.2f, -0.63f))
        * glm::scale(glm::mat4(1.0f), glm::vec3(1.0f))
        * glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    Node* maind_node = new Node(maind_mat);
    maind_node->add(maind);
    statue->add(maind_node);


    //Bras gauche
    Shape* epauleg = new TexturedSphere(texture_shader, sphere, 0.20f, 36, 18);
    glm::mat4 epauleg_mat = glm::translate(glm::mat4(1.0f), glm::vec3(-0.45f, 0.8f, -1.0f))
        * glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 1.0f, 1.0f))
        * glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    Node* epauleg_node = new Node(epauleg_mat);
    epauleg_node->add(epauleg);
    statue->add(epauleg_node);

    Shape* bicepsg = new  TexturedCylinder(texture_shader, cylinderTexture, 0.71f, 0.15f, 48);
    glm::mat4 bicepsg_mat = glm::translate(glm::mat4(1.0f), glm::vec3(-0.33f, 0.68f, -0.74f))
        * glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 1.0f, 1.0f))
        * glm::rotate(glm::mat4(1.0f), glm::radians(45.0f), glm::vec3(1.0f, 1.0f, 0.0f));
    Node* bicepsg_node = new Node(bicepsg_mat);
    bicepsg_node->add(bicepsg);
    statue->add(bicepsg_node);

    Shape* coudeg = new TexturedSphere(texture_shader, sphere, 0.15f, 36, 18);
    glm::mat4 coudeg_mat = glm::translate(glm::mat4(1.0f), glm::vec3(-0.19f, 0.50f, -0.4f))
        * glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 1.0f, 1.0f))
        * glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    Node* coudeg_node = new Node(coudeg_mat);
    coudeg_node->add(coudeg);
    statue->add(coudeg_node);

    Shape* brasg = new  TexturedCylinder(texture_shader, cylinderTexture, 0.73f, 0.13f, 48);
    glm::mat4 brasg_mat = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.8f, -0.45f))
        * glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 1.0f, 1.0f))
        * glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f))
        * glm::rotate(glm::mat4(1.0f), glm::radians(-50.0f), glm::vec3(0.0f, 1.0f, 1.0f));
    Node* brasg_node = new Node(brasg_mat);
    brasg_node->add(brasg);
    statue->add(brasg_node);

    Shape* maing = new TexturedSphere(texture_shader, sphere, 0.15f, 36, 18);
    glm::mat4 maing_mat = glm::translate(glm::mat4(1.0f), glm::vec3(0.24f, 1.16f, -0.54f))
        * glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 1.0f, 1.0f))
        * glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    Node* maing_node = new Node(maing_mat);
    maing_node->add(maing);
    statue->add(maing_node);


    // Tete


    Shape* tete = new TexturedSphere(texture_shader, sphere, 0.22f, 36, 18);
    glm::mat4 tete_mat = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 1.1f, -1.0f))
        * glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 1.0f, 1.0f))
        * glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    Node* tete_node = new Node(tete_mat);
    tete_node->add(tete);
    statue->add(tete_node);

    // Jambe droite
    Shape* cuissed = new  TexturedCylinder(texture_shader, cylinderTexture, 0.7f, 0.20f, 48);
    glm::mat4 cuissed_mat = glm::translate(glm::mat4(1.0f), glm::vec3(0.4f, -0.3f, -0.85f))
        * glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 1.0f, 1.0f))
        * glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f))
        *glm::rotate(glm::mat4(1.0f), glm::radians(40.0f), glm::vec3(0.0f, 1.0f, 0.0f))
        * glm::rotate(glm::mat4(1.0f), glm::radians(-30.0f), glm::vec3(1.0f, 0.0f, .0f));
    Node* cuissed_node = new Node(cuissed_mat);
    cuissed_node->add(cuissed);
    statue->add(cuissed_node);

    Shape* genoud = new TexturedSphere(texture_shader, sphere, 0.19f, 36, 18);
    glm::mat4 genoud_mat = glm::translate(glm::mat4(1.0f), glm::vec3(0.6f, -0.5f, -0.65f))
        * glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 1.0f, 1.0f))
        * glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    Node* genoud_node = new Node(genoud_mat);
    genoud_node->add(genoud);
    statue->add(genoud_node);

    Shape* molletd = new TexturedCylinder(texture_shader, cylinderTexture, 0.7f, 0.15f, 48);
    glm::mat4 molletd_mat = glm::translate(glm::mat4(1.0f), glm::vec3(0.6f, -0.82f, -0.65f))
        * glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 1.0f, 1.0f))
        * glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    Node* molletd_node = new Node(molletd_mat);
    molletd_node->add(molletd);
    statue->add(molletd_node);

    // Jambe gauche
    Shape* cuisseg = new  TexturedCylinder(texture_shader, cylinderTexture, 0.7f, 0.20f, 48);
    glm::mat4 cuisseg_mat = glm::translate(glm::mat4(1.0f), glm::vec3(-0.4f, -0.3f, -0.85f))
        * glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 1.0f, 1.0f))
        * glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f))
        * glm::rotate(glm::mat4(1.0f), glm::radians(-40.0f), glm::vec3(0.0f, 1.0f, 0.0f))
    *glm::rotate(glm::mat4(1.0f), glm::radians(-30.0f), glm::vec3(1.0f, 0.0f, .0f));
    Node* cuisseg_node = new Node(cuisseg_mat);
    cuisseg_node->add(cuisseg);
    statue->add(cuisseg_node);    

    Shape* genoug = new TexturedSphere(texture_shader, sphere, 0.19f, 36, 18);
    glm::mat4 genoug_mat = glm::translate(glm::mat4(1.0f), glm::vec3(-0.6f, -0.5f, -0.65f))
        * glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 1.0f, 1.0f))
        * glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    Node* genoug_node = new Node(genoug_mat);
    genoug_node->add(genoug);
    statue->add(genoug_node);


    Shape* molletg = new  TexturedCylinder(texture_shader, cylinderTexture, 0.7f, 0.15f, 48);
    glm::mat4 molletg_mat = glm::translate(glm::mat4(1.0f), glm::vec3(-0.6f, -0.82f, -0.65f))
        * glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 1.0f, 1.0f))
        * glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    Node* molletg_node = new Node(molletg_mat);
    molletg_node->add(molletg);
    statue->add(molletg_node);


    //Socle
    Shape* socle = new  TexturedCylinder(texture_shader, cylinderTexture, 0.15f, 1.1f, 48);
    glm::mat4 socle_mat = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -1.3f, -0.75f))
        * glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 1.0f, 1.0f))
        * glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    Node* socle_node = new Node(socle_mat);
    socle_node->add(socle);
    statue->add(socle_node);


    //Katana
    Shape* kata = new TexturedCube(texture_shader, textures, 2.0f, 0.05f, 0.05f);
    glm::mat4 kata_mat = glm::translate(glm::mat4(1.0f), glm::vec3(-0.3f, 0.8f, -0.05f))
        * glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 1.0f, 1.0f))
        * glm::rotate(glm::mat4(1.0f), glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 1.0f));
    Node* kata_node = new Node(kata_mat);
    kata_node->add(kata);
    statue->add(kata_node);

    return statue;
}