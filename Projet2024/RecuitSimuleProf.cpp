#include "RecuitSimuleProf.h"

#include "OBJFileHandler.h"
#include "myUtils.h"	// Pour doubleToStringRounded()


/**
 * Chemin du repertoire ves lequel l'agoritme ecrit
 * les solutions trouvees sous forme de fichiers .obj
*/
const string RecuitSimuleProf::GENERATE_OBJ_PATH = "Tests/generated/RecuitSimuleProf/";

RecuitSimuleProf::RecuitSimuleProf(const string& filename)
    : RecuitSimuleAlgorithm(filename)
{
}

/**
 * @brief Algorithme principal du recuit simule
*/
void RecuitSimuleProf::run()
{
    int maxIter = 1000;
    int maxIterStep = 24;
    d_coolingFactor = 0.95;
    int maxReducSteps = static_cast<int>(0.5 - (3.0 / log(d_coolingFactor)));
    int stagnationCrit = 1000;
    double aireMin = this->evaluateSolution(d_polyhedra);
    int continuer = 0;
    const int nbPermutations = 4;

    vector<Polyedre> bestSolution = d_polyhedra;
    double currentEval;
    double bestEval;
    int nbIterations = 0;

    int PARAM_SA_C_IT = 1;

    // Debut du chronometre (pour compter le temps d'execution)
    clock_t tStart = clock();

    do
    {
        double initialTemp = 1000.0;
        double d_temperature = initialTemp;
        int nonImprovIter = 0;
        int tempReducSteps = 0;
        int totalNbImpr = 0;
        vector<Polyedre> currentSolution = d_polyhedra;
        currentEval = this->evaluateSolution(currentSolution);
        bestEval = currentEval;

        for (int i = 1; i <= maxIter; i++)
        {
            nbIterations++;

            vector<Polyedre> neighborSolution = currentSolution;
            this->permuteNElements(neighborSolution, nbPermutations);  // Perturbation
            double neighborEval = this->evaluateSolution(neighborSolution);

            bool isAccepted = isNeighborAccepted(currentEval, neighborEval);
            if (isAccepted) {
                currentSolution = neighborSolution;
                currentEval = neighborEval;

                d_dataWriter.addPoint(nbIterations, currentEval); // ADD DATA
            }
            else {
                nonImprovIter++;
            }

            initialTemp = exp(PARAM_SA_C_IT * (-i) / maxIter) * 1000.0;
            if (i % maxIterStep == 0)
            {
                tempReducSteps++;
                if (tempReducSteps > maxReducSteps && nonImprovIter > stagnationCrit) {
                    tempReducSteps = 0;
                    if (currentEval != bestEval) {
                        bestSolution = currentSolution;
                        bestEval = currentEval;
                    }
                    d_temperature = initialTemp;
                }
                else {
                    d_temperature *= d_coolingFactor;
                }
            }
        }

        if (this->evaluateSolution(bestSolution) < aireMin)
        {
            continuer = 0;
            aireMin = this->evaluateSolution(bestSolution);
        }
        else
        {
            continuer++;
        }

        cout << "solution : " << aireMin << endl;
    } while (continuer < 2);


    // Fin du chronometre
    double timeTaken = (double)(clock() - tStart) / CLOCKS_PER_SEC;

    // Fusion sur la meilleur solution trouvee
    const vector<Polyedre> mergedBestSolution = mergeAlgorithm(bestSolution);

    // ECRITURE DE LA MEILLEURE SOLUTION EN OBJ
    cout << "SIZE : " << mergedBestSolution.size() << endl;
    // Ecriture du fichier OBJ pour cette solution
    string filename = GENERATE_OBJ_PATH + "FUSION."
        + to_string(mergedBestSolution.size()) + ".obj";
    OBJFileHandler::writeOBJ(d_vertices, mergedBestSolution, filename);

    // AFFICHAGE DU GRAPHIQUE

    // Temps d'execution en string
    string strExecutionTime;
    if (timeTaken < 60)
        strExecutionTime = doubleToStringRounded(timeTaken, 3) + " s";
    else
    {
        int minutes = static_cast<int>(timeTaken) / 60;
        double seconds = timeTaken - (minutes * 60);
        strExecutionTime = to_string(minutes) + " min " + doubleToStringRounded(seconds, 3) + " s";
    }

    // Encadre d'information sur le graphique
    string info = "Nb permutations pour voisin : " + to_string(nbPermutations) + "\\n";
    info += "Initial temp : " + to_string(1000) + "\\n";
    info += "PARAM_SA_C_IT : " + to_string(PARAM_SA_C_IT) + "\\n";
    info += "PARAM_SA_C_CS : " + to_string(10) + "\\n";
    info += "Facteur refroidissement : " + doubleToStringRounded(d_coolingFactor, 3) + "\\n";
    info += "Nb iteration par palier : " + to_string(maxIterStep) + "\\n";
    info += "Nb iteration effectuees : " + to_string(nbIterations) + "\\n";
    info += "Temps d'execution : " + strExecutionTime + "\\n";
    info += "Best eval : " + to_string(bestEval) + "\\n";
    info += "Taille finale : " + to_string(mergedBestSolution.size()) + "\\n";
    info += "Solution : ";
    for (auto& p : bestSolution)	// Affiche la solution
        info += p.getId() + " ";

    this->printDataChart(info);

}

bool RecuitSimuleProf::isNeighborAccepted(const double& currentEval, const double& neighborEval)
{
    bool isAccepted = true;
    int PARAM_SA_C_CS = 1;
    double gain = neighborEval - currentEval;
    double aireMax = d_polyhedra.size() - 1;

    std::uniform_real_distribution<double> uniformDis(0.0, 1000.0);
    // Genere un nombre entre 0 et 1000
    double random = uniformDis(d_randomGenerator);

    // O n l'accepte avec une proba de 0.5 si gain nul ou pire
    double v = 1000.0 * (1.0 / (1.0 + exp((PARAM_SA_C_CS * gain) / (aireMax * d_temperature))));
    //cout << "v = " << v << endl;
    //cout << "random = " << random << endl;
    if (gain < 0 || ((d_temperature > 0) && (random > v)))
    {
    }
    else {
        isAccepted = false;
    }
    return isAccepted;
}

/**
 * @brief Affiche le graphique qui montre l'evolution des donnees de l'algo
 */
void RecuitSimuleProf::printDataChart(const string& info)
{
    const string legend = "";
    const string title = "[Prof] Evolution de l'objectif au cours des iterations";
    d_dataWriter.writeDataToFile(
        GENERATE_OBJ_PATH + "RecuitProfChart",	// Nom fichier
        "Temperature",	// Axe X
        "Objectif",		// Axe Y
        legend,
        title,
        info,
        false	// Invertion de l'axe X
    );
}