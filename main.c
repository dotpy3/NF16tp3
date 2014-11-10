#include "tp3.c"

int main() {
  t_ludotheque *ludotest,*ludotest2;
  t_jeu *jeutest1;
  int choixtri = 0, choix = 0, choixLudo = 0, choixLudo2 = 0, genreTMP, minTMP, maxTMP, dureeTMP, ludoCreee[2];
  ludoCreee[0]=0;
  ludoCreee[1]=0;
  int param1, param2, param3; //param1 : nbJoueurs, param2 : duree, param3 : genre
  char *nomTMP;

    /*
      L'entier choix determine ce qui doit se passer dans la boucle.
      0 : doit afficher le menu
      1 : doit creer une ludotheque
      2 : doit afficher une ludotheque
      3 : Demande le tri et l'affichage d'une ludotheque pour les differents champs
      (par nom, par nombre de joueur minimum, par genre, par duree)
      4 : ajoute un jeu dans la ludotheque en saisissant ses caracteristiques
      5 : effectue une recherche de jeu a partir des criteres de l'utilisateur
      6 : Cree 2 ludotheques, les affiche, les fusionne, et affiche la nouvelle ludotheque
      7 : doit quitter
    */

  while (choix != 7) {
    switch(choix) {
      case 1: // doit creer une ludotheque
        printf("====> CREATION DE LUDOTHEQUE\n\nSi la ludotheque existe deja, elle sera remplacee.\nQuelle ludotheque voulez-vous creer ? (1/2)\n> ");
        scanf("%d",&choixLudo);
        if(choixLudo == 1)
          {ludotest = creer_ludotheque();
          ludoCreee[0] = 1;}
        else if(choixLudo == 2)
          {ludotest2 = creer_ludotheque();
          ludoCreee[1] = 1;}
        choix=0;
        printf("\n");
        break;
      case 2:
        printf("====> AFFICHAGE DE LUDOTHEQUE\n\n");
        do {
          printf("Quelle ludotheque voulez-vous afficher ?\n> ");
          scanf("%d",&choixLudo);
        } while (choixLudo != 1 && choixLudo != 2);
        choixLudo--;
        if(ludoCreee[choixLudo] == 0){
          printf("La ludotheque en question n'a pas encore ete creee !\n\n");
          choix=0;
          break;
        }
        printf("\n");
        if(choixLudo == 0)
          affiche_ludotheque(ludotest);
        else if (choixLudo == 1)
          affiche_ludotheque(ludotest2);
        choix = 0;
        printf("\n");
        break;
      case 3:
        printf("====> AJOUT DE JEU\n\n");
        do {
          printf("Quelle ludotheque voulez-vous utiliser ?\n> ");
          scanf("%d",&choixLudo);
        } while (choixLudo != 1 && choixLudo != 2);
        choixLudo--;
        if(ludoCreee[choixLudo] == 0){
          printf("La ludotheque en question n'a pas encore ete creee !\n\n");
          choix=0;
          break;
        }
        jeutest1 = malloc(sizeof(t_jeu));
        nomTMP=malloc(40*sizeof(char));
        printf("Ecrivez le nom du jeu :\n> ");
        scanf("%s",nomTMP);
        printf("De quel genre est le jeu ? (0 : plateau, 1 : RPG, 2 : cooperatif, 3 : ambiance, 4 : hasard)\n> ");
        scanf("%d",&genreTMP);
        do { printf("Combien de joueurs au minimum ? (doit etre superieur ou egal a 0)\n> ");
        scanf("%d",&minTMP); } while (minTMP < 0);
        do {
          printf("Combien de joueurs au maximum ?\n> ");
          scanf("%d",&maxTMP);
        } while (maxTMP<minTMP);
        printf("Quelle est la duree moyenne d'une partie en minutes ?\n> ");
        scanf("%d",&dureeTMP);
        jeutest1 = creer_jeu(nomTMP, minTMP, maxTMP, genreTMP, dureeTMP);
        if(choixLudo == 0)
          ajouter_jeu(ludotest,jeutest1);
        else if (choixLudo == 1)
          ajouter_jeu(ludotest2,jeutest1);
        choix = 0;
        printf("\n");
        break;
      case 4:
        printf("====> RECHERCHE D'ELEMENTS\n\n");
        do {
          printf("Dans quelle ludotheque voulez-vous rechercher ?\n> ");
          scanf("%d",&choixLudo);
        } while (choixLudo != 1 && choixLudo != 2);
        choixLudo--;
        if(ludoCreee[choixLudo] == 0){
          printf("La ludotheque en question n'a pas encore ete creee !\n\n");
          choix=0;
          break;
        }
        printf("De quel genre doit etre le jeu ? (0 : plateau, 1 : RPG, 2 : cooperatif, 3 : ambiance, 4 : hasard)\n> ");
        scanf("%d",&param3);
        printf("Pour combien de joueurs doit convenir le jeu ? (tapez -1 pour negliger)\n> ");
        scanf("%d",&param1);
        printf("Pour quelle duree en minutes doit convenir ce jeu ? (tapez -1 pour negliger)\n> ");
        scanf("%d",&param2);
        if(choixLudo == 0)
          affiche_ludotheque(requete_jeu(ludotest,param3,param1,param2));
        else if(choixLudo == 1)
          affiche_ludotheque(requete_jeu(ludotest2,param3,param1,param2));
        choix = 0;
        printf("\n");
        break;
      case 5: // doit creer une ludotheque
        printf("====> FUSION DES LUDOTHEQUES\n\nOn fusionne les deux ludotheques.\n");
        if(ludoCreee[0] == 0 || ludoCreee[1] == 0){
          printf("Impossible de fusionner tant que les 2 ludotheques n'ont pas ete creees !\n\n");
          choix=0;
          break;
        }
        printf("\nLudotheque 1 :\n");
        affiche_ludotheque(ludotest);
        printf("\nLudotheque 2 :\n");
        affiche_ludotheque(ludotest2);
        printf("\nLudotheque finale :\n");
        affiche_ludotheque(fusion(ludotest,ludotest2));
        choix = 0;
        printf("\n");
        break;
      case 6:
        printf("====> SUPPRESSION D'UN ELEMENT\n\n");
        do {
          printf("Dans quelle ludotheque voulez-vous supprimer un element ?\n> ");
          scanf("%d",&choixLudo);
        } while (choixLudo != 1 && choixLudo != 2);
        choixLudo--;
        if(ludoCreee[choixLudo] == 0){
          printf("La ludotheque en question n'a pas encore ete creee !\n\n");
          choix=0;
          break;
        }
        nomTMP=malloc(40*sizeof(char));
        printf("Ecrivez le nom du jeu :\n> ");
        scanf("%s",nomTMP);
        if(choixLudo == 0){
        if(retirer_jeu(ludotest,nomTMP) == 1)
            printf("Suppression de l'element reussie.\n");
        else
            printf("La suppression de l'element a echoue !\n");
        } else if (choixLudo == 1) {
            if(retirer_jeu(ludotest2,nomTMP) == 1)
            printf("Suppression de l'element reussie.\n");
        else
            printf("La suppression de l'element a echoue !\n");
        }
        choix = 0;
        printf("\n");
        break;
      default: // retour au menu
        printf("========> Que voulez-vous faire ? <========\n");
        printf("\t1 : Cree une ludotheque\n\t2 : Affiche une ludotheque\n\t3 : Ajoute un jeu dans la ludotheque en saisissant ses caracteristiques\n\t4 : Effectue une recherche de jeu a partir de criteres donnes\n\t5 : Affiche les ludotheques, les fusionne, et affiche la nouvelle\n\t6 : Supprime un element d'une ludotheque\n\t7 : Quitter le programme\n> ");
        scanf("%d",&choix);
        printf("\n");
        break;
      }
  }
  if(ludoCreee[0] == 1)
    supprimer_ludotheque(ludotest);
  if(ludoCreee[1] == 1)
    supprimer_ludotheque(ludotest2);
  printf("Fin du programme.\n");
  return 0;
}
