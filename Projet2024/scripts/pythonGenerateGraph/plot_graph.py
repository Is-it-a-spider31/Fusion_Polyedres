import matplotlib.pyplot as plt
import argparse

def read_data_from_file(filename):
    ##################################################################
    #   Lecture des donnes contenues dans le fichier
    ##################################################################

    with open(filename, 'r') as file:
        lines = file.readlines()

    title = lines[0].split(':')[1].strip()
    x_axis_name = lines[1].split(':')[1].strip()
    y_axis_name = lines[2].split(':')[1].strip()
    legend = lines[3].split(':')[1].strip()

    # Extraction du texte après le premier ":"
    info_box = lines[4].split(':', 1)[1].strip()
    # Remplacement des \\n par \n
    info_box = info_box.replace("\\n", "\n")

    invert_x = lines[5].split(':')[1].strip() == "1" # 1 => True

    data_points = []
    for line in lines[7:]:
        x, y = map(float, line.split(','))
        data_points.append((x, y))

    return title, x_axis_name, y_axis_name, legend, info_box, invert_x, data_points


def plot_graph(title, x_axis_name, y_axis_name, legend, info_box, invert_x, data_points, filepath):
    ##################################################################
    # Affichage des donnees dans un graphique
    ##################################################################

    x_values, y_values = zip(*data_points)

    plt.figure(figsize=(10, 6))
    plt.plot(x_values, y_values, label=legend, color='blue', marker='o')
    plt.title(title)
    plt.xlabel(x_axis_name)
    plt.ylabel(y_axis_name)
    plt.legend()
    plt.grid(True)

    # Inverser l'axe des x
    if invert_x:
        plt.gca().invert_xaxis()

    # Ajout de l'info box
    plt.annotate(info_box, xy=(0.5, 0.5), xycoords='axes fraction', fontsize=10,
                 bbox=dict(facecolor='white', edgecolor='black'))

    plt.savefig(filepath+filename+".png")
    plt.show()


##################################################################
# Lit les donnees du fichier passe en argument, puis affiche
# le graphique correspondant.
#
# Cf. README.txt pour plus de détails.
##################################################################
if __name__ == "__main__":

    # Chemin/nom du fichier passe en argument
    parser = argparse.ArgumentParser()
    parser.add_argument('filepath', type=str)
    parser.add_argument('filename', type=str)
    filename = parser.parse_args().filename
    filepath = parser.parse_args().filepath

    # Lecture des donnees
    title, x_axis_name, y_axis_name, legend, info_box, invert_x, data_points = read_data_from_file(filepath+filename + ".txt")

    # Affichage des donnes
    plot_graph(title, x_axis_name, y_axis_name, legend, info_box, invert_x, data_points, filepath)