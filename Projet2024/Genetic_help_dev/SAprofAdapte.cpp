#include "RecuitSimuleAlgorithm.h"

#include <algorithm>	// Pour std:swap
#include "OBJFileHandler.h"

/**
 * Chemin du repertoire ves lequel l'agoritme ecrit
 * les solutions trouvees sous forme de fichiers .obj
*/
const string RecuitSimuleAlgorithm::GENERATE_OBJ_PATH = "Tests/generated/RecuitSimule/";


RecuitSimuleAlgorithm::RecuitSimuleAlgorithm(const string& filename)
    : Algorithm(filename),
    d_coolingFactor(0.99),
    d_temperature(10000),
    d_randomGenerator(std::random_device()())
{

}

/**
 * @brief Algorithme principal du recuit simule
*/
void RecuitSimuleAlgorithm::run()
{
    int maxIter = 10000;
    int maxIterStep = 24;
    double reducCoef = 0.99;
    int maxReducSteps = static_cast<int>(0.5 - (3.0 / log(reducCoef)));
    int stagnationCrit = 1000;
    double aireMin = this->evaluateSolution(d_polyhedra);
    int continuer = 0;

    vector<Polyedre> bestSolution = d_polyhedra;

    int PARAM_SA_C_IT = 0.1;

    do
    {
        double temp = 10000.0;
        double d_temperature = temp;
        int nonImprovIter = 0;
        int tempReducSteps = 0;
        int totalNbImpr = 0;
        vector<Polyedre> currentSolution = d_polyhedra;
        double currentEval = this->evaluateSolution(currentSolution);
        double bestEval = currentEval;

        for (int i = 1; i <= maxIter; i++)
        {
            vector<Polyedre> neighborSolution = currentSolution;
            this->permuteNElements(neighborSolution, 4);  // Perturbation
            double neighborEval = this->evaluateSolution(neighborSolution);
            cout << "Eval : " << neighborEval << endl;

            bool isAccepted = isNeighborAccepted(currentEval, neighborEval);
            if (isAccepted) {
                currentSolution = neighborSolution;
                currentEval = neighborEval;
            }
            else {
                nonImprovIter++;
            }

            temp = exp(PARAM_SA_C_IT * (-i) / maxIter) * 1000.0;
            if (i % maxIterStep == 0)
            {
                tempReducSteps++;
                if (tempReducSteps > maxReducSteps && nonImprovIter > stagnationCrit) {
                    tempReducSteps = 0;
                    if (currentEval != bestEval) {
                        bestSolution = currentSolution;
                        bestEval = currentEval;
                    }
                    d_temperature = temp;
                }
                else {
                    d_temperature *= reducCoef;
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

    // ECRITURE

    cout << "SIZE : " << d_polyhedra.size() << endl;
    // Ecriture du fichier OBJ pour cette solution
    string filename = GENERATE_OBJ_PATH + "FUSION."
        + to_string(bestSolution.size()) + ".obj";
    OBJFileHandler::writeOBJ(d_vertices, bestSolution, filename);
}

/**
 * @brief Permute N > 1 elements dans la liste
 *
 * @param polyhedra Liste de polyedres a permuter
 * @param n nombre d'elements a permuter
*/
void RecuitSimuleAlgorithm::permuteNElements(vector<Polyedre>& polyhedra, const size_t n)
{
    // Si liste vide ou n < 2 : permutation impossible
    if (polyhedra.empty() || n < 2 || n > polyhedra.size())
        return;

    std::uniform_int_distribution<size_t> dis(0, polyhedra.size() - 1);
    vector<size_t> indices;	// indices des N elements a permuter

    // Liste des N indices a permuter
    while (indices.size() < n)
    {
        size_t index = dis(d_randomGenerator);	// Indice aleatoire
        // Il faut que l'indice soit different des precedents
        if (std::find(indices.begin(), indices.end(), index) == indices.end())
            indices.push_back(index);	// Ajout de l'indice
    }

    // Ajout des elements a permuter dans une liste temporaire
    vector<Polyedre> temp(n);
    for (size_t i = 0; i < n; ++i)
        temp[i] = polyhedra[indices[i]];
    // Melange des elements
    std::shuffle(temp.begin(), temp.end(), d_randomGenerator);

    // Modification de la liste initiale
    for (size_t i = 0; i < n; ++i)
        polyhedra[indices[i]] = temp[i];
}

/**
  * @brief Teste si la solution voisine est acceptee ou pas
  *
  * Calcule la probabilite d'acceptation de la solution voisine
  * avec la formule classique donne dans l'algo du recuit simule.
  *
  * @param currentEval Evaluation de la solution courante
  * @param neighborEval Evaluation de la solution voisine
  *
  * @return true si solution voisine acceptee, false sinon
 */
bool RecuitSimuleAlgorithm::isNeighborAccepted(const double& currentEval, const double& neighborEval)
{
    bool isAccepted = true;

    /*
    if (neighborEval > currentEval)
    {	// Acceptation possible avec une certaine probabilite

        double proba = std::exp((currentEval - neighborEval) / d_temperature);

        // Distribution uniforme dans [0, 1]
        std::uniform_real_distribution<double> uniformDis(0.0, 1.0);
        // Genere un nombre entre 0 et 1
        double random = uniformDis(d_randomGenerator);
        //cout << "proba" << proba << endl;
        //cout << "random" << random << endl;

        if (random >= proba)
            isAccepted = false;
    }
    */
    int PARAM_SA_C_CS = 10;
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
