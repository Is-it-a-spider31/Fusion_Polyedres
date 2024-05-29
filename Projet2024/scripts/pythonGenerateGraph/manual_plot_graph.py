import os

from plot_graph import read_data_from_file, plot_graph

if __name__ == "__main__":
# Affichage d'un graphique a partir d'un fichier ecrit
# a la main dans le code

    script_dir = os.path.dirname(os.path.abspath(__file__))

    filename = "RecuitChart_2024-05-29-102414" + ".txt"
    file_path = "../../Tests/generated/RecuitSimule/" + filename
    # path = "/../../Tests/generated/GeneticAlgo/" + filename
    # path = "/../../Tests/generated/BruteForce/" + filename

    # Chemin complet du fichier
    file_path = os.path.normpath(os.path.join(script_dir, file_path))

    # Lecture des donnees
    title, x_axis_name, y_axis_name, legend, info_box, invert_x, data_points = read_data_from_file(file_path)

    # Affichage des donnes
    plot_graph(title, x_axis_name, y_axis_name, legend, info_box, invert_x, data_points)
