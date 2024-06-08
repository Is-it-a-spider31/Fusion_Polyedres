    /*
    
MAIL PROF POUR RECUIT

Voici l'exemple de recuit bricolé. 
Pour la formule d'acception (ou non) d'une solution voisine, 
voici celle (non nettoyée) que l'on avait utilisée pour la compétition :

if (gain < 0 || ((temp > 0) && (d_dist1000(mt_rand) > (1000.0*(1.0/(1.0 + exp((PARAM_SA_C_CS*gain)/(aireMax*temp))))))))

*/
    
    // gain = solVoisine - solCourante // (ou l'inverse)
    // aireMax = (1 - nbPolyedres // ou) nbPolyedres - 1
    
    
    int maxIter = 10000;
    int maxIterStep = 24;
    double reducCoef = 0.99;
    int maxReducSteps = (int)(0.5 - (3.0 / log(reducCoef)));
	int stagnationCrit = 100;
    long long aireMin=eval();
    int continuer=0;
    do
    {
        double temp=1000;
        double T2=temp;
        int nonImprovIter = 0;
        int tempReducSteps = 0;
        int totalNbImpr = 0;

        for (int i=1; i<=maxIter; i++)
        {
			int nbImpr = mutation((int) T2, Tmin);
			if (nbImpr != 0) {
				nonImprovIter = 0;
				if (nbImpr > 0) {
					totalNbImpr += nbImpr;
				}
			}
			else
				nonImprovIter++;

            temp = exp(PARAM_SA_C_IT * (-i) / maxIter) * 1000.0;
            if (i%maxIterStep==0)
            {
                tempReducSteps++;
                if (tempReducSteps>maxReducSteps && nonImprovIter>stagnationCrit) {
                    tempReducSteps = 0;
                    if (eval()!=Tmin.eval) {
                        save(Tmin);
                    }
                    T2 = temp;
                }
                else
                    T2*=reducCoef;
            }
        }

        save(Tmin);
        if (eval() < aireMin)
        {
            continuer=0;
            aireMin=eval();
        }
        else
        {
            continuer++;
        }

        cout << "solution : " << aireMin << endl;
    }
    while (continuer<2);
