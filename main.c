#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fonction.h"
#define TAILLE_MAX 256
#define MAXTAB 100000

int main(void){
    printf("binz");
    remplir(0,0,tableau);
    int tab[7] = {25,13,2,14,36,15,1};/* initialisation du tableau de valeurs*/
    /*insertion(tab,(sizeof tab / sizeof tab[0]));*/
    char choix[TAILLE_MAX+1],choix_tri[TAILLE_MAX+1],choix_affiche[TAILLE_MAX+1], choixchoix_filtre[TAILLE_MAX+1],choix_filtre[TAILLE_MAX+1],filtre[TAILLE_MAX+1],nom[TAILLE_MAX+1],prenom[TAILLE_MAX+1],adresse[TAILLE_MAX+1],code_postale[TAILLE_MAX+1],num[TAILLE_MAX+1],mail[TAILLE_MAX+1],profession[TAILLE_MAX+1];
    debut : printf("\nChoisis une action a realiser : \n  - Ajout de client --> tapez \"ajout\" \n  - Afficher la base de donnees --> tapez \"afficher\" \n  - Supprimer un client --> tapez \"suppr\"\n  - Rechercher un client --> tapez \"recherche\"\n  - Afficher tous les clients auquels il manque un ou plusieurs champ(s) --> tapez \"manquant\" \n ");
    scanf("%s",&choix);
    if (strcmp(choix, "afficher")==0){
        /*ajouter le tri*/
        printf("Voulez vous afficher les donnees avec un filtre ou un tri ? \n  - Pour un filtre --> tapez \"filtre\" \n  - Pour un tri --> tapez \"tri\" \n  - Si vous voulez uniquement afficher la base de donnees --> tapez \"non\" \n");
        scanf("%s",choix_affiche);
        if (strcmp(choix_affiche,"tri")==0){
            /*choisir le tri voulu*/
        }
        else if (strcmp(choix_affiche,"filtre")==0){
            choixchoixfiltre : printf("Voulez vous filtrer avec la premiere lettre ou un champ precis ?\n  - Pour une seule lettre --> tapez \"oui\" \n  - Pour un champ precis --> tapez \"non\"\n");
            scanf("%s",&choixchoix_filtre);
            if (strcmp(choixchoix_filtre,"oui")!=0&&strcmp(choixchoix_filtre,"non")!=0){
                printf("\nErreur de selection\n");
                goto choixchoixfiltre;
            }

            choixchampfiltre : printf("Par quel champ voulez vous filtrer ? \n  - Pour un filtre par prenom --> tapez \"prenom\" \n  - Pour un filtre par nom --> tapez \"nom\" \n  - Pour un filtre par profession --> tapez \"profession\"\n  - Pour un filtre par code postale --> tapez \"code_postale\" \n");
            scanf("%s",&choix_filtre);
            if (strcmp(choix_filtre,"prenom")!=0&&strcmp(choix_filtre,"nom")!=0&&strcmp(choix_filtre,"profession")!=0&&strcmp(choix_filtre,"code_postale")!=0){
                printf("\nErreur de selection de filtre\n");
                goto choixchampfiltre;
            }
            choixfiltre : printf("Indiquez le filtre que vous souhaitez appliquer : ");
            scanf("%s",&filtre);
            if (strcmp(choix_filtre,"code_postale")==0&&strcmp(choixchoix_filtre,"oui")!=0){
                if (est_code_postal(filtre)){
                    filtre_code_postale(filtre);
                    goto debut;
                }
                else{
                    printf("\nCode postale non valide\nNorme des codes postaux : 00000\n");
                    goto choixfiltre;
                }
            }
            else if (strcmp(choix_filtre,"prenom")==0){
                filtre_prenom(filtre,choixchoix_filtre);
                goto debut;
            }
            else if (strcmp(choix_filtre,"nom")==0){
                filtre_nom(filtre,choixchoix_filtre);
                goto debut;
            }
            else if (strcmp(choix_filtre,"profession")==0){
                filtre_profession(filtre,choixchoix_filtre);
                goto debut;
            }

        }
        else{
            afficher(choix_tri);
            goto debut;
        }

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
        printf("Entrez le prenom du client a supprimer : ");
        scanf("%s",&prenom);
        printf("Entrez le nom du client a supprimer : ");
        scanf("%s",&nom);
        scan_critere_suppr : printf("Souhaitez vous entrer son email ou son numero de telephone ? \nPour l'email--> tapez \"mail\"\nPour le numero de telephone --> tapez \"tel\"\n");
        scanf("%s",&verif);
        if (strcmp(verif,"mail")==0){
            scanmail_suppr : printf("Entrez le mail du client a supprimer : ");
            scanf("%s",&mail);
            if (est_mail(mail)){
                trouver(prenom,nom,"0",mail,1);
                goto debut;
            }
            else{
                printf("\nEmail non valide\nNorme des adresses email : ---@---.---\n");
                goto scanmail_suppr;
            }
        }
        else if (strcmp(verif,"tel")==0){
            scannum_suppr : printf("Entrez le numero de telephone du client a supprimer : ");
            scanf("%s",&num);
            if (est_num(num)){
                trouver(prenom,nom,num,"0",1);
                goto debut;
            }
            else{
                printf("\nNumero de telephone non valide\nNorme des numeros de telephone : 00.00.00.00.00\n");
                goto scannum_suppr;
            }
        }
        else{
            printf("\nErreur dans la selection\n");
            goto scan_critere_suppr;
        }
    }
    else if(strcmp(choix,"stop")==0){
    }
    else if (strcmp(choix,"recherche")==0){
        char verif[TAILLE_MAX+1];
        char num[TAILLE_MAX+1],mail[TAILLE_MAX+1],nom[TAILLE_MAX+1],prenom[TAILLE_MAX+1];
        printf("Entrez le prenom du client que vous cherchez : ");
        scanf("%s",&prenom);
        printf("Entrez le nom du client que vous cherchez : ");
        scanf("%s",&nom);
        scan_critere : printf("Souhaitez vous entrer son email ou son numero de telephone ? \nPour l'email--> tapez \"mail\"\nPour le numero de telephone --> tapez \"tel\"\n");
        scanf("%s",&verif);
        if (strcmp(verif,"mail")==0){
            scanmail : printf("Entrez le mail du client que vous cherchez : ");
            scanf("%s",&mail);
            if (est_mail(mail)){
                trouver(prenom,nom,"0",mail,0);
                goto debut;
            }
            else{
                printf("\nEmail non valide\nNorme des adresses email : ---@---.---\n");
                goto scanmail;
            }
        }
        else if (strcmp(verif,"tel")==0){
            scannum : printf("Entrez le numero de telephone du client que vous cherchez: ");
            scanf("%s",&num);
            if (est_num(num)){
                trouver(prenom,nom,num,"0",0);
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
    else if (strcmp(choix,"manquant")==0){
        afficher("manquant");
        goto debut;
    }
    else{
        goto debut;
    }
    return 0;
}








