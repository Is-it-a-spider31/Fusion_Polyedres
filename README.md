# Fusion_Polyedres

### todo
	- clean README avant d'envoyer

	- Affichage plusieurs graphiques différent pour 1 exécution
	- Enregistrement automatique dans un dossier


	 1 - (0.2 * (d_temp / initTemp))
	 [0.8, 1]

	- Fonction objectif avec récompense et pénalité


	while different
		pour cahque poly

			merged = calculer solution

			if mergedSize < solutionSize
				solution = merged
				merged.clear()


	PARAM_1 = 1000;
	aireMax = 1.5 (tester avec 2)
	Proba = 1000 * (1 / (1 + (exp((PARAM_1 * gain) / (aireMax * d_temperature))))

	gain augmente, Proba diminue

	d_temperature diminue, Proba diminue