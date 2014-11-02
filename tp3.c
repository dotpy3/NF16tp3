#include "tp3.h"

// TODO :
// PENSER A COMMENTER CHAQUE FONCTION
// RESOUDRE LE BUG DE FUSION

t_ludotheque* creer_ludotheque() {
	/* Créé une nouvelle ludothèque et retourne un pointeur vers celle-ci */
	t_ludotheque *ludo = malloc(sizeof(t_ludotheque));

	if (ludo != NULL) {
		ludo->nb_jeu = 0;
		ludo->debut = NULL;
		return ludo;
	}
	return NULL; // Si la ludothèque n'a pas été correctement initialisée
}

t_jeu* creer_jeu(char *nom, int nbJoueurMin, int nbJoueurMax, genre_jeu genre, int duree) {
	/* Créé un nouveau jeu en fonction des paramètres d'entrée et retourne un pointeur vers celui-ci */
	t_jeu *jeu = malloc(sizeof(t_jeu));

	if(jeu != NULL) {
		jeu->nom = nom;
		jeu->genre = genre;
		jeu->nbJoueurMin = nbJoueurMin;
		jeu->nbJoueurMax = nbJoueurMax;
		jeu->duree = duree;
		jeu->suivant = NULL;
		return jeu;
	}
	return NULL; // Si le jeu n'a pas été correctement créé
}

int triAlphabetique(char *c1, char *c2) {
	// rend 1 si la chaîne située en premier dans l'ordre lexicographique est la 1ère, rend 2 si la chaîne située en premier est la seconde
	// la fonction rend prioritairement les chaines en minuscule
	// c1 et c2 doivent être des tableaux
	int i, longC1 = sizeof(c1), longC2 = sizeof(c2), plusGrand, max;

	if (longC1 < longC2) {
		plusGrand = 2;
		max = longC1;
	} else if (longC2 < longC1) {
		plusGrand = 1;
		max = longC2;
	} else {
		plusGrand = 0;
		max = longC1;
	}

	for (i=0;i<max;i++) {
		if (c1[i] < c2[i])
			return 1;
		else if (c2[i] < c1[i])
			return 2;
	}

	if (plusGrand == 0)
		return 0;
	else if (plusGrand == 2)
		return 1;
	else if (plusGrand == 1)
		return 2;
	else
		return -1;
}

int ajouter_jeu(t_ludotheque *ludo, t_jeu *j) {
	/* Ajoute un jeu à une ludothèque */
	if (ludo->debut == NULL) {
		// premier cas possible : il n'y a aucun jeu dans la ludothèque
		ludo->debut = j;
		ludo->nb_jeu++;
		return 1;
	} else if (triAlphabetique(j->nom,ludo->debut->nom) == 1) {
		// second cas possible : le premier jeu de la liste est situé après le nouveau dans l'ordre lexicographique
		j->suivant = ludo->debut;
		ludo->debut = j;
		return 1;
	} else {
		t_jeu *jTemp = ludo->debut;

		while ((jTemp->suivant != NULL) && (triAlphabetique(j->nom, (jTemp->suivant)->nom) == 2)) {
			jTemp = jTemp->suivant;

		}
		if (jTemp->suivant == NULL) {
			jTemp->suivant = j;
			j->suivant=NULL;
			ludo->nb_jeu++;
			return 1;
		} else {
			j->suivant = jTemp->suivant;
			jTemp->suivant = j;
			ludo->nb_jeu++;
			return 1;
		}
		return 0;
	}
}

int retirer_jeu(t_ludotheque *ludo, char *nom) {
	t_jeu *iter, *temp;
	iter = ludo->debut;
	if (iter != NULL && iter->nom == nom){
		temp = iter;
		ludo->debut = temp->suivant;
		ludo->nb_jeu--;
		free(temp);
		return 1;
	}
	while(iter != NULL && iter->suivant != NULL && (iter->suivant)->nom != nom)
		iter = iter->suivant;
	if ((iter->suivant)->nom == nom) {
		temp = iter->suivant;
		iter->suivant = temp->suivant;
		ludo->nb_jeu--;
		free(temp);
		return 1;
	} else
		return 0;
}

