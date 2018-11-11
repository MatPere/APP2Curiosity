#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <stdlib.h>
#ifdef NCURSES
#include <ncurses.h>
#endif
#include "listes.h"
#include "curiosity.h"
#include "interprete.h"

/*
 *  Auteur(s) :
 *  Date :
 *  Suivi des Modifications :
 *
 */

void stop (void)
{
#ifdef NCURSES
    getch();  /* attente appui sur touche */
#else
    char enter = '\0';
    printf ("Appuyer sur entrée pour continuer...\n");
    while (enter != '\r' && enter != '\n') { enter = getchar(); }
#endif
}

cellule_t * condition_ou_boucle(cellule_t * act, int *n, int *fin, bool debug){
  int profondeur = 1 ;


  cellule_t * debut = act ;
  act = act->suivant;
  while (profondeur > 0) {
    if (act->command=='{') profondeur++;
    if (act->command=='}') profondeur--;
    act=act->suivant;
  }
  if (act->command=='{') return traiter_condition(debut, n, fin, debug) ;
  else return traiter_boucle(debut, n ,fin, debug);

}


cellule_t * traiter_boucle(cellule_t * act, int *n, int *fin, bool debug) {

  int profondeur = 1 ;
  int iter ;
  act = act->suivant;
  cellule_t * debut = act ;
  while (profondeur > 0) {
    if (act->command=='{') profondeur++;
    if (act->command=='}') profondeur--;
    act=act->suivant;
  }
  iter = act->suivant->command ;
  for (int i=0; i<iter; i++){
    act=debut;
    while (act->command!='}'){
      act = traiter(act, n, fin, debug) ;
      if (act == NULL) return NULL ;
    }
  }
  return act->suivant->suivant->suivant ;
}

cellule_t * traiter_condition(cellule_t * act, int *n, int *fin, bool debug){
  act = act->suivant;
  int profondeur = 1 ;
  if (*n==0){
    while (profondeur > 0) {
      if (act->command=='{') profondeur++;
      if (act->command=='}') profondeur--;
      act=act->suivant;
    }
    act=act->suivant ;
    while (act->command!='?') {
      act = traiter(act, n, fin, debug) ;
      if (act == NULL) return NULL ;

    }
    return act->suivant;


 } else {


   while (act->command!='}') {
     act = traiter(act, n, fin, debug) ;
     if (act == NULL) return NULL ;

   }

   act=act->suivant->suivant ;


   while (profondeur > 0) {
     if (act->command=='{') profondeur++;
     if (act->command=='}') profondeur--;
     act=act->suivant;
   }
   return act->suivant;
 }
}




cellule_t * traiter(cellule_t *act, int * n, int * fin, bool debug){
  if (act==NULL && *fin==-1) *fin = CIBLERATEE ;
  if (act==NULL) return NULL ;
  if (*fin != -1) return NULL ;
  else {
    char commande = act->command ;

    if ((commande>='0')&&(commande<='9')) {
      *n = commande - '0';

    } else if ((commande=='a')||(commande=='A')) {
        switch (avance()) {
            case VICTOIRE: *fin = VICTOIRE; return NULL ;
            case RATE: *fin = RATE; return NULL ;
            case REUSSI: break;
        }
    } else if (commande=='{') {
        return condition_ou_boucle(act, n, fin, debug);
    } else if ((commande=='g')||(commande=='G')) {
        gauche();
    } else if ((commande=='d')||(commande=='D')) {
        droite();
    } else if ((commande=='p')||(commande=='P')) {
        pose(*n);
    } else if ((commande=='B')||(commande=='}')||(commande=='?')) {
        //rien

    } else if ((commande=='m')||(commande=='M')) {
        *n=mesure(*n);
        printf("Résultat de la mesure : ");
        switch (*n) {
          case 0 : {
            printf("rien\n" );
            break ;
          }
          case 1 : {
            printf("marque\n" );
            break ;
          }
          case 2 : {
            printf("eau\n" );
            break ;
          }
          case 3 : {
            printf("rocher\n" );
            break ;
          }
        }


    } else {
        printf ("Commande inconnue: %c\n", commande);
    }


    afficherCarte();
    printf("Valeur : %d\n",*n);
    printf ("Programme : ");
    sequence_t seq;
    seq.tete = act ;
    afficher(&seq);
    printf ("\n");
    return act->suivant;
    if (debug) stop();
  }
}

int interprete (sequence_t* seq, bool debug)
{

    int n = 0;
    cellule_t * act = seq ->tete ;
    int fin =-1 ; //Variable qui transporte l'information de victoire




    printf ("Programme : ");
    afficher(seq);
    printf ("\n");
    if (debug) stop();


    while ( act != NULL) {
      act = traiter(act, &n, &fin, debug);
      if (fin != -1) return fin ;
    }
    return CIBLERATEE;
}
