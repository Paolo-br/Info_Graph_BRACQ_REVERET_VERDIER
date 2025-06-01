# Projet OpenGL – Visualisation 3D en C++

Ce projet est un squelette de base pour des applications graphiques en **OpenGL** avec **C++**, enrichi ici d’un système de **caméra libre**, de **formes 3D (pyramides, prismes)**, et de **textures**.

## 👨‍💻 Auteurs du projet

Ce projet a été réalisé par :

- **BRACQ Paolo**
- **REVERET Pablo**
- **VERDIER Gabor**


### 🔧 Répartition du travail

- **Paolo** : 
  - Conception de `arche`, `statue`, `cone`, `pyramid`, `Phong_shader2`.
  - Gestion de la caméra libre et du système de contrôle et de la Skybox
  - Architecture générale du code
- **Pablo** : 
  - Création des différentes textures
  - Conception de `maison`, `herbe`, `main`.
- **Gabor** : 
  - Conception de `cube`, `prism`, `temple`.
---

## 🛠️ Installation

Ce projet nécessite **CMake** pour la compilation. 

---

## 📦 Setup

Après avoir cloné ce dépôt et lancé le projet sur votre machine, voici quelques informations pratiques pour l'utilisation :

- 🎮 **Contrôles de déplacement** :
  - Flèches directionnelles : déplacement horizontal (avant, arrière, gauche, droite)
  - **Espace** : monter
  - **Shift (gauche)** : descendre
  - **Souris** : rotation de la caméra (regarder autour de soi)

- ⚠️ **Remarques** :
  - Les structures **ne sont pas solides** : il est possible de passer à travers.
  - Il **n’est pas possible de redimensionner la fenêtre**.
  - Pour **quitter l'application** : appuyez sur `Échap` ou `Q`.
