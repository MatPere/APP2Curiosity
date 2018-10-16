#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <stdlib.h>
#ifdef NCURSES
#include <ncurses.h>
#endif
#include "listes.h"
#include "curiosity.h"

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



int interprete (sequence_t* seq, bool debug)
{
    // Version temporaire a remplacer par
    //  - une lecture des commandes dans la liste chainee
    // suivie par
    //  - une interpretation des commandes lues (partie fournie)
    char argument = 0;
    char commande = 0;


     /* debug = True À enlever par la suite et utiliser "-d" sur la ligne de commandes */

    printf ("Programme : ");
    afficher(seq);
    printf ("\n");
    if (debug) stop();
    // À partir d'ici, beaucoup de choses à modifier dans la suite.

     //à modifier: premiere commande de la sequence

    while ( seq->tete != NULL) {
        commande = seq->tete->command ;

        if ((commande>='0')&&(commande<='9')) {
          argument = commande - '0';

        } else if ((commande=='a')||(commande=='A')) {
            switch (avance()) {
                case VICTOIRE: return VICTOIRE;
                case RATE: return RATE;
                case REUSSI: break;
            }
       
          

        

        } else if ((commande=='g')||(commande=='G')) {
            gauche();
        } else if ((commande=='d')||(commande=='D')) {
            droite();
        } else if ((commande=='p')||(commande=='P')) {
            pose(argument);

        } else if ((commande=='m')||(commande=='M')) {
            argument=mesure(argument);
            printf("Résultat de la mesure : ");
            switch (argument) {
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

        seq->tete= seq->tete->suivant;
        afficherCarte();
        printf("Valeur : %d\n",argument);
        printf ("Programme : ");
        afficher(seq);
        printf ("\n");
        if (debug) stop();
    }



    /* Si on sort de la boucle sans arriver sur le @
     * c'est raté :-( */

    return CIBLERATEE;
}
