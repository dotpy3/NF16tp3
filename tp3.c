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
		if (jTemp->suivant != NULL) {
			jTemp->suivant = j;
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
	printf("On va ajouter les jeux de la ludothèque 2.");

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

int main() {
	t_ludotheque *ludotest,*ludotest2;
	t_jeu *jeutest1;
	int nbLudos = 0, choixtri = 0, choix = 0, choixLudo = 0, choixLudo2 = 0, genreTMP, minTMP, maxTMP, dureeTMP, ludoCreee[2];
	ludoCreee[0]=0;
	ludoCreee[1]=0;
	int param1, param2, param3; //param1 : nbJoueurs, param2 : duree, param3 : genre
	char *nomTMP;

    /*
      L'entier choix détermine ce qui doit se passer dans la boucle.
      0 : doit afficher le menu
      1 : doit créer une ludothèque
      2 : doit afficher une ludothèque
      3 : Demande le tri et l'affichage d'une ludothèque pour les différents champs
      (par nom, par nombre de joueur minimum, par genre, par durée)
      4 : ajoute un jeu dans la ludothèque en saisissant ses caractéristiques
      5 : effectue une recherche de jeu à partir des critères de l'utilisateur
      6 : Crée 2 ludothèques, les affiche, les fusionne, et affiche la nouvelle ludothèque
      7 : doit quitter
    */

	while (choix != 6) {
		switch(choix) {
			case 1: // doit créer une ludothèque
				printf("====> CREATION DE LUDOTHEQUE\n\nSi la ludothèque existe déjà, elle sera remplacée.\nQuelle ludothèque voulez-vous créer ? (1/2)\n> ");
				scanf("%d",&choixLudo);
				if(choixLudo == 1)
					{ludotest = creer_ludotheque();
					ludoCreee[0] = 1;}
				else if(choixLudo == 2)
					{ludotest2 = creer_ludotheque();
					ludoCreee[1] = 1;}
				choix=0;
				printf("\nEtat de ludoCreee[%d] : %d\n\n",choixLudo,ludoCreee[choixLudo-1]);
				break;
			case 2:
				printf("====> AFFICHAGE DE LUDOTHEQUE\n\n");
				do {
					printf("Quelle ludothèque voulez-vous afficher ?\n> ");
					scanf("%d",&choixLudo);
				} while (choixLudo != 1 && choixLudo != 2);
				choixLudo--;
				if(ludoCreee[choixLudo] == 0){
					printf("La ludothèque en question n'a pas encore été créée !\n\n");
					choix=0;
					break;
				}
				printf("\n");
				if(choixLudo == 1)
					affiche_ludotheque(ludotest);
				else
					affiche_ludotheque(ludotest2);
				choix = 0;
				printf("\n");
				break;
			case 3:
				printf("====> AJOUT DE JEU\n\n");
				do {
					printf("Quelle ludothèque voulez-vous utiliser ?\n> ");
					scanf("%d",&choixLudo);
				} while (choixLudo != 1 && choixLudo != 2);
				choixLudo--;
				if(ludoCreee[choixLudo] == 0){
					printf("La ludothèque en question n'a pas encore été créée !\n\n");
					choix=0;
					break;
				}
				jeutest1 = malloc(sizeof(t_jeu));
				nomTMP=malloc(40*sizeof(char));
				printf("Ecrivez le nom du jeu :\n> ");
				scanf("%s",nomTMP);
				printf("De quel genre est le jeu ? (0 : plateau, 1 : RPG, 2 : coopératif, 3 : ambiance, 4 : hasard)\n> ");
				scanf("%d",&genreTMP);
				printf("Combien de joueurs au minimum ?\n> ");
				scanf("%d",&minTMP);
				do {
					printf("Combien de joueurs au maximum ?\n> ");
					scanf("%d",&maxTMP);
				} while (maxTMP<minTMP);
				printf("Quelle est la durée moyenne d'une partie en minutes ?\n> ");
				scanf("%d",&dureeTMP);
				jeutest1 = creer_jeu(nomTMP, minTMP, maxTMP, genreTMP, dureeTMP);
				if(choixLudo == 1)
					ajouter_jeu(ludotest,jeutest1);
				else
					ajouter_jeu(ludotest2,jeutest1);
				choix = 0;
				printf("\n");
				break;
			case 4:
				printf("====> RECHERCHE D'ELEMENTS\n\n");
				do {
					printf("Dans quelle ludothèque voulez-vous rechercher ?\n> ");
					scanf("%d",&choixLudo);
				} while (choixLudo != 1 && choixLudo != 2);
				choixLudo--;
				if(ludoCreee[choixLudo] == 0){
					printf("La ludothèque en question n'a pas encore été créée !\n\n");
					choix=0;
					break;
				}
				printf("De quel genre doit être le jeu ? (0 : plateau, 1 : RPG, 2 : coopératif, 3 : ambiance, 4 : hasard)\n> ");
				scanf("%d",&param3);
				printf("Pour combien de joueurs doit convenir le jeu ? (tapez -1 pour négliger)\n> ");
				scanf("%d",&param1);
				printf("Pour quelle durée en minutes doit convenir ce jeu ? (tapez -1 pour négliger)\n> ");
				scanf("%d",&param2);
				if(choixLudo == 1)
					affiche_ludotheque(requete_jeu(ludotest,param3,param1,param2));
				else
					affiche_ludotheque(requete_jeu(ludotest2,param3,param1,param2));
				choix = 0;
				printf("\n");
				break;
			case 5: // doit créer une ludothèque
				printf("====> FUSION DES LUDOTHEQUES\n\nOn fusionne les deux ludothèques.\n");
				if(ludoCreee[0] == 0 || ludoCreee[1] == 0){
					printf("Impossible de fusionner tant que les 2 ludothèques n'ont pas été créées !\n\n");
					choix=0;
					break;
				}
				printf("\nLudothèque 1 :\n");
				affiche_ludotheque(ludotest);
				printf("\nLudothèque 2 :\n");
				affiche_ludotheque(ludotest2);
				printf("\nLudothèque finale :\n");
				affiche_ludotheque(fusion(ludotest,ludotest2));
				nbLudos++;
				choix = 0;
				printf("\n");
				break;
			default: // retour au menu
				printf("========> Que voulez-vous faire ?\n");
				printf("1 : Crée une ludothèque\n2 : Affiche une ludothèque\n3 : Ajoute un jeu dans la ludothèque en saisissant ses caractéristiques\n4 : Effectue une recherche de jeu à partir des critères de l'utilisateur\n5 : Crée 2 ludothèques, les affiche, les fusionne, et affiche la nouvelle ludothèque\n6 : Quitter le programme\n> ");
				scanf("%d",&choix);
				printf("\n");
				break;
			}
	}
	printf("Fin du programme.\n");
	return 0;
}
