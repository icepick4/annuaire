#include <stdio.h>
#include <stdlib.h>
#include "fonction.c"
#define TAILLE_MAX 256
int main(){
    int tab[7] = {25,13,2,14,36,15,1};/* initialisation du tableau de valeurs*/
    insertion(tab,(sizeof tab / sizeof tab[0]));
    return 0;
}


