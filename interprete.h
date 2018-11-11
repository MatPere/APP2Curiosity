#ifndef INTERPRETE_H
#define INTERPRETE_H
cellule_t * traiter(cellule_t * act, int *n, int *fin, bool debug) ;
int interprete (sequence_t* seq, bool debug);
cellule_t * traiter_boucle(cellule_t * act, int *n, int *fin, bool debug);
cellule_t * traiter_condition(cellule_t * act, int *n, int *fin, bool debug);
cellule_t * condition_ou_boucle(cellule_t * act, int *n, int *fin, bool debug);

#endif
