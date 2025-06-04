# 🏗️ Projet OpenGL — Visualisation 3D en C++

Ce projet a été réalisé dans le cadre du cours *Introduction à l’Infographie*. Il s’agit d’une scène 3D interactive développée en **C++** avec **OpenGL**, intégrant des notions de **modélisation**, **texturage**, **éclairage**, ainsi qu’un système de **caméra libre**. Le projet repose sur une architecture modulaire, avec des objets 3D personnalisés comme des **pyramides**, **prismes**, **cônes**, **structures architecturales** et une **skybox** immersive.

---

## 👨‍💻 Auteurs du projet

- **Paolo BRACQ**
- **Pablo REVERET**
- **Gabor VERDIER**

### 🔧 Répartition du travail

| Membre  | Contributions principales |
|---------|---------------------------|
| **Paolo**  | Caméra libre, contrôles utilisateur, `arche`, `statue`, `cone`, `pyramid`, `Phong_shader2`, architecture générale du projet, Skybox |
| **Pablo**  | Création des textures, modélisation de `maison`, `herbe`, `main` |
| **Gabor**  | Développement de `cube`, `prism`, `temple` |

---

## 📝 Description du projet

L’objectif était de concevoir une **scène 3D originale**, en utilisant les concepts vus en cours : modélisation avec sommets, normales et indices, **texturage multi-face**, **gestion des lumières avec un shader Phong**, et **navigation libre dans l’espace 3D**.  
Le projet a été pensé comme une petite "ville" abstraite avec une ambiance japonaise.

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
