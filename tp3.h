#include <stdio.h>
#include <stdlib.h>

/* DEFINITION TYPES ET ENUMS */

typedef enum genre_jeu { PLATEAU, RPG, COOPERATIF, AMBIANCE, HASARD } genre_jeu;

typedef struct jeu t_jeu;
struct jeu {
	char *nom;
	genre_jeu genre;
	int nbJoueurMin;
	int nbJoueurMax;
	int duree;
	struct jeu *suivant;
};

typedef struct ludotheque {
	int nb_jeu;
	t_jeu *debut;
} t_ludotheque;

/* PROTOTYPES DE FONCTIONS */

t_ludotheque* creer_ludotheque();
t_jeu* creer_jeu(char *nom, int nbJoueurMin, int nbJoueurMax, genre_jeu genre, int duree);
int triAlphabetique(char *c1, char *c2);
int ajouter_jeu(t_ludotheque *ludo, t_jeu *j);
int retirer_jeu(t_ludotheque *ludo, char *nom);
void supprimer_ludotheque(t_ludotheque *ludo);
void affiche_ludotheque(t_ludotheque *ludo);
t_ludotheque* requete_jeu(t_ludotheque *ludo, genre_jeu genre, int nbJoueurs, int duree);
int doublons(t_jeu *j, t_ludotheque *ludo);
t_ludotheque* fusion(t_ludotheque *ludo1, t_ludotheque *ludo2);
void triLudo(t_ludotheque *ludo, int tri);
