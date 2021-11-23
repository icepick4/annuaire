#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fonction.c"
#define TAILLE_MAX 256
void main(){
    remplir(0,0,-1);
    int tab[7] = {25,13,2,14,36,15,1};/* initialisation du tableau de valeurs*/
    /*insertion(tab,(sizeof tab / sizeof tab[0]));*/
    char choix[TAILLE_MAX+1],choix_tri[TAILLE_MAX+1],nom[TAILLE_MAX+1],prenom[TAILLE_MAX+1],adresse[TAILLE_MAX+1],code_postale[TAILLE_MAX+1],num[TAILLE_MAX+1],mail[TAILLE_MAX+1],profession[TAILLE_MAX+1];
    debut : printf("\nChoisis une action a realiser : \n  - Ajout de client --> tapez \"ajout\" \n  - Afficher la base de donnees --> tapez \"afficher\" \n  - Supprimer un client --> tapez \"suppr\"\n");
    scanf("%s",&choix);
    if (strcmp(choix, "afficher")==0){
        /*ajouter le tri*/
        printf("Voulez vous trier l'affichage des données ? \n Si oui tapez \"\" pour ... \"\" pour ... sinon tapez \"non\"(en cours) ");
        scanf("%s",choix_tri);
        afficher(choix_tri);
    }
    else if (strcmp(choix, "ajout")==0){
        printf("Prenom : ");
        scanf("%s",&prenom);
        printf("Nom : ");
        scanf("%s",&nom);
        printf("Ville : ");
        scanf("%s",&adresse);
        scan_ajout_codepostale : printf("Code postale : ");
        scanf("%s",&code_postale);
        if (!(est_code_postal(code_postale))){
            printf("\nCode postale non valide\nNorme des codes postaux : 00000\n");
            goto scan_ajout_codepostale;
        }
        scan_ajout_num : printf("Numero de telephone : ");
        scanf("%s",&num);
        if (!(est_num(num))){
            printf("\nNumero de telephone non valide\nNorme des numeros de telephone : 00.00.00.00.00\n");
            goto scan_ajout_num;
        }
        scan_ajout_mail : printf("Adresse email : ");
        scanf("%s",&mail);
        if (!(est_mail(mail))){
            printf("\nEmail non valide\nNorme des adresses email : ---@---.---\n");
            goto scan_ajout_mail;
        }
        printf("Profession : ");
        scanf("%s",&profession);
        ajout(nom,prenom,adresse,code_postale,num,mail,profession);
        printf("Le client a bien ete ajoute\n");
        goto debut;
    }
    else if(strcmp(choix,"suppr")==0){
        char verif[TAILLE_MAX+1];
        char num[TAILLE_MAX+1],mail[TAILLE_MAX+1],nom[TAILLE_MAX+1],prenom[TAILLE_MAX+1];
        scan_nom : printf("Entrez le prenom du client a supprimer : ");
        scanf("%s",&prenom);
        printf("Entrez le nom du client a supprimer : ");
        scanf("%s",&nom);
        scan_critere : printf("Souhaitez vous entrer son email ou son numero de telephone ? \nPour l'email--> tapez \"mail\"\nPour le numero de telephone --> tapez \"tel\"\n");
        scanf("%s",&verif);
        if (strcmp(verif,"mail")==0){
            scanmail : printf("Entrez le mail du client a supprimer : ");
            scanf("%s",&mail);
            if (est_mail(mail)){
                trouver(prenom,nom,"0",mail,1);
                goto debut;
            }
            else{
                printf("\nEmail non valide\nNorme des adresses email : ---@---.---\n");
                goto scanmail;
            }
        }
        else if (strcmp(verif,"tel")==0){
            scannum : printf("Entrez le numero de telephone du client a supprimer : ");
            scanf("%s",&num);
            if (est_num(num)){
                trouver(prenom,nom,num,"0",1);
                goto debut;
            }
            else{
                printf("\nNumero de telephone non valide\nNorme des numeros de telephone : 00.00.00.00.00\n");
                goto scannum;
            }
        }
        else{
            printf("\nErreur dans la selection\n");
            goto scan_critere;
        }
    }
    else if(strcmp(choix,"stop")==0){
    }
    else{
        goto debut;
    }
}








