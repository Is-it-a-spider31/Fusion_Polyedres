import os
import matplotlib.pyplot as plt

from plot_graph import read_data_from_file, plot_graph

if __name__ == "__main__":
# Affichage d'un graphique a partir d'un fichier ecrit
# a la main dans le code

    script_dir = os.path.dirname(os.path.abspath(__file__))
    base_path = "../../Tests/generated/RecuitSimule/"

    # current_dir = "Run_Poly18_2024-06-10-133210/"
    # current_dir = "Run_Poly18_2024-06-10-134024/"
    # current_dir = "Run_Poly21_2024-06-10-135854/"
    # current_dir = "Run_Poly18_2024-06-10-140942/"
    # current_dir = "Run_Poly19_2024-06-10-143303/"
    # current_dir = "Run_Poly20_2024-06-10-144900/"
    # current_dir = "Poly13_2024-06-10-164103/"
    # current_dir = "Run_Poly12_2024-06-10-172759/"
    current_dir = "UTILISABLE3_Run_Poly16_2024-06-10-141450/"

    # EVALUATION

    filename1 = current_dir + "RecuitChartObj" + ".txt"
    # filename1 = current_dir + "RecuitChartBestEval" + ".txt"

    file_path1 = base_path + filename1
    # Chemin complet du fichier
    file_path1 = os.path.normpath(os.path.join(script_dir, file_path1))
    # Lecture des donnees
    title, x_axis_name, y_axis_name, legend, info_box, invert_x, data_points1 = read_data_from_file(file_path1)

    # TEMLPERATURE
    filename2 = current_dir + "RecuitChartTemp" + ".txt"
    file_path2 = base_path + filename2
    # Chemin complet du fichier
    file_path2 = os.path.normpath(os.path.join(script_dir, file_path2))
    # Lecture des donnees
    title, x_axis_name, y_axis_name, legend, info_box, invert_x, data_points2 = read_data_from_file(file_path2)


    def custom_plot_graph():
            ##################################################################
            # Affichage des donnees dans un graphique
            ##################################################################
            x_axis_name = "Nb itérations"
            y_axis_name1 = "Evaluation"
            y_axis_name2 = "Température"

            # EXPLORATION
            title = "Exploration des solutions au cours des itérations"
            legend1 = "Solutions explorées" # a verifier si best eval ou pas (mais pour montrer température  normalement non)

            # BEST EVAL
            # title = "Graphe de convergence"
            # legend1 = "Meilleure solution actuelle" # a verifier si best eval ou pas (mais pour montrer température  normalement non)

            legend2 = "Température"
            x_values, y_values = zip(*data_points1)
            x_values2, y_values2 = zip(*data_points2)

            fig, ax1 = plt.subplots(figsize=(10, 6))
            # Tracer les solutions explorées sur l'axe y principal
            ax1.plot(x_values, y_values, label=legend1, color='blue', marker='o')
            ax1.set_xlabel(x_axis_name)
            ax1.set_ylabel(y_axis_name1, color='blue')
            ax1.tick_params(axis='y', labelcolor='blue')
            ax1.legend(loc='upper left')
            ax1.grid(True)

            # Créer un second axe y pour la température
            ax2 = ax1.twinx()
            ax2.plot(x_values2, y_values2, label=legend2, color='red', marker='o', alpha=0.5)
            ax2.set_ylabel(y_axis_name2, color='black')
            ax2.tick_params(axis='y', labelcolor='red')
            ax2.legend(loc='upper right')

            # Uniquement la température
            # title = "Evolution de la température au cours des itérations"
            # ax1.plot(x_values2, y_values2, label=legend2, color='red', marker='o', alpha=0.5)
            # ax1.set_xlabel(x_axis_name)
            # ax1.set_ylabel(y_axis_name2, color='black')
            # ax1.tick_params(axis='y', labelcolor='black')
            # ax1.legend(loc='upper left')
            # ax1.grid(True)

            plt.title(title)


            plt.legend()
            plt.grid(True)

            # Inverser l'axe des x
            if invert_x:
                plt.gca().invert_xaxis()

            # plt.savefig(file_path1+"EvalTemp"+".png")
            plt.show()

    custom_plot_graph()