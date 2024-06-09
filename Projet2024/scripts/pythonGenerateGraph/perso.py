import os

from plot_graph import read_data_from_file, plot_graph

if __name__ == "__main__":
# Affichage d'un graphique a partir d'un fichier ecrit
# a la main dans le code

    script_dir = os.path.dirname(os.path.abspath(__file__))

    # EVALUATION
    filename1 = "RecuitChart_2024-05-29-115502" + ".txt"
    file_path1 = "../../Tests/generated/RecuitSimule/" + filename1
    # Chemin complet du fichier
    file_path1 = os.path.normpath(os.path.join(script_dir, file_path1))
    # Lecture des donnees
    title, x_axis_name, y_axis_name, legend, info_box, invert_x, data_points1 = read_data_from_file(file_path1)

    # TEMLPERATURE
    filename2 = "RecuitChart_2024-05-29-115502" + ".txt"
    file_path2 = "../../Tests/generated/RecuitSimule/" + filename2
    # Chemin complet du fichier
    file_path2 = os.path.normpath(os.path.join(script_dir, file_path2))
    # Lecture des donnees
    title, x_axis_name, y_axis_name, legend, info_box, invert_x, data_points2 = read_data_from_file(file_path1)


def custom_plot_graph():
        ##################################################################
        # Affichage des donnees dans un graphique
        ##################################################################

        title = "Evolution température et eexplorations des solutions au au cours itérations"
        x_values, y_values = zip(*data_points)
        x_values2, y_values2 = zip(*data_points2)
        legned1 = "Solutions explorées" # a verifier si best eval ou pas (mais pour montrer température  normalement non)
        legned2 = "Température"

        plt.figure(figsize=(10, 6))
        plt.plot(x_values, y_values, label=legend1, color='blue', marker='o')
        plt.plot(x_values2, y_values2, label=legend2, color='red', marker='o')
        plt.title(title)
        plt.xlabel(x_axis_name)
        plt.ylabel(y_axis_name)
        plt.legend()
        plt.grid(True)

        # Inverser l'axe des x
        if invert_x:
            plt.gca().invert_xaxis()

        # Ajout de l'info box
        # plt.annotate(info_box, xy=(0.5, 0.5), xycoords='axes fraction', fontsize=10,
        #              bbox=dict(facecolor='white', edgecolor='black'))

        plt.savefig(filepath1+"EvalTemp"+".png")
        plt.show()