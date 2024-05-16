#include "CMake_Reine_VS.h"
#include <iostream>
#include <mpi.h>


using namespace std;

int main(int argc, char* argv[])
{
    int my_rank, num_proc_suivant, num_proc_precedent, etiquette = 100;
    int numprocs;
    int nbIndiv = 2;
    int iterChange = 5;

    MPI_Status status;
    MPI_Request request;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    num_proc_precedent = (numprocs + my_rank - 1) % numprocs;
    num_proc_suivant = (my_rank + 1) % numprocs;

    srand(time(0) + my_rank);
    geneticQueenAlgo ga(1000, 30, 14, 0.5, 0.1);
    ga.populationInit();

    //Conflit minimum trouvé
    int minConflit = ga.dimension();

    //Indice du conflit minimum
    int minConflit_Ind;
    int i = 0;

    int raz = 1;
    int winner, loser;
    int iteration = 0;

    //evaluation de la population sans changement - SI minconflit = 0 -> STOP
    while (minConflit != 0 && i < ga.popSize())
    {
        if (ga.individuEvaluate(i) < minConflit)
        {
            minConflit = ga.individuEvaluate(i);
            minConflit_Ind = i;

        }

        i++;
    }

    //Si pas de solution trouvé au problème dans la population
    if (minConflit != 0)
    {

        do
        {

            if (minConflit != 0)
            {
                //Commence un tournoi
                for (int j = 0; j < ga.popSize(); j++)
                {
                    //PICK 2 RANDOM
                    int a, b;
                    //Si a == b on repick 2 random
                    do {
                        a = rand() % ga.popSize();
                        b = rand() % ga.popSize();
                    } while (a == b);

                    //définition du winner et loser
                    if (ga.individuEvaluate(a) < ga.individuEvaluate(b))
                    {
                        winner = a;
                        loser = b;

                    }
                    else
                    {
                        winner = b;
                        loser = a;

                    }


                    //creation proba de cross et de mutation pour chaque individu

                    int rdm_cross = rand() % 101;
                    int rdm_mut = rand() % 101;

                    //si le rdm cross est < a la probacross
                    //CROSS

                    if (rdm_cross < ga.probaCross() * 100)
                    {
                        //cross la moitié des gènes winner avec loser
                        ga.crossover(winner, loser);

                        //evaluation des nouveaux individus + update

                        if (ga.individuEvaluate(winner) < minConflit)
                        {
                            minConflit = ga.individuEvaluate(winner);
                            minConflit_Ind = winner;


                        }
                        if (ga.individuEvaluate(loser) < minConflit)
                        {
                            minConflit = ga.individuEvaluate(loser);
                            minConflit_Ind = loser;

                        }
                    }
                        //Si c'est une solution on arrete
                        if (minConflit == 0)
                            break;





                        //si le rdm mutation est < a la probamutation
                        //CROSS
                        if (rdm_mut < ga.probaMut() * 100)
                        {
                            //mute un gene au hasard avec une valeur au hasard
                            ga.mutation(j);
                            // evaluation des nouveaux individus + update
                            if (ga.individuEvaluate(j) < minConflit)
                            {
                                minConflit = ga.individuEvaluate(j);
                                minConflit_Ind = j;

                            }
                            
                        }

                  //si solution on arrete
                  if (minConflit == 0)
                    break;

                  

                }

            }

            //trie la population par ordre de minimumConflit croissant
            ga.trie();
            // apres le trie, minconflit_ind vaut 1
            minConflit_Ind = 0;
            
            //toute les iterChange 
            if (raz == iterChange)
            {
               //cout << iteration << " P" << my_rank << endl;
                //Nombre de best Individu que l'on veut envoyer
                for (int c = 0; c < nbIndiv; c++)
                {
                    //creation du tableau que l'on envoie
                    vector<vector<int>> tabSend;

                    //le tableau devient une copie de la population triée
                    ga.d_populationCopy(tabSend);

                    
                    //ga.coutPop();

                    //envoie les valeurs du n ième individu au processus suivant
                    MPI_Send(&tabSend[c][0], ga.dimension(), MPI_INT, num_proc_suivant, etiquette, MPI_COMM_WORLD);
                    
                    
                   /* cout << "MOI proc " << my_rank << "je send a" << num_proc_suivant << " ";
                    for(int f = 0 ; f< ga.dimension() ; f++)
                    {
                      cout << tabSend[c][f] << " ";
                    }
                    cout << endl;*/

                    //recoit les valeurs du n ième individu du processus precedent
                    MPI_Recv(&tabSend[c][0], ga.dimension(), MPI_INT, num_proc_precedent, etiquette, MPI_COMM_WORLD, &status);



                   /* cout << "MOI proc " << my_rank << "je recoie de" << num_proc_precedent << " ";
                    for(int f = 0 ; f< ga.dimension() ; f++)
                   {
                      cout << tabSend[c][f] << " ";*/

                    //ecrase l'individu N pour mettre l'individu recu du proc précédent 
                   //en position ga.popSize()-1-nbIndiv+c
                    ga.popChange(tabSend[c], ga.popSize()-1-nbIndiv+1+c);
                   
                   /*  }
                     cout << " indice pour inser" << ga.popSize()-1-nbIndiv+1+c << endl;
                    ga.coutPop();*/
                }
              raz = 1;
            }
            //augmente iteration
            raz ++;
            //cout << iteration << endl;
            iteration++;
            
        } while (minConflit != 0);//tant que pas de solution trouvé

    }

    //SI SOLUTION TROUVé


    vector<vector<int>> r;
    ga.d_populationCopy(r);

    
    //cout << "MIN CONFLIT : " << minConflit << "   " << "indice : " << minConflit_Ind << endl;
    
    //Affichage de la solution trouvé ainsi que le num du processus qui l'a trouvé
    cout << "[ ";
    for (int i = 0; i < ga.dimension(); i++)
    {
        cout << r[minConflit_Ind][i] << " ";
    }
    cout << "] Proc:" << my_rank << " Iter:" << iteration << endl;
    // cout << r[minConflit_Ind][0] << " "<< r[minConflit_Ind][1] << " "<< r[minConflit_Ind][2] << " "<< r[minConflit_Ind][3] << endl;

    //On arrete tout
    MPI_Abort(MPI_COMM_WORLD, 0);
    MPI_Finalize();
}
