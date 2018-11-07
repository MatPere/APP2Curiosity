#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <stdlib.h>
#ifdef NCURSES
#include <ncurses.h>
#endif
#include "listes.h"
#include "curiosity.h"
#include <ctype.h>


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

void traiter_condition(sequence_t *seq, int n, cellule_t *courant){
	int profondeur =1;
	if (n!=0){
		courant = courant -> suivant;
		while (profondeur != 0){
			if (courant->command == '{') {
				profondeur++;
			}
			if (courant->command == '}') {
				profondeur--;
			}
			courant = traiter(&seq,&courant);
			courant = courant -> suivant;
		}
		while (courant->command != '?'){
			courant = courant->suivant;
		}
		courant= courant->suivant;

	}else if (n==0){
		courant = courant -> suivant;
		while (profondeur !=0){
			if (courant->command == '{') {
				profondeur++;
			}
			if (courant->command == '}') {
				profondeur--;
			}
			courant = courant -> suivant;
		}
		profondeur = 1;
		while (profondeur !=0){
			if (courant->command == '{') {
				profondeur++;
			}
			if (courant->command == '}') {
				profondeur--;
			}
			courant = traiter(&seq,&courant);
			courant = courant -> suivant;
		}
		courant = courant -> suivant;
	}
}

int interprete (sequence_t* seq){
	bool debug = true;
	printf ("Programme:");
	cellule_t* courant;
	courant = seq -> tete;
	while (courant->command != NULL){
		afficher(seq);
    		printf ("\n");
    		if (debug) stop();
		courant = traiter(&seq,&courant);
	}
	return CIBLERATEE;
}

cellule_t* traiter (*seq,*courant){
    char commande = 0;
    commande = courant->command ; //à modifier: premiere commande de la sequence
    int num;
    while (commande) {

        if ((commande=='a')||(commande=='A')) {
            switch (avance()) {
                case VICTOIRE: return VICTOIRE;
                case RATE: return RATE;
                case REUSSI: break;
            }
		
	}else if (isdigit(commande)){
		num=commande-'0';
	} else if ((commande == 'P') || (commande == 'p')){
		pose(num);
	}else if ((commande == 'M') || (commande == 'm')){
		num=mesure(num);
		switch (num){
			case 0 : { printf("Il n'y a rien la..."); break;}
			case 1 : {printf("Oh, une marque posee par Curiosity !"); break;}
			case 2 : {printf("Il y a de l'eau, je ne sais pas nager..."); break;}
			case 3 : {printf("C'est un rocher."); break;}
		}
        } else if ((commande=='g')||(commande=='G')) {
            gauche();
        } else if ((commande=='d')||(commande=='D')) {
            droite();
	}else if (commande == '{'){
	    traiter_condition(&seq,num,&courant);
        } else {
            printf ("Commande inconnue: %c\n", commande);
        }

	courant =  courant->suivant;
        commande = courant->command ; //commande suivante dans la sequence
	seq->tete = courant;

        afficherCarte();
        printf ("Programme:");
        afficher(seq);
        printf ("\n");
	return courant;
    }

    /* Si on sort de la boucle sans arriver sur le @
     * c'est raté :-( */

}







