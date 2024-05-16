#!/bin/bash

# SCRIPT BASH POUR LINUX

# Supprime les fichiers .obj qui sont generes par le projet cpp
# (evite de supprimer les fichiers a la main avant chaque execution)
directory="MergeTest\generated"  # Chemin du repertoire
find "$directory" -type f -name "*.obj" -delete

directory="RecuitSimule\generated"  # Chemin du repertoire
find "$directory" -type f -name "*.obj" -delete