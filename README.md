# Fusion de polyèdres - 2024

**Contexte :** Projet semestre 2 master 1 informatique et mobilité - Université de Strasbourg

### Auteurs
- Jérôme Dubois
- Antoine Fontaine
### Encadrant
- Julien Lepagnot

## Description
Ce projet a pour but de développer un algorithme visant à fusionner itérativement des polyèdres convexes élémentaires de façon à minimiser le nombre de polyèdres convexes résultant de cette fusion. 

L'objectif est de trouver dans quel ordre fusionner les polyèdres afin de minimiser le nombre.

## Aspects techniques
Tous les fichiers d'environnement 3D sont au format *.obj*.
#### Environnement de developpement
- **C++ 14**
- Visual studio
- Blender (pour visualiser les fichiers *.obj*)

#### Documentation Doxygen
- Installer doxygen
- Ouvrir un terminal dans le répertoire */Projet2024*
- Tapez ***doxygen Doxyfile*** pour générer la documentation html

La documentation est générée dans le **répertoire */doc*** a la racine du projet.
Les paramètres de génération sont configurés dans le fichier */Projet2024/Doxyfile*.

L'auto completion des commentaires Doxygen dans le code peut être activée dans visual studio

## Fonctionnalités
- Fusion de polyèdres
- Graphe des fusions convexes
- Algorithme Force-brute
- Algorithme de recuit simulé
- Algorithme génétique
- Sauvegarde / Affichage des résultats trouvés

## Structure du projet

### /Projet2024/Tests/
- Les répertoires suffixés par "*Test*" contiennent des fichiers "*.obj*" qui ont été utilisé pour tester le code. 
- */TestsBlender/* contient des projets blenders qui sont utilisés pour visualiser des résultats ou créer des fichiers "*.obj*" à tester.
- ***/generated/*** contient les **resultats générés** par le projet C++. Chaque type d'algorithme a un répertoire dédié

### /Projet2024/scripts/
#### 2 scripts "delete_obj_files":
- (un pour windows et un pour linux) qui permettent de supprimer les fichiers "*.obj*" du répertoire */Projet2024/Tests/generated/BruteForce/*
- Ils sont appelés automatiquement par le projet C++
#### pythonGenerateGraph/ : 
- Projet python qui **genère et enregistre des graphiques** (matplotlib) avec à partir de fichiers de données
- Exécutable : *dist/plot_graph.exe*, prend 2 arguments en paramètres (chemin du répertoire et nom du fichier) 
- L'éxécutable est utilisé par le projet C++ pour générer des graphiques