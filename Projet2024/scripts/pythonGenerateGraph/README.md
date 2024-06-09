# Affichage de graphiques


## Description
- Projet python qui **genère et enregistre des graphiques** (*matplotlib*) avec à partir de fichiers de données
- Exécutable : *dist/plot_graph.exe*, prend 2 arguments en paramètres (chemin du répertoire et nom du fichier) 
- L'éxécutable est utilisé par le projet C++ pour générer des graphiques

Ce projet dispose de 2 fichiers python :
- *plot_graph.py* : Sert à générer l'éxécutable, prend 2 arguments en paramètre 
    (Chemin du répertoire, nom du fichier). Affiche et enregistre  un graphique 
    à partir d'un fichier contenant des données.  
- *manual_plot_graph.py* : Permet de tester les fonctions du fichier plot_graph.py
    manuellement

## Utilisation

#### Installation des dépendances
    pip install -r requirements.txt

#### Générer l'éxécutable
L'éxécutable sera généré dans le répertoire */dist*
    
    pyinstaller --onefile plot_graph.py