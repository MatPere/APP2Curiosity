int boucle(cellule_t *courant)
{
    sequence_t seq;
    seq.tete=courant;
    int cpt;
    while (courant != ']'){
      courant=courant->suivant;
      courant=traiter(courant);
    }
    cpt=courant->suivant->command;
    cpt=courant->command - '0';
    while (cpt>0){
      courant=seq.tete;
      while (courant != ']'){
        courant=courant->suivant;
	courant=traiter(courant);
      }
      cpt--;
    }
    return courant->suivant;
}

