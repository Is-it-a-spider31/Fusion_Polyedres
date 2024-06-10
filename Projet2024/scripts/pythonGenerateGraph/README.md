# Affichage de graphiques


## Description
- Projet python qui **genère et enregistre des graphiques** (*matplotlib*) avec à partir de fichiers de données
- Exécutable : *dist/plot_graph.exe*, prend 2 arguments en paramètres (chemin du répertoire et nom du fichier) 
- L'éxécutable est utilisé par le projet C++ pour générer des graphiques

Ce projet dispose de 3 fichiers python :
- **plot_graph.py** : Sert à générer l'éxécutable, prend 2 arguments en paramètre 
    (Chemin du répertoire, nom du fichier). Affiche et enregistre  un graphique 
    à partir d'un fichier contenant des données.  
- **manual_plot_graph.py** : Permet de tester les fonctions du fichier plot_graph.py
    manuellement
- **perso.py** : qui permet de générer des graphes complétement customisés manuellement 
    (pour rendre des documents par exemple)

## Utilisation

#### Ouvrir Le projet avec Pycharm
- Créer un nouveau projet
- Sélectionner le répertoire *pythonGenerateGraph* (créer un projet à partir de sources)
- L'utilisation d'un environnement virtuel est conseillé

#### Installation des dépendances
    pip install -r requirements.txt

#### Générer l'éxécutable
L'éxécutable sera généré dans le répertoire */dist*
    
    pyinstaller --onefile plot_graph.py