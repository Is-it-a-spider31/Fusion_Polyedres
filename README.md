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

## Documentation

#### Doxygen
- Installer doxygen
- Ouvrir un terminal dans le répertoire */Projet2024*
- Tapez la commande pour générer la documentation html
  
        doxygen Doxyfile

La documentation est générée dans le **répertoire */doc*** a la racine du projet.
Les paramètres de génération sont configurés dans le fichier */Projet2024/Doxyfile*. \
L'auto completion des commentaires Doxygen dans le code peut être activée dans visual studio. \
Voici un exemples de variables intéressantes à modifier dans le fichier Doxyfile :

    # Nom du projet
    PROJECT_NAME           = "Nom du projet"
    ...
    # Répertoire d'entrée
    INPUT                  = ./
    ...
    # Inclure récursivement les sous-répertoires
    RECURSIVE              = YES
    ...
    # Exclure plusieurs patterns
    EXCLUDE_PATTERNS       = */test/* *.cpp
    ...
    # Répertoire de sortie
    OUTPUT_DIRECTORY       = doc
    ...
    # Générer de la documentation HTML
    GENERATE_HTML          = YES
    ...
    # Ne pas générer de documentation LaTeX
    GENERATE_LATEX         = NO
    ...
    # Optimiser la sortie pour éviter les redondances
    OPTIMIZE_OUTPUT_FOR_C  = YES


#### Diagramme de classe visual studio
- Fichier *ClassDiagram.cd*
- Pour lire le fichier il faut installer une extension visual studio : 
  - https://stackoverflow.com/questions/17191218/generate-a-class-diagram-from-visual-studio
- Les associations ne sont pas représentées
  - https://stackoverflow.com/questions/47895358/creating-aggregation-and-composition-in-class-diagram-in-visual-studio-2017


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
#### pythonGenerateGraph/ : 
- Projet python qui **genère et enregistre des graphiques** (matplotlib) avec à partir de fichiers de données
- Exécutable : *dist/plot_graph.exe*, prend 2 arguments en paramètres (chemin du répertoire et nom du fichier) 
- L'éxécutable est utilisé par le projet C++ pour générer des graphiques