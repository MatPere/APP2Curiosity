#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#ifdef NCURSES
#include <ncurses.h>
#endif
#include "listes.h"

/*
 *  Auteur(s) :
 *  Date :
 *  Suivi des Modifications :
 *
 */


void ajout_tete(char car, sequence_t *seq){
  cellule_t *elem = nouvelleCellule();
  elem->command = car;
  elem->suivant = (seq->tete);
  seq->tete = elem;
}

void conversion (char *texte, sequence_t *seq)
{
  int longueur ;
  for ( longueur = 0 ; texte[longueur]!=0 ; longueur++);
  int j = longueur-1 ;
  while (  j>=0 ){
    while ((texte[j] == ' ')&&(j>=0)) j--;
    if (j >= 0) ajout_tete(texte[j], seq);
    j--;
  }



}






void afficher (sequence_t* seq)
{
    cellule_t * point = (seq -> tete);
    while (point != NULL){
      printf("%c ",point->command );
      point = (point->suivant);
    }
    printf("\n" );
}

cellule_t* nouvelleCellule (void)
{
    cellule_t* elem = (cellule_t *) malloc(sizeof(cellule_t));
    return elem ;
}


void detruireCellule (cellule_t* cel)
{
    free(cel);
}
