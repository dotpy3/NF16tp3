#include "tp3.c"

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
  if(ludoCreee[0] == 1)
    supprimer_ludotheque(ludotest);
  if(ludoCreee[1] == 1)
    supprimer_ludotheque(ludotest2);
  printf("Fin du programme.\n");
  return 0;
}
