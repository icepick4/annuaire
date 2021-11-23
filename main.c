#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fonction.c"
#define TAILLE_MAX 256

int main(){
    int tab[7] = {25,13,2,14,36,15,1};/* initialisation du tableau de valeurs*/
    /*insertion(tab,(sizeof tab / sizeof tab[0]));*/
    char choix[TAILLE_MAX+1],nom[TAILLE_MAX+1],prenom[TAILLE_MAX+1],adresse[TAILLE_MAX+1],code_postale[TAILLE_MAX+1],num[TAILLE_MAX+1],mail[TAILLE_MAX+1],profession[TAILLE_MAX+1];
    printf("Choisi une action à réaliser : Ajout de client (\"ajout\"), Afficher la base de données (\"afficher\"), Supprimer un client (\"suppr\")");
    scanf("%s",&choix);
    if (strcmp(choix, "afficher")==0){
        /*ajouter le tri*/
        afficher();
    }
    else if (strcmp(choix, "ajout")==0){
            scanf("%s%s%s%s%s%s%s",&nom,&prenom,&adresse,&code_postale,&num,&mail,&profession);
            int i;
            ajout(nom,prenom,adresse,code_postale,num,mail,profession);
    }
    else if(strcmp(choix,"suppr")==0){
        scan_num : printf("Entrez le numéro de téléphone du client à supprimer");
        char num[TAILLE_MAX+1];
        scanf("%s",&num);
        if(est_num(num)){
            suppr(num);
        }
        else{
            goto scan_num;
        }
    }

    return EXIT_SUCCESS;
}








