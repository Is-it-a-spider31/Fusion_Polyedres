#!/bin/bash

# SCRIPT BASH POUR LINUX

# Supprime les fichiers .obj qui sont generes par le programme c++
# (evite de supprimer les fichiers a la main avant chaque execution)

# ATTENTION : prendre en compte que le script est execute depuis le fichier main.cpp 
# Les chemins sont donc relatifs au fichier main.cpp

# Bruteforce
directory="Tests/generated/BruteForce"
find "$directory" -type f -name "*.obj" -delete

# Recuit simule
directory="Tests/generated/RecuitSimule"
find "$directory" -type f -name "*.obj" -delete

# Genetique
directory="Tests/generated/GeneticAlgo"
find "$directory" -type f -name "*.obj" -delete