void supprimer_ludotheque(t_ludotheque *ludo) {
	t_jeu *iter = ludo->debut;
	t_jeu *iterTemp;
	if (iter != NULL) {
		while(iter->suivant != NULL) {
			iterTemp = iter;
			iter = iterTemp->suivant;
			free(iterTemp);
		}
		free(iter);
		free(ludo);
	} else
		free(ludo);
		return;
}

void affiche_ludotheque(t_ludotheque *ludo) {
	int i;
	char *tabTypes[5]={"PLATEAU", "RPG", "COOPERATIF", "AMBIANCE", "HASARD"};

	if(ludo->debut == NULL) {
		printf("Aucun jeu dans la ludotheque.\n");
		return;
	}

	t_jeu *iter = ludo->debut;
	printf("Nom             Type         Nombre de joueurs  Duree Moyenne    \n");

	for(i=0; i<ludo->nb_jeu; i++) {
		printf("%-16s%-13s%8d-%-10d%-17d\n", iter->nom, tabTypes[iter->genre], iter->nbJoueurMin, iter->nbJoueurMax, iter->duree);
		iter = iter->suivant;
	}

	printf("Total\t\t%d\n",ludo->nb_jeu);
}

t_ludotheque* requete_jeu(t_ludotheque *ludo, genre_jeu genre, int nbJoueurs, int duree) {
	t_ludotheque* nLudo;
	t_jeu *jTemp, *iter;
	nLudo = malloc(sizeof(t_ludotheque));
	nLudo->nb_jeu = 0;
	nLudo->debut=NULL;
	int i;

	for (i=0; i<(ludo->nb_jeu); i++) {
		iter = (i==0) ? ludo->debut : iter->suivant;

		if (nbJoueurs == -1 && duree == -1) {
			if(genre == iter->genre)
				ajouter_jeu(nLudo,iter);
		} else if (nbJoueurs == -1) {
			if((genre == iter->genre) && ((duree > 0.90*iter->duree) && (duree < 1.10*iter->duree)))
				ajouter_jeu(nLudo,iter);
		} else if (duree == -1) {
			if((genre == iter->genre) && ((nbJoueurs > iter->nbJoueurMin) && (nbJoueurs < iter->nbJoueurMax)))
				ajouter_jeu(nLudo,iter);
		} else {
			if((genre == iter->genre) && ((nbJoueurs > iter->nbJoueurMin) && (nbJoueurs < iter->nbJoueurMax)) && ((duree > 0.90*iter->duree) && (duree < 1.10*iter->duree)))
				ajouter_jeu(nLudo,iter);
		}
	}
	return nLudo;
}

int doublons(t_jeu *j, t_ludotheque *ludo) {
	/* Cette fonction permet de déterminer si j est déjà présent dans ludo en fonction de toutes ses caractéristiques.
	Si oui, il renvoit 1. Sinon, il renvoit 0.*/
	t_jeu *temp = ludo->debut;
	while(temp != NULL){
		if (temp->nom == j->nom && temp->genre == j->genre && temp->nbJoueurMin == j->nbJoueurMin && temp->nbJoueurMax == j->nbJoueurMax && temp->duree == j->duree)
			return 1;
		temp=temp->suivant;
	}
	return 0;
}

t_ludotheque* fusion(t_ludotheque *ludo1, t_ludotheque *ludo2) {
	t_ludotheque *nLudo;
	nLudo = malloc(sizeof(t_ludotheque));
	t_jeu *iter = ludo1->debut;

	while(iter != NULL) {
		ajouter_jeu(nLudo,iter);
		iter=iter->suivant;
	}

	printf("Etat actuel de la ludothèque :\n");
	affiche_ludotheque(nLudo);
	printf("On va ajouter les jeux de la ludothèque 2.\n");

	iter = ludo2->debut;
	while(iter != NULL) {
		if(doublons(iter, nLudo))
			iter = iter->suivant;
		else {
			ajouter_jeu(nLudo, iter);
			iter = iter->suivant;
		}
	}
	return nLudo;
}
