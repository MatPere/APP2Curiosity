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

void stop(void)
{
#ifdef NCURSES
    getch();  /* attente appui sur touche */
#else
    char enter = '\0';
    printf ("Appuyer sur entrée pour continuer...\n");
    while (enter != '\r' && enter != '\n') { enter = getchar(); }
#endif
}




int isvictoire(int* vic){
  return *vic!=999 ;
}
void traiter_condition(cellule_t ** courant, int* globale, int* victoire){
  *courant=(**courant).suivant;
  int profondeur = 1;
  if (*globale==0){

    while (profondeur > 0) {
      if ((**courant).command=='{') profondeur++;
      if ((**courant).command=='}') profondeur--;
      *courant=(**courant).suivant;
    }
    *courant=(**courant).suivant;
    while((**courant).command != '?'){
      traiter(courant,globale, victoire);
      if (isvictoire(victoire)) return;
    }

  }
  if (*globale!=0){
    while((**courant).command != '}'){
      traiter(courant,globale, victoire);
      if (isvictoire(victoire)) return;
    }
    while (profondeur > 0) {
      if ((**courant).command=='{') profondeur++;
      if ((**courant).command=='}') profondeur--;
      *courant=(**courant).suivant;
    }
    traiter(courant,globale, victoire);
      if (isvictoire(victoire)) return;
    

  }
} 


int interprete (sequence_t* seq, bool debug)
{
    int globale = 0;
    printf ("Programme : ");
    afficher(seq);
    printf ("\n");
    //if (debug) stop();
    
    
    int victoire = 999;
    cellule_t * p = seq->tete;
    cellule_t ** pointeur;
    *pointeur = p;
    while ( pointeur != NULL && *pointeur != NULL) {
      traiter(pointeur, &globale, &victoire);
      printf("Viktoir ! ! ! ! : %d \n", victoire);
      switch (victoire) {
            case VICTOIRE: return VICTOIRE;
            case RATE: return RATE;
            case REUSSI : break;
            default : break;
      
      //if (debug) stop();

      }
    }
    return CIBLERATEE;
    
  
}
void traiter(cellule_t ** point, int *globale, int* victoire){
    
    //printf("########### %c ############\n", (**point).command);
     /* debug = True À enlever par la suite et utiliser "-d" sur la ligne de commandes */
    if (point==NULL) {} 
    else {
      if (*point==NULL) {*victoire=CIBLERATEE;} 
      
      
        
      
      // À partir d'ici, beaucoup de choses à modifier dans la suite.

      //à modifier: premiere commande de la sequence

      
      if (((**point).command>='0')&&((**point).command<='9')) {
        *globale = (**point).command - '0';
        

      } else if (((**point).command=='a')||((**point).command=='A')) {
          //printf("On avance  ###################>");
          switch (avance()) {
              case VICTOIRE: 
                *victoire = VICTOIRE;
                break;
              case RATE: 
                *victoire = RATE;
                break;
              case REUSSI: 
                *victoire = REUSSI;
                break;
          }
      } else if ((**point).command=='{') {
          traiter_condition(point, globale, victoire);
      } else if (((**point).command=='g')||((**point).command=='G')) {
          gauche();
      } else if (((**point).command=='d')||((**point).command=='D')) {
          droite();
      } else if (((**point).command=='p')||((**point).command=='P')) {
          pose(*globale);

      } else if (((**point).command=='m')||((**point).command=='M')) {
          *globale=mesure(*globale);
          printf("Résultat de la mesure : ");
          switch (*globale) {
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


      } else if (((**point).command=='}')||((**point).command=='?')||((**point).command==']')){}
      else {
          printf ("commande inconnue: %c\n", (**point).command);
      }
      
      afficherCarte();
      printf("Valeur : %d\n",*globale);
      printf ("Programme : ");
      sequence_t seq ;
      seq.tete = *point ;

      afficher(&seq);
      printf ("\n");

      printf("!!!1 point = %c\n", (**point).command);
      *point=(**point).suivant ;
      //if (*point!=NULL){
      //  printf("!!!2 point = %c\n", (**point).command);
      //} 
    }  
    return;
}

/* Si on sort de la boucle sans arriver sur le @
   c'est raté :-( */



