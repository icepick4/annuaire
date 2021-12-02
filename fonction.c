#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fonction.h"
#include <ctype.h>
#define TAILLE_MAX 256
#define chemin "annuaire5000_test.csv"
#define nouveau_chemin "annuaire5000_test_nouveau.csv"
#define MAXTAB 100000
char choix[TAILLE_MAX+1],choix_tri[TAILLE_MAX+1],choix_affiche[TAILLE_MAX+1],
choixchoix_filtre[TAILLE_MAX+1],choix_filtre[TAILLE_MAX+1],filtre[TAILLE_MAX+1],
choix_affichage[TAILLE_MAX+1],ligne[TAILLE_MAX+1]; /*initialisation des variables chaine de caractères*/
char * champ[8] = {"Id : ","Prenom : ","Nom : ","Adresse : ","Code Postale : ","Numero de telephone : ","Adresse Mail : ","Profession : "}; /*initialisation des champs d'un client*/
const char *sep = ",";
char *token; /*initialisation du token et du separateur*/
sclient tableau[MAXTAB];
void remplir(int modifier, int supprimer,sclient *client){ /*Fonction faite par Rémi JARA*/
    FILE *fichier= fopen(chemin,"a+"); /*On ouvre le fichier csv*/
    int i=0; /* compteur qui correspond à l'id d'un client*/
    if (modifier == 0 && supprimer == 0){
        if (fichier == NULL)
        {
            printf("Erreur de lecture du fichier\n"); /*vérification qu'il n'y a aucune erreur avec le fichier*/
            exit(EXIT_FAILURE);
        }
        while(fgets(ligne,TAILLE_MAX+1,fichier)){/* on récupère chaque ligne du fichier dans la variable ligne*/
            char * token = strtok_empty(ligne, "," ); /*on sépare chaque champ de la ligne avec le séparateur "," pour les récupérer dans la variable token*/
            int j = 0; /*compteur qui correspond à l'indice du champ actuel, respectivement : prenom, nom, adresse, code postale, numéro de tel, mail, metier*/
            while (token){ /*on boucle tant que le token n'est pas vide*/
                /*condition permettant de remplir le bon attribut de la structure client passé en argument*/
                if (j==0){
                    if (strlen(token)>0){/*si le token est vide, on remplit avec une chaine permettant de le savoir par la suite*/
                        client[i].prenom = copie(token);
                    }
                    else{
                        client[i].prenom = copie("*Champ vide*");
                    }
                }
                else if (j==1){
                    if (strlen(token)>0){
                        client[i].nom = copie(token);
                    }
                    else{
                        client[i].nom = copie("*Champ vide*");
                    }
                }
                else if (j==2){
                    if (strlen(token)>0){
                        client[i].adresse = copie(token);
                    }
                    else{
                        client[i].adresse = copie("*Champ vide*");
                    }
                }
                else if (j==3){
                    if (strlen(token)>0){
                        client[i].code_postale = copie(token);
                    }
                    else{
                        client[i].code_postale = copie("*Champ vide*");
                    }
                }
                else if (j==4){
                    if (strlen(token)>0){
                        client[i].num = copie(token);
                    }
                    else{
                        client[i].num = copie("*Champ vide*");
                    }
                }
                else if (j==5){
                    if (strlen(token)>0){
                        client[i].mail = copie(token);
                    }
                    else{
                        client[i].mail = copie("*Champ vide*");
                    }
                }
                else if (j==6){/*pour le métier, on s'assure que s'il est vide, son dernier caractères devienne un '\0'*/
                    if (token[strlen(token)-1]=='\n'){
                        token[strlen(token)-1]='\0';
                    }
                    if (strlen(token)>0){
                        client[i].profession = copie(token);
                    }
                    else{
                        client[i].profession = copie("*Champ vide*");
                    }
                }
                j++;/*on incrémente de 1 a chaque token récupéré*/
                token = strtok_empty (NULL,",");
            }
            client[i].deleted = copie("ok"); /*remplissage de l'id du client et de son état de suppression*/
            client[i].id = i+1;
            i++;
        }
        tableau[i].prenom=NULL; /*on attribut au dernier client (inexistant) un prenom null pour s'en servir plus tard en tant que condition*/
        fclose(fichier);/*on ferme notre fichier il est désormais rempli*/
    }
}
char *copie(char *str){
    int len_str = strlen(str) + 1;
    char *copie = malloc(len_str);
    if(copie)
    {
        strcpy(copie, str);
    }
    return copie;
}
char * strtok_empty (char * str, char const * sep){ /*Fonction trouvé sur internet*/
    static char  * src = NULL;
    char  *  p,  * ret = 0;

    if (str != NULL)
    src = str;

    if (src == NULL)
    return NULL;

    if ((p = strpbrk (src, sep)) != NULL) {
    *p  = 0;
    ret = src;
    src = ++p;
    }
    else if (*src) {
        ret = src;
        src = NULL;
    }
    return ret;
}
void ajout(){ /*Fonction faite par Rémi JARA*/
    int i,j;
    for (i=0;tableau[i].prenom!=NULL;){
        i++;                                /*boucle for permettant de trouver le nombre de client dans le tableau*/
    }
    char nom[TAILLE_MAX+1],prenom[TAILLE_MAX+1]={"vide"},adresse[TAILLE_MAX+1]={0}, /*initialisation des variables que l'on va ajouter*/
    code_postale[TAILLE_MAX+1],num[TAILLE_MAX+1],mail[TAILLE_MAX+1],profession[TAILLE_MAX+1]={"vide"};
    do{
        if(strcmp(prenom,"vide")!=0)printf("Prenom : ");
        fgets(prenom,TAILLE_MAX+1,stdin);
    }while(!(est_vide(prenom)));
    for (j=0;prenom[j]!='\n';){
        j++;
    }
    prenom[j] = 0;
    do{
        printf("Nom : ");
        fgets(nom,TAILLE_MAX+1,stdin); /*on vérifie que les champs entrés ne sont pas vide avec la fonction est_vide*/
    }while(!(est_vide(nom)));
    for (j=0;nom[j]!='\n';){
        j++;/*on trouve l'index du dernier caractère*/
    }
    nom[j] = 0;/*on retire le '\n' du champ entré*/
    do{
        printf("Ville : ");
        fgets(adresse,TAILLE_MAX+1,stdin);
    }while(!(est_vide(adresse)));
    for (j=0;adresse[j]!='\n';){
        j++;
    }
    adresse[j] = 0;
    do{
        printf("Code postale : ");
        scanf("%s",code_postale);
    }while(!(est_code_postal(code_postale)));

    do{
        printf("Numero de telephone : ");/*pour ceux qui en ont besoin, on vérifie qu'ils sont correspondant avec le champ avec des do while*/
        scanf("%s",num);
    }while(!(est_num(num)));
    /*on scan chaque chaque champ*/
    do{
        printf("Adresse email : ");
        scanf("%s",mail);
    }while(!(est_mail(mail)));
    do{
        if(strcmp(profession,"vide")!=0)printf("Profession : ");
        fgets(profession,TAILLE_MAX+1,stdin);
    }while(!(est_vide(profession)));
    for (j=0;profession[j]!='\n';){
        j++;
    }
    profession[j] = 0;

    tableau[i].id = i+1;
    majuscule_nom(prenom);
    tableau[i].prenom = copie(prenom);
    majuscule_nom(nom);
    tableau[i].nom = copie(nom);
    majuscule_adresse(adresse);
    tableau[i].adresse = copie(adresse);/*on remplit à la dernière place du tableau chaque attribut du client avec ceux scanés*/
    tableau[i].code_postale = copie(code_postale);
    tableau[i].num = copie(num);
    tableau[i].mail = copie(mail);
    tableau[i].profession = copie(profession);
    tableau[i].deleted = copie("ok");
    printf("Le client a bien ete ajoute\n");
}
void afficher(){ /*Fonction faite par Rémi JARA*/
    int i;
    do{
        printf("Voulez vous afficher les donnees avec un filtre ou un tri ? \n  - Pour un filtre --> tapez \"filtre\" \n  - Pour un tri --> tapez \"tri\" \n  - Si vous voulez uniquement afficher la base de donnees --> tapez \"non\" \n  - Si vous voulez afficher les clients auquels il manque un ou plusieurs champs --> tapez \"manquant\"\n");
        scanf("%s",choix_affiche);
    }while(strcmpi(choix_affiche,"filtre")!=0&&strcmpi(choix_affiche,"tri")!=0&&strcmpi(choix_affiche,"non")!=0); /*scan du choix d'affichage avec vérification*/
    if (strcmpi(choix_affiche,"tri")==0){
        do{
            printf("Par quel champ souhaitez vous trier les clients ? \n  - Pour trier par leur prenom --> tapez \"prenom\"\n  - Pour trier par leur nom --> tapez \"nom\"\n  - Pour trier par leur code postaux --> tapez \"code_postale\"\n  - Pour trier par leur profession --> tapez \"profession\"\n");
            scanf("%s",choix_tri);/*scan du type de tri avec vérification*/
        }while(!(est_champ(choix_tri)));
        if (strcmpi(choix_tri,"prenom")==0){
            char choix_sens_tri[TAILLE_MAX+1];
            int temp;
            do{
            printf("Souhaitez vous un affichage croissant (1) ou décroissant (0) ? : ");
            scanf("%s",choix_sens_tri);/*scan du sens du tri avec vérification*/
            }while(!(est_zero_ou_un(choix_sens_tri)));
            temp = atoi(choix_sens_tri);/*on transforme la variable en int pour pouvoir se servir du switch*/
            switch(temp){
                case 0:
                    tri_prenom(0);
                    break;         /*si le choix est 0 on appelle la fonction de tri avec 0 comme argument, si c'est 1 on l'appelle avec 1*/
                case 1:
                    tri_prenom(1);
                    break;
                default:
                    printf("ERREUR");
                    break;
            }
        }
        else if (strcmpi(choix_tri,"nom")==0){
            char choix_sens_tri[TAILLE_MAX+1];
            int temp;
            do{
            printf("Souhaitez vous un affichage croissant (1) ou décroissant (0) ? : ");
            scanf("%s",choix_sens_tri);
            }while(!(est_zero_ou_un(choix_sens_tri)));
            temp = atoi(choix_sens_tri);
            switch(temp){
                case 0:
                    tri_nom(0);
                    break;
                case 1:
                    tri_nom(1);
                default:
                    printf("ERREUR");
                    break;
            }
        }
        else if (strcmpi(choix_tri,"code_postale")==0){
           char choix_sens_tri[TAILLE_MAX+1];
            int temp;
            do{
            printf("Souhaitez vous un affichage croissant (1) ou décroissant (0) ? : ");
            scanf("%s",choix_sens_tri);
            }while(!(est_zero_ou_un(choix_sens_tri)));
            temp = atoi(choix_sens_tri);
            switch(temp){
                case 0:
                    tri_code_postale(0);
                    break;
                case 1:
                    tri_code_postale(1);
                    break;
                default:
                    printf("ERREUR");
                    break;
            }
        }
        else if (strcmpi(choix_tri,"profession")==0){
            char choix_sens_tri[TAILLE_MAX+1];
            int temp;
            do{
            printf("Souhaitez vous un affichage croissant (1) ou décroissant (0) ? : ");
            scanf("%s",choix_sens_tri);
            }while(!(est_zero_ou_un(choix_sens_tri)));
            temp = atoi(choix_sens_tri);
            switch(temp){
                case 0:
                    tri_profession(0);
                    break;
                case 1:
                    printf("oui");
                    tri_profession(1);
                default:
                    printf("ERREUR");
                    break;
            }
        }
    }
    else if (strcmpi(choix_affiche,"filtre")==0){
        do{
        printf("Par quel champ voulez vous filtrer ? \n  - Pour un filtre par prenom --> tapez \"prenom\" \n  - Pour un filtre par nom --> tapez \"nom\" \n  - Pour un filtre par profession --> tapez \"profession\"\n  - Pour un filtre par code postale --> tapez \"code_postale\" \n");
        scanf("%s",choix_filtre);
        }while(!(est_champ(choix_filtre)));/*on scan le champ à filtrer*/
        char param_filtre[TAILLE_MAX+1];
        int temp;
        do{
        printf("Quel filtre souhaitez-vous ? \n  - Champ commençant par le filtre --> tapez \"0\"\n  - Champ contenant le filtre --> tapez \"1\"\n  - Champ se terminant par le filtre --> tapez \"2\"\n  - Champ ne contenant pas le filtre --> tapez \"3\"\n");
        scanf("%s",param_filtre);
        }while(!(est_choix_filtre(param_filtre)));
        temp = atoi(param_filtre);
        if (strcmpi(choix_filtre,"code_postale")==0){
            do{
                if(strcmp(filtre,"\n")==0)printf("Indiquez le filtre que vous souhaitez appliquer : ");
                fgets(filtre,TAILLE_MAX+1,stdin);
            }while(!(est_vide(filtre)));
            switch(temp){
                case 0:
                    commencant(filtre,2);
                    break;
                case 1:
                    recherche(filtre,2);
                case 2:
                    terminant(filtre,2);
                    break;
                 case 3:
                    exclu(filtre,2);
                    break;
                 default:
                    printf("ERREUR");
                    break;
            }
        }
        else if (strcmpi(choix_filtre,"prenom")==0){
            do{
                if(strcmp(filtre,"\n")==0)printf("Indiquez le filtre que vous souhaitez appliquer : ");
                fgets(filtre,TAILLE_MAX+1,stdin);
            }while(!(est_vide(filtre)));
            for (i=0;filtre[i]!='\n';){
                i++;
            }
            filtre[i]=0;
            switch(temp){
                case 0:
                    commencant(filtre,0);
                    break;
                case 1:
                    recherche(filtre,0);
                case 2:
                    terminant(filtre,0);
                    break;
                case 3:
                    exclu(filtre,0);
                    break;
                 default:
                    printf("ERREUR");
                    break;
            }
        }
        else if (strcmpi(choix_filtre,"nom")==0){

            do{
                if(strcmp(filtre,"\n")==0)printf("Indiquez le filtre que vous souhaitez appliquer : ");
                fgets(filtre,TAILLE_MAX+1,stdin);
            }while(!(est_vide(filtre)));
            for (i=0;filtre[i]!='\n';){
                i++;
            }
            filtre[i]=0;
            switch(temp){
                case 0:
                    commencant(filtre,1);
                    break;
                case 1:
                    recherche(filtre,1);
                case 2:
                    terminant(filtre,1);
                    break;
                case 3:
                    exclu(filtre,1);
                    break;
                 default:
                    printf("ERREUR");
                    break;
            }/*on applique le filtre voulu*/
        }
        else{
            do{
                if(strcmp(filtre,"\n")==0)printf("Indiquez le filtre que vous souhaitez appliquer : ");
                fgets(filtre,TAILLE_MAX+1,stdin);
            }while(!(est_vide(filtre)));
            for (i=0;filtre[i]!='\n';){
                i++;
            }
            filtre[i]=0;
            switch(temp){
                case 0:
                    commencant(filtre,3);
                    break;
                case 1:
                    recherche(filtre,3);
                case 2:
                    terminant(filtre,3);
                    break;
                case 3:
                    exclu(filtre,3);
                    break;
                 default:
                    printf("ERREUR");
                    break;
            }
        }
    }
    else{
        int j,i,k=0;
        for (j=0;tableau[j].prenom!=NULL;){
            j++;                                /*on récupère le nombre de client dans le tableau */
        }
        printf("|%-5s | %-20s | %-26s | %-22s | %-16s | %-23s | %-40s | %-22s \n",champ[0],champ[1],champ[2],champ[3],champ[4],champ[5],champ[6],champ[7]);
        /*on print les champs pour plus de compréhension*/
        for (i=0;i<j;i++) /*boucle allant de i valant 0 à j vallant le nombre de client dans le tableau*/
        {
            if (strcmpi(choix_affiche,"manquant")!=0){
                afficher_client(tableau,i);
            }
            else if (strcmpi(choix_affiche,"manquant")==0){
                /*si on a indiqué l'option "manquant" on affiche uniquement si un des champs est vide en comparant avec la chaine : "*Champ vide*"*/
                if ((strcmp(tableau[i].deleted,"ok")==0 && strcmp(tableau[i].prenom,"*Champ vide*")==0)||(strcmp(tableau[i].nom,"*Champ vide*")==0)||(strcmp(tableau[i].adresse,"*Champ vide*")==0)||(strcmp(tableau[i].code_postale,"*Champ vide*")==0)||(strcmp(tableau[i].num,"*Champ vide*")==0)||(strcmp(tableau[i].mail,"*Champ vide*")==0)||(strcmp(tableau[i].profession,"*Champ vide*")==0)){
                printf("|%-5d | %-20s | %-26s | %-22s | %-16s | %-23s | %-40s | %-22s \n",tableau[i].id,tableau[i].prenom,tableau[i].nom,tableau[i].adresse,tableau[i].code_postale,tableau[i].num,tableau[i].mail,tableau[i].profession);
                k++;
                }
            }
        }
        if (strcmpi(choix_affiche,"manquant")==0){
            printf("Le fichier client contient %d client avec un ou plusieurs champs manquants",k);
        }
    }
}
void afficher_client(sclient *tableau,int i){/*Fonction faite par Rémi JARA*/
    if (strcmpi(tableau[i].deleted,"ok")==0){/*on affiche chaque champ de chaque client du tableau*/
        printf("|%-5d | %-20s | %-26s | %-22s | %-16s | %-23s | %-40s | %-22s \n",tableau[i].id,tableau[i].prenom,tableau[i].nom,tableau[i].adresse,tableau[i].code_postale,tableau[i].num,tableau[i].mail,tableau[i].profession);
    }
}
void filtre_prenom(char *filtre,char *choixchoix_filtre){ /*Fonction faite par Rémi JARA*/
    int j,i;
    for (j=0;tableau[j].prenom!=NULL;){
        j++;                            /*on récupère le nombre de client dans le tableau */
    }
    printf("|%-5s | %-20s | %-26s | %-22s | %-16s | %-23s | %-40s | %-22s \n",champ[0],champ[1],champ[2],champ[3],champ[4],champ[5],champ[6],champ[7]);
    /*on print les champs pour plus de compréhension*/
    for (i=0;i<j;i++)
    {   if(strcmpi(tableau[i].prenom,filtre)==0){/*on affiche chaque champ de chaque client qui a le champ correspondant qui est égal au filtre voulu*/
            if (strcmpi(tableau[i].deleted,"ok")==0){
                printf("|%-5d | %-20s | %-26s | %-22s | %-16s | %-23s | %-40s | %-22s \n",tableau[i].id,tableau[i].prenom,tableau[i].nom,tableau[i].adresse,tableau[i].code_postale,tableau[i].num,tableau[i].mail,tableau[i].profession);
            }
        }
    }
}
void filtre_nom(char *filtre,char *choixchoix_filtre){ /*Fonction faite par Rémi JARA*/
    int j,i;
    for (j=0;tableau[j].prenom!=NULL;){
        j++;
    }
    printf("|%-5s | %-20s | %-26s | %-22s | %-16s | %-23s | %-40s | %-22s \n",champ[0],champ[1],champ[2],champ[3],champ[4],champ[5],champ[6],champ[7]);

    for (i=0;i<j;i++)
    {
        if(strcmpi(tableau[i].nom,filtre)==0){
            if (strcmp(tableau[i].deleted,"ok")==0){
                printf("|%-5d | %-20s | %-26s | %-22s | %-16s | %-23s | %-40s | %-22s \n",tableau[i].id,tableau[i].prenom,tableau[i].nom,tableau[i].adresse,tableau[i].code_postale,tableau[i].num,tableau[i].mail,tableau[i].profession);
            }
        }
    }
}
void filtre_profession(char *filtre,char *choixchoix_filtre){ /*Fonction faite par Rémi JARA*/
    int j,i;
    for (j=0;tableau[j].prenom!=NULL;){
        j++;
    }
    printf("|%-5s | %-20s | %-26s | %-22s | %-16s | %-23s | %-40s | %-22s \n",champ[0],champ[1],champ[2],champ[3],champ[4],champ[5],champ[6],champ[7]);

    for (i=0;i<j;i++)
    {
        if(strcmpi(tableau[i].profession,filtre)==0){
            if (strcmp(tableau[i].deleted,"ok")==0){
                printf("|%-5d | %-20s | %-26s | %-22s | %-16s | %-23s | %-40s | %-22s \n",tableau[i].id,tableau[i].prenom,tableau[i].nom,tableau[i].adresse,tableau[i].code_postale,tableau[i].num,tableau[i].mail,tableau[i].profession);
            }
        }
    }
}
void filtre_code_postale(char *filtre){ /*Fonction faite par Rémi JARA*/
    int j,i;
    for (j=0;tableau[j].prenom!=NULL;){
        j++;
    }
    printf("|%-5s | %-20s | %-26s | %-22s | %-16s | %-23s | %-40s | %-22s \n",champ[0],champ[1],champ[2],champ[3],champ[4],champ[5],champ[6],champ[7]);

    for (i=0;i<j;i++)
    {
        if(strcmpi(tableau[i].code_postale,filtre)==0){
            if (strcmp(tableau[i].deleted,"ok")==0){
                printf("|%-5d | %-20s | %-26s | %-22s | %-16s | %-23s | %-40s | %-22s \n",tableau[i].id,tableau[i].prenom,tableau[i].nom,tableau[i].adresse,tableau[i].code_postale,tableau[i].num,tableau[i].mail,tableau[i].profession);
            }
        }
    }
}
void modifierclient(int modifierligne){/*Fonction faite par Rémi JARA*/
    int tableauChoix[7],i=0,j,newchoix;/*on initialise un tableau permettant de savoir quel(s) champ(s) modifier et deux compteur
                                        et la variable newchoix qui permet de selectionner les champ à modifier en amont*/
    char choix[TAILLE_MAX+1];
    printf("Quel champs voulez vous modifier ?\n");
    do{
    printf("Prenom ?\n  - Oui --> tapez \"1\"\n  - Non --> tapez \"0\"\n");
    scanf("%s",choix);
    }while(!(est_zero_ou_un(choix)));
    newchoix = atoi(choix);
    tableauChoix[i] = newchoix;
    i++;
    do{
    printf("Nom ?\n  - Oui --> tapez \"1\"\n  - Non --> tapez \"0\"\n");       /*si on veut modifier le champ demandé, on rentre 1, sinon 0*/
    scanf("%s",choix);                                                        /*cette valeur est alors envoyé dans le tableau à son indice correspondant*/
    }while(!(est_zero_ou_un(choix)));
    newchoix = atoi(choix);
    tableauChoix[i] = newchoix;
    i++;
    do{
    printf("Adresse ?\n  - Oui --> tapez \"1\"\n  - Non --> tapez \"0\"\n");
    scanf("%s",choix);
    }while(!(est_zero_ou_un(choix)));
    newchoix = atoi(choix);
    tableauChoix[i] = newchoix;
    i++;
    do{
    printf("Code postale ?\n  - Oui --> tapez \"1\"\n  - Non --> tapez \"0\"\n");
    scanf("%s",choix);
    }while(!(est_zero_ou_un(choix)));
    newchoix = atoi(choix);
    tableauChoix[i] = newchoix;
    i++;
    do{
    printf("Numero de telephone ?\n  - Oui --> tapez \"1\"\n  - Non --> tapez \"0\"\n");
    scanf("%s",choix);
    }while(!(est_zero_ou_un(choix)));
    newchoix = atoi(choix);
    tableauChoix[i] = newchoix;
    i++;
    do{
    printf("Adresse email ?\n  - Oui --> tapez \"1\"\n  - Non --> tapez \"0\"\n");
    scanf("%s",choix);
    }while(!(est_zero_ou_un(choix)));
    newchoix = atoi(choix);
    tableauChoix[i] = newchoix;
    i++;
    do{
    printf("Profession ?\n  - Oui --> tapez \"1\"\n  - Non --> tapez \"0\"\n");
    scanf("%s",choix);
    }while(!(est_zero_ou_un(choix)));
    newchoix = atoi(choix);
    tableauChoix[i] = newchoix;
    for (j=0;j<7;j++){/*boucle faisant 7 itérations (nombre de champ) avec j qui équivaut au champ actuel*/
        if (tableauChoix[j]){/*si la valeur du tableau vaut 1, on rentre dans le if*/
            char newchamp[TAILLE_MAX+1];
            if (j==0){
                printf("%s",champ[j+1]);
                scanf("%s",newchamp);                          /*si j vaut 0 : on modifie le prenom, si j vaut 1 : on modifie le nom etc...*/
                tableau[modifierligne].prenom= copie(newchamp);
            }
            if (j==1){
                printf("%s",champ[j+1]);
                scanf("%s",newchamp);
                tableau[modifierligne].nom= copie(newchamp);
            }
            if (j==2){
                printf("%s",champ[j+1]);
                scanf("%s",newchamp);
                tableau[modifierligne].adresse= copie(newchamp);
            }
            if (j==3){
                do{
                    printf("%s",champ[j+1]);
                    scanf("%s",newchamp);
                }while (!(est_code_postal(newchamp)));
                tableau[modifierligne].code_postale= copie(newchamp);
            }
            if (j==4){
                do{
                    printf("%s",champ[j+1]);
                    scanf("%s",newchamp);
                }while (!(est_num(newchamp)));
                tableau[modifierligne].num= copie(newchamp);
            }
            if (j==5){
                do{
                    printf("%s",champ[j+1]);
                    scanf("%s",newchamp);
                }while (!(est_mail(newchamp)));
                tableau[modifierligne].mail= copie(newchamp);
            }
            if (j==6){
                printf("%s",champ[j+1]);
                scanf("%s",newchamp);
                tableau[modifierligne].profession= copie(newchamp);
            }
        }
    }
}
int trouver(char scanprenom[],char scannom[],char scannum[], char scanmail[],int checksuppr,int checkmodifier){ /*Fonction faite par Rémi JARA*/
    int i,j=0,choix;/*initialisation des compteurs et du choix de client*/
    int liste[MAXTAB];/*initialisation du tableau qui va contenir les clients correspondant à la recherche*/
    for (i=0;tableau[i].prenom!=NULL;i++){
        if (strcmp(tableau[i].prenom,scanprenom)==0 && strcmp(tableau[i].nom,scannom)==0 && (strcmp(tableau[i].num,scannum)==0 || strcmp(tableau[i].mail,scanmail)==0)){
            liste[j] = tableau[i].id - 1;/*en parcourant tout le tableau, si on vérifie les conditions de recherche (nom*prenom*(mail+mail)) on rentre l'id des clients dans notre liste*/
            j++;/*on incrémente j pour obtenir la taille de la liste plus facilement*/
        }
    }
    int k;
    if (j>0){
        for(k=0;k<j;k++){/*on affiche tout les clients correspondant à la recherche*/
            printf("\nClient numero %d : %-3d %-20s | %-26s | %-20s | %-10s | %-20s | %-40s | %-22s \n",k,tableau[liste[k]].id,tableau[liste[k]].prenom,tableau[liste[k]].nom,tableau[liste[k]].adresse,tableau[liste[k]].code_postale,tableau[liste[k]].num,tableau[liste[k]].mail,tableau[liste[k]].profession);
        }
        if (checksuppr){/*si on est dans le cas d'une suppression, on appelle la fonction correspondante*/
            do{
                printf("\nIndiquez quel client vous souhaitez supprimer en rentrant son indice ecrit ci-dessus : ");
                scanf("%d",&choix);
            }while(choix<0 || choix>j+1);
            suppr(liste[choix]);
            printf("Le client a bien ete supprime");
            return 1;
        }
        else if(checkmodifier){/*si on est dans le cas d'une modification, on appelle la fonction correspondante*/
            do{
                printf("\nIndiquez quel client vous souhaitez modifier en rentrant son indice ecrit ci-dessus : ");
                scanf("%d",&choix);
            }while(choix<0 || choix>j+1);
            modifierclient(liste[choix]);
            printf("Le client a bien ete modifie");
            return 1;
        }
    }
    else{/*si la longueur de la liste vaut 0, la recherche n'a pas été concluante*/
        printf("Aucun client ne rempli ces criteres\nVous pouvez l'ajouter si vous le souhaitez");
        return 0;
    }
    return 0;
}
int suppr(int supprligne){/*Fonction faite par Rémi JARA*/
    int i,j;/*Fonction faite par Rémi JARA*/
    for (i=0;tableau[i].prenom!=NULL;){
        i++;                                /*boucle for permettant de trouver le nombre de client dans le tableau*/
    }
    tableau[supprligne].deleted = "deleted";/*on ajout l'état deleted au client ayant l'id entré en argument*/
    for (j=supprligne;j<i;j++){
        tableau[j].id=tableau[j].id-1;
    }
    return 1;
}
void input(int checksuppr,int checkmodifier){ /*Fonction faite par Rémi JARA*/
    char verif[TAILLE_MAX+1];/*fonction permettant de récupérer un nom un prénom et une adresse mail ou un numéro de téléphone pour faire des recherches*/
    char num[TAILLE_MAX+1]="0",mail[TAILLE_MAX+1]="0",nom[TAILLE_MAX+1],prenom[TAILLE_MAX+1];
    printf("Entrez le prenom du client que vous cherchez : ");
    scanf("%s",prenom);
    printf("Entrez le nom du client que vous cherchez : ");
    scanf("%s",nom);/*on scan le prenom et le nom du client voulu*/
    do{
    printf("Souhaitez vous entrer son email ou son numero de telephone ? \nPour l'email--> tapez \"mail\"\nPour le numero de telephone --> tapez \"tel\"\n");
    scanf("%s",verif);
    }while(strcmpi(verif,"mail")!=0 && strcmpi(verif,"tel")!=0);/*l'utilisateur veut il chercher avec le mail ou le numéro de tel ? vérification*/
    if (strcmpi(verif,"mail")==0){
        do{
        printf("Entrez le mail du client que vous cherchez : ");
        scanf("%s",mail);
        }while(!(est_mail(mail)));
        trouver(prenom,nom,num,mail,checksuppr,checkmodifier);/*on lance la fonction permettant de trouver le client voulu avec soit un mail soit un numéro de tel*/
    }                                                         /*les arguments checksuppr et checkmodifier permettent de savoir dans quel cas nous nous trouvons*/
    else{                                                     /* (1,0) pour une suppression, (0,1) pour une modification, (0,0) pour une simple recherche*/
        do{
        printf("Entrez le numero de telephone du client que vous cherchez: ");
        scanf("%s",num);
        }while(!(est_num(num)));
        trouver(prenom,nom,num,mail,checksuppr,checkmodifier);
    }
}
int est_champ(char * choix_filtre){/*Fonction faite par Rémi JARA*//*fonction qui renvoit 1 si la valeur passé en argument est un champ valide, 0 sinon*/
    if (strcmpi(choix_filtre,"prenom")!=0&&strcmpi(choix_filtre,"nom")!=0&&strcmpi(choix_filtre,"profession")!=0&&strcmpi(choix_filtre,"code_postale")!=0){
        printf("\nErreur de selection de champ a filtrer\n");
        return 0;
    }
    return 1;
}
int est_vide (char *mot){/*Fonction faite par Rémi JARA*/
    int i,j=0;
    if (strcmp(mot,"\n")==0 || mot == NULL){
        return 0;
    }
    for(i=0;i<strlen(mot);i++){
        if (isspace(mot[i])){
            j++;
        }
    }
    if (j==strlen(mot)){
        return 0;
    }
    return 1;
}
int est_zero_ou_un(char *choix){/*Fonction faite par Rémi JARA*//*fonction qui renvoit 1 si la valeur passé en argument est un 0 ou un 1, renvoit 0 sinon*/
    if (strcmp(choix,"0")==0 || strcmp(choix,"1")==0 ){
        return 1;
    }
    printf("\nErreur dans la selection\n");
    return 0;
}
int est_choix_filtre(char *choix){/*Fonction faite par Rémi JARA*//*fonction qui renvoit 1 si la valeur passé en argument est un 0, 1, 2 ou 3 renvoit 0 sinon*/
    if (strcmp(choix,"0")==0 || strcmp(choix,"1")==0 || strcmp(choix,"2")==0 || strcmp(choix,"3")==0 ){
        return 1;
    }
    printf("\nErreur dans la selection\n");
    return 0;
}
int est_num(char *num){ /*Fonction faite par Rémi JARA*/
    int i,ctrcheck = 0;/*fonction qui renvoit 1 si la valeur passé en argument est un numéro de téléphone valide, 0 sinon*/
    for (i=0;i<14;i++){/*boucle qui parcourt le numéro*/
        if (i!=2&&i!=5&&i!=8&&i!=11){/*si on est a l'emplacement d'un chiffre on rentre dans le if*/
            if (isdigit(num[i])){
                ctrcheck++;/*si c'est bien un chiffre, on incrémente le compteur de vérification*/
            }
        }
        else{
            if (num[i]==46){
                ctrcheck++;/* si on est à l'emplacement d'un point, et que c'est bien un point, on incrémente le commpteur de vérification*/
            }
        }
    }
    if (ctrcheck==14 && strlen(num)==14){/*si on a incrémenté 14 fois (nombre de caractère d'un numéro, le numéro est validé*/
        return 1;
    }
    else{
        printf("\nNumero de telephone non valide\nNorme des numeros de telephone : 00.00.00.00.00\n");/*sinon on renvoie un message d'érreur*/
        return 0;
    }
}
int est_mail(char *mail){ /*Fonction faite par Rémi JARA*/
    int i=0;/*fonction qui renvoit 1 si la valeur passé en argument est une adresse mail valide, 0 sinon*/
    int len_mail = strlen(mail);
    if (!(isalpha(mail[i]))){/*si le premier caractère n'est pas une lettre, l'email n'est pas valide*/
        printf("\nEmail non valide\nNorme des adresses email : ---@---.---\n");
        return 0;
    }
    int at=-1,point=-1;
    for (i=0;i<len_mail;i++){
        if (mail[i]==64){
            at = i;
        }
        else if (mail[i]==46){/*boucle qui parcourt le mail, et qui vérifie la présence d'un @ et d'un point*/
            point = i;
        }
    }
    if (point==-1||at==-1){/*si il n'y a pas de @ iu pas de point, l'email n'est pas valide*/
        printf("\nEmail non valide\nNorme des adresses email : ---@---.---\n");
        return 0;
    }
    if ((point >= (len_mail - 1))){/*si le point est en dernière position*/
        printf("\nEmail non valide\nNorme des adresses email : ---@---.---\n");
        return 0;
    }
    return 1;/*l'email est bien valide*/
}
int est_code_postal(char *code_postale){ /*Fonction faite par Rémi JARA*/
    int i,ctr=0;
    for (i=0;i<strlen(code_postale);i++){/*on incrémente le compteur si chaque caractère du code postale est un chiffre*/
        if (isdigit(code_postale[i])){
            ctr++;
        }
    }
    if (ctr==5){/*si le compteur vaut 5 c'est un code postale valide*/
        return 1;
    }
    printf("\nCode postale non valide\nNorme des codes postaux : 00000\n");/*sinon on renvoit un message d'erreur*/
    return 0;
}
int est_fichier(char fichier[]){/*Fonction faite par Rémi JARA*/
    int i;
    char *carac="<>:\"|?*\\/";
    for(i=0;i<strlen(fichier);i++){
        if (strchr(carac,fichier[i])!=NULL){
            printf("Erreur dans la sélection du nom du fichier\nLe nom ne peut pas contenir les caractères suivants : / \\ : ? : | < > * \"\n");
            return 0;
        }
    }
    return 1;
}
char *majuscule_nom(char *mot){/*Fonction faite par Rémi JARA*/
    mot[0] = toupper(mot[0]);
    return mot;
}
char *majuscule_adresse(char *mot){/*Fonction faite par Rémi JARA*/
    int i;
    for(i=0;i<strlen(mot);i++){
        mot[i]=toupper(mot[i]);
    }
    return mot;
}
void tri_prenom(int choix_sens_tri){/*Fonction faite par Idrissa SALL*/
    char *tempprenom, *tempnom, *tempadresse, *tempcode_postale, *tempnum, *tempmail, *tempprofession, *tempdeleted;
    int i,j,k,tempid;
    for (k=0;tableau[k].prenom!=NULL;){
        k++;
    }
    for (i = 0; i < k; i++){
        for (j = 0; j < k; j++){
            if(choix_sens_tri){
                if (strcmpr(tableau[i].prenom, tableau[j].prenom) < 0&& strcmpr(tableau[i].prenom, "*Champ vide*")!=0){
                    tempid = tableau[i].id;
                    tempdeleted = tableau[i].deleted;
                    tempprenom = tableau[i].prenom;
                    tempnom = tableau[i].nom;
                    tempadresse = tableau[i].adresse;
                    tempcode_postale = tableau[i].code_postale;
                    tempnum = tableau[i].num;
                    tempmail = tableau[i].mail;
                    tempprofession = tableau[i].profession;
                    tableau[i] = tableau[j];
                    tableau[j].id = tempid;
                    tableau[j].deleted = tempdeleted;
                    tableau[j].prenom = tempprenom;
                    tableau[j].nom = tempnom;
                    tableau[j].adresse = tempadresse;
                    tableau[j].code_postale = tempcode_postale;
                    tableau[j].num = tempnum;
                    tableau[j].mail = tempmail;
                    tableau[j].profession = tempprofession;
                }
            }
            else{
                if (strcmpi(tableau[i].prenom, tableau[j].prenom) > 0&& strcmp(tableau[i].prenom, "*Champ vide*")!=0){
                    tempid = tableau[i].id;
                    tempdeleted = tableau[i].deleted;
                    tempprenom = tableau[i].prenom;
                    tempnom = tableau[i].nom;
                    tempadresse = tableau[i].adresse;
                    tempcode_postale = tableau[i].code_postale;
                    tempnum = tableau[i].num;
                    tempmail = tableau[i].mail;
                    tempprofession = tableau[i].profession;
                    tableau[i] = tableau[j];
                    tableau[j].id = tempid;
                    tableau[j].deleted = tempdeleted;
                    tableau[j].prenom = tempprenom;
                    tableau[j].nom = tempnom;
                    tableau[j].adresse = tempadresse;
                    tableau[j].code_postale = tempcode_postale;
                    tableau[j].num = tempnum;
                    tableau[j].mail = tempmail;
                    tableau[j].profession = tempprofession;
                }
            }
        }
    }
    printf("|%-5s | %-20s | %-26s | %-22s | %-16s | %-23s | %-40s | %-22s \n",champ[0],champ[1],champ[2],champ[3],champ[4],champ[5],champ[6],champ[7]);
    for (i=0;i<k;i++)
    {
        if (strcmp(tableau[i].deleted,"ok")==0){
            printf("|%-5d | %-20s | %-26s | %-22s | %-16s | %-23s | %-40s | %-22s \n",tableau[i].id,tableau[i].prenom,tableau[i].nom,tableau[i].adresse,tableau[i].code_postale,tableau[i].num,tableau[i].mail,tableau[i].profession);
        }
    }
}
void tri_nom(int choix_sens_tri){/*Fonction faite par Idrissa SALL*/
    char *tempprenom, *tempnom, *tempadresse, *tempcode_postale, *tempnum, *tempmail, *tempprofession, *tempdeleted;
    int i, j,k,tempid;
    remplir(0,0,tableau);
    for (k=0;tableau[k].prenom!=NULL;){
        k++;
    }
    for (i = 0; i < k; i++){
        for (j = 0; j < k; j++){
            if(choix_sens_tri){
                if (strcmpi(tableau[i].nom, tableau[j].nom) < 0&& strcmp(tableau[i].nom, "*Champ vide*")!=0){
                    tempid = tableau[i].id;
                    tempdeleted = tableau[i].deleted;
                    tempprenom = tableau[i].prenom;
                    tempnom = tableau[i].nom;
                    tempadresse = tableau[i].adresse;
                    tempcode_postale = tableau[i].code_postale;
                    tempnum = tableau[i].num;
                    tempmail = tableau[i].mail;
                    tempprofession = tableau[i].profession;
                    tableau[i] = tableau[j];
                    tableau[j].id = tempid;
                    tableau[j].deleted = tempdeleted;
                    tableau[j].prenom = tempprenom;
                    tableau[j].nom = tempnom;
                    tableau[j].adresse = tempadresse;
                    tableau[j].code_postale = tempcode_postale;
                    tableau[j].num = tempnum;
                    tableau[j].mail = tempmail;
                    tableau[j].profession = tempprofession;
                }
            }
            else{
                if (strcmpi(tableau[i].nom, tableau[j].nom) > 0&& strcmp(tableau[i].nom, "*Champ vide*")!=0){
                    tempid = tableau[i].id;
                    tempdeleted = tableau[i].deleted;
                    tempprenom = tableau[i].prenom;
                    tempnom = tableau[i].nom;
                    tempadresse = tableau[i].adresse;
                    tempcode_postale = tableau[i].code_postale;
                    tempnum = tableau[i].num;
                    tempmail = tableau[i].mail;
                    tempprofession = tableau[i].profession;
                    tableau[i] = tableau[j];
                    tableau[j].id = tempid;
                    tableau[j].deleted = tempdeleted;
                    tableau[j].prenom = tempprenom;
                    tableau[j].nom = tempnom;
                    tableau[j].adresse = tempadresse;
                    tableau[j].code_postale = tempcode_postale;
                    tableau[j].num = tempnum;
                    tableau[j].mail = tempmail;
                    tableau[j].profession = tempprofession;
                }
            }
        }
    }
    printf("|%-5s | %-20s | %-26s | %-22s | %-16s | %-23s | %-40s | %-22s \n",champ[0],champ[1],champ[2],champ[3],champ[4],champ[5],champ[6],champ[7]);
    for (i=0;i<k;i++)
    {
        if (strcmp(tableau[i].deleted,"ok")==0){
            printf("|%-5d | %-20s | %-26s | %-22s | %-16s | %-23s | %-40s | %-22s \n",tableau[i].id,tableau[i].prenom,tableau[i].nom,tableau[i].adresse,tableau[i].code_postale,tableau[i].num,tableau[i].mail,tableau[i].profession);
        }
    }
}
void tri_profession(int choix_sens_tri){/*Fonction faite par Idrissa SALL*/
    char *tempprenom, *tempnom, *tempadresse, *tempcode_postale, *tempnum, *tempmail, *tempprofession, *tempdeleted;
    int i, j,k,tempid;
    remplir(0,0,tableau);
    for (k=0;tableau[k].prenom!=NULL;){
        k++;
    }
    for (i = 0; i < k; i++){
        for (j = 0; j < k; j++){
            if(choix_sens_tri){
                if (strcmpi(tableau[i].profession, tableau[j].profession) < 0 && strcmp(tableau[i].profession, "*Champ vide*")!=0){
                    tempid = tableau[i].id;
                    tempdeleted = tableau[i].deleted;
                    tempprenom = tableau[i].prenom;
                    tempnom = tableau[i].nom;
                    tempadresse = tableau[i].adresse;
                    tempcode_postale = tableau[i].code_postale;
                    tempnum = tableau[i].num;
                    tempmail = tableau[i].mail;
                    tempprofession = tableau[i].profession;
                    tableau[i] = tableau[j];
                    tableau[j].id = tempid;
                    tableau[j].deleted = tempdeleted;
                    tableau[j].prenom = tempprenom;
                    tableau[j].nom = tempnom;
                    tableau[j].adresse = tempadresse;
                    tableau[j].code_postale = tempcode_postale;
                    tableau[j].num = tempnum;
                    tableau[j].mail = tempmail;
                    tableau[j].profession = tempprofession;
                }
            }
            else{
                if (strcmpi(tableau[i].profession, tableau[j].profession) > 0&& strcmp(tableau[i].profession, "*Champ vide*")!=0){
                    tempid = tableau[i].id;
                    tempdeleted = tableau[i].deleted;
                    tempprenom = tableau[i].prenom;
                    tempnom = tableau[i].nom;
                    tempadresse = tableau[i].adresse;
                    tempcode_postale = tableau[i].code_postale;
                    tempnum = tableau[i].num;
                    tempmail = tableau[i].mail;
                    tempprofession = tableau[i].profession;
                    tableau[i] = tableau[j];
                    tableau[j].id = tempid;
                    tableau[j].deleted = tempdeleted;
                    tableau[j].prenom = tempprenom;
                    tableau[j].nom = tempnom;
                    tableau[j].adresse = tempadresse;
                    tableau[j].code_postale = tempcode_postale;
                    tableau[j].num = tempnum;
                    tableau[j].mail = tempmail;
                    tableau[j].profession = tempprofession;
                }
            }
        }
    }
    printf("|%-5s | %-20s | %-26s | %-22s | %-16s | %-23s | %-40s | %-22s \n",champ[0],champ[1],champ[2],champ[3],champ[4],champ[5],champ[6],champ[7]);
    for (i=0;i<k;i++)
    {
        if (strcmp(tableau[i].deleted,"ok")==0){
            printf("|%-5d | %-20s | %-26s | %-22s | %-16s | %-23s | %-40s | %-22s \n",tableau[i].id,tableau[i].prenom,tableau[i].nom,tableau[i].adresse,tableau[i].code_postale,tableau[i].num,tableau[i].mail,tableau[i].profession);
        }
    }
}
void tri_code_postale(int choix_sens_tri){/*Fonction faite par Idrissa SALL*/


    char *tempprenom, *tempnom, *tempadresse, *tempcode_postale, *tempnum, *tempmail, *tempprofession, *tempdeleted;
    int i, j,k,tempid;
    remplir(0,0,tableau);
    for (k=0;tableau[k].prenom!=NULL;){
        k++;
    }
    for (i = 0; i < k; i++){
        for (j = 0; j < k; j++){
            if(choix_sens_tri){
                if (strcmpi(tableau[i].code_postale, tableau[j].code_postale) < 0&& strcmp(tableau[i].code_postale, "*Champ vide*")!=0){
                    tempid = tableau[i].id;
                    tempdeleted = tableau[i].deleted;
                    tempprenom = tableau[i].prenom;
                    tempnom = tableau[i].nom;
                    tempadresse = tableau[i].adresse;
                    tempcode_postale = tableau[i].code_postale;
                    tempnum = tableau[i].num;
                    tempmail = tableau[i].mail;
                    tempprofession = tableau[i].profession;
                    tableau[i] = tableau[j];
                    tableau[j].id = tempid;
                    tableau[j].deleted = tempdeleted;
                    tableau[j].prenom = tempprenom;
                    tableau[j].nom = tempnom;
                    tableau[j].adresse = tempadresse;
                    tableau[j].code_postale = tempcode_postale;
                    tableau[j].num = tempnum;
                    tableau[j].mail = tempmail;
                    tableau[j].profession = tempprofession;
                }
            }
            else{
                if (strcmpi(tableau[i].code_postale, tableau[j].code_postale) > 0&& strcmp(tableau[i].code_postale, "*Champ vide*")!=0){
                    tempid = tableau[i].id;
                    tempdeleted = tableau[i].deleted;
                    tempprenom = tableau[i].prenom;
                    tempnom = tableau[i].nom;
                    tempadresse = tableau[i].adresse;
                    tempcode_postale = tableau[i].code_postale;
                    tempnum = tableau[i].num;
                    tempmail = tableau[i].mail;
                    tempprofession = tableau[i].profession;
                    tableau[i] = tableau[j];
                    tableau[j].id = tempid;
                    tableau[j].deleted = tempdeleted;
                    tableau[j].prenom = tempprenom;
                    tableau[j].nom = tempnom;
                    tableau[j].adresse = tempadresse;
                    tableau[j].code_postale = tempcode_postale;
                    tableau[j].num = tempnum;
                    tableau[j].mail = tempmail;
                    tableau[j].profession = tempprofession;
                }
            }
        }
    }
    printf("|%-5s | %-20s | %-26s | %-22s | %-16s | %-23s | %-40s | %-22s \n",champ[0],champ[1],champ[2],champ[3],champ[4],champ[5],champ[6],champ[7]);
    for (i=0;i<k;i++)
    {
        if (strcmp(tableau[i].deleted,"ok")==0){
            printf("|%-5d | %-20s | %-26s | %-22s | %-16s | %-23s | %-40s | %-22s \n",tableau[i].id,tableau[i].prenom,tableau[i].nom,tableau[i].adresse,tableau[i].code_postale,tableau[i].num,tableau[i].mail,tableau[i].profession);
        }
    }
}
int strcmpr(char * ch1, char * ch2){/*Fonction faite par Idrissa SALL*//*fonction pour comparer deux chaines*/




    int x=0 ,y=0;
    while(ch1[x] || ch2[y]){
        if(ch1[x] != ch2[y]){
            if(ch1[x] < ch2[y])
                return -9;
            if(ch1[x] > ch2[y])
                return 4;
        }
        if(ch1[x] != '\0')
            x++;
        if(ch2[y] != '\0')
            y++;
    }
    return 0;
}
void commencant(char c[],int paramfiltre){/*Fonction faite par Idrissa SALL*//*recherche en debut de mot*/
    int t,j;
    for (j=0;tableau[j].prenom!=NULL;){
        j++;                                /*boucle for permettant de trouver le nombre de client dans le tableau*/
    }
    t=strlen(c);
    int i=0;
    switch(paramfiltre){
        case 0:
            for(i=0; i< j; i++){
                if(strnicmp(tableau[i].prenom,c,t)==0 && strcmp(tableau[i].prenom,"*Champ vide*")!=0){/*si on veut faire avec casse on peut utiliser strnicmp. sans casse on utilise ma fonction sntncmpr*/
                    afficher_client(tableau,i);
                }
            }
            break;
        case 1:
            for(i=0; i< j; i++){
                if(strnicmp(tableau[i].nom,c,t)==0&& strcmp(tableau[i].nom,"*Champ vide*")!=0){/*si on veut faire avec casse on peut utiliser strnicmp. sans casse on utilise ma fonction sntncmpr*/
                    afficher_client(tableau,i);
                }
            }
            break;
        case 2:
            for(i=0; i< j; i++){
                if(strnicmp(tableau[i].code_postale,c,t-1)==0&& strcmp(tableau[i].code_postale,"*Champ vide*")!=0){/*si on veut faire avec casse on peut utiliser strnicmp. sans casse on utilise ma fonction sntncmpr*/
                    afficher_client(tableau,i);
                }
            }
            break;
        case 3:
            for(i=0; i< j; i++){
                if(strnicmp(tableau[i].profession,c,t)==0&& strcmp(tableau[i].profession,"*Champ vide*")!=0){/*si on veut faire avec casse on peut utiliser strnicmp. sans casse on utilise ma fonction sntncmpr*/
                    afficher_client(tableau,i);
                }
            }
            break;
        default:
            printf("ERREUR");
            break;
    }
}
void terminant(char c[],int paramfiltre){/*Fonction faite par Idrissa SALL*//*recherche en fin de mot*/
    int t,j;
    for (j=0;tableau[j].prenom!=NULL;){
        j++;                                /*boucle for permettant de trouver le nombre de client dans le tableau*/
    }
    t=strlen(c);
    int i=0;
    switch(paramfiltre){
        case 0:
            for(i=0; i< j; i++){
                if(strinvcmpr(tableau[i].prenom,c,t)==0&& strcmp(tableau[i].prenom,"*Champ vide*")!=0){/*si on veut faire avec casse on peut utiliser strinvcmpr. sans casse on utilise ma fonction sntncmpr*/
                    afficher_client(tableau,i);
                }
            }
            break;
        case 1:
            for(i=0; i< j; i++){
                if(strinvcmpr(tableau[i].nom,c,t)==0&& strcmp(tableau[i].nom,"*Champ vide*")!=0){/*si on veut faire avec casse on peut utiliser strinvcmpr. sans casse on utilise ma fonction sntncmpr*/
                    afficher_client(tableau,i);
                }
            }
            break;
        case 2:
            for(i=0; i< j; i++){
                if(strinvcmpr(tableau[i].code_postale,c,t)==0&& strcmp(tableau[i].code_postale,"*Champ vide*")!=0){/*si on veut faire avec casse on peut utiliser strinvcmpr. sans casse on utilise ma fonction sntncmpr*/
                    afficher_client(tableau,i);
                }
            }
            break;
        case 3:
            for(i=0; i< j; i++){
                if(strinvcmpr(tableau[i].profession,c,t)==0&& strcmp(tableau[i].profession,"*Champ vide*")!=0){/*si on veut faire avec casse on peut utiliser strinvcmpr. sans casse on utilise ma fonction sntncmpr*/
                    afficher_client(tableau,i);
                }
            }
            break;
        default:
            printf("ERREUR");
            break;
    }
}
void recherche(char c[],int paramfiltre){/*Fonction faite par Idrissa SALL*//*recherche au milieu du mot*/
    int j;
    for (j=0;tableau[j].prenom!=NULL;){
        j++;                                /*boucle for permettant de trouver le nombre de client dans le tableau*/
    }
    int i=0;
    switch(paramfiltre){
        case 0:
            for(i=0; i< j; i++){
                if(strstr(tableau[i].prenom,c)!=0&& strcmp(tableau[i].prenom,"*Champ vide*")!=0){/*si on veut faire avec casse on peut utiliser strstr. sans casse on utilise ma fonction sntncmpr*/
                    afficher_client(tableau,i);
                }
            }
            break;
        case 1:
            for(i=0; i< j; i++){
                if(strstr(tableau[i].nom,c)!=0&& strcmp(tableau[i].nom,"*Champ vide*")!=0){/*si on veut faire avec casse on peut utiliser strstr. sans casse on utilise ma fonction sntncmpr*/
                    afficher_client(tableau,i);
                }
            }
            break;
        case 2:
            for(i=0; i< j; i++){
                if(strstr(tableau[i].code_postale,c)!=0&& strcmp(tableau[i].code_postale,"*Champ vide*")!=0){/*si on veut faire avec casse on peut utiliser strstr. sans casse on utilise ma fonction sntncmpr*/ /*on affiche chaque champ de chaque client du tableau*/
                    afficher_client(tableau,i);
                }
            }
            break;
        case 3:
            for(i=0; i< j; i++){
                if(strstr(tableau[i].profession,c)!=0&& strcmp(tableau[i].profession,"*Champ vide*")!=0){/*si on veut faire avec casse on peut utiliser strstr. sans casse on utilise ma fonction sntncmpr*/
                    afficher_client(tableau,i);
                }
            }
            break;
        default:
            break;
    }
}
void exclu(char c[],int paramfiltre){/*Fonction faite par Idrissa SALL*//*exclure la chaine tapée*/
    int j;
    for (j=0;tableau[j].prenom!=NULL;){
        j++;                                /*boucle for permettant de trouver le nombre de client dans le tableau*/
    }
    int i=0;
    switch(paramfiltre){
        case 0:
            for(i=0; i< j; i++){
                if(strcase(tableau[i].prenom,c)==0&& strcmp(tableau[i].prenom,"*Champ vide*")!=0){/*si on veut faire avec casse on peut utiliser strstr. sans casse on utilise ma fonction sntncmpr*/
                    afficher_client(tableau,i);
                }
            }
            break;
        case 1:
            for(i=0; i< j; i++){
                if(strcase(tableau[i].nom,c)==0&& strcmp(tableau[i].nom,"*Champ vide*")!=0){/*si on veut faire avec casse on peut utiliser strstr. sans casse on utilise ma fonction sntncmpr*/
                    afficher_client(tableau,i);
                }
            }
            break;
        case 2:
            for(i=0; i< j; i++){
                if(strcase(tableau[i].code_postale,c)==0&& strcmp(tableau[i].code_postale,"*Champ vide*")!=0){/*si on veut faire avec casse on peut utiliser strstr. sans casse on utilise ma fonction sntncmpr*/
                    afficher_client(tableau,i);
                }
            }
            break;
        case 3:
            for(i=0; i< j; i++){
                if(strcase(tableau[i].profession,c)==0&& strcmp(tableau[i].profession,"*Champ vide*")!=0){/*si on veut faire avec casse on peut utiliser strstr. sans casse on utilise ma fonction sntncmpr*/
                    afficher_client(tableau,i);
                }
            }
            break;
        default:
            printf("ERREUR");
            break;
    }
}
char* strcase( const char* ch1, const char* ch2 ){/*Fonction faite par Idrissa SALL*/
    const char* pt1 = ch1 ;
    const char* pt2 = ch2 ;
    const char* r = *pt2 == 0 ? ch1 : 0 ;

    while( *pt1 != 0 && *pt2 != 0 ){
        if( tolower( (unsigned char)*pt1 ) == tolower( (unsigned char)*pt2 ) ){
            if( r == 0 )
                r = pt1 ;
            pt2++ ;
        }
        else{
            pt2 = ch2 ;
            if( r != 0 )
                pt1 = r + 1 ;
            if( tolower( (unsigned char)*pt1 ) == tolower( (unsigned char)*pt2 ) ){
                r = pt1 ;
                pt2++ ;
            }
            else
                r = 0 ;
        }
        pt1++ ;
    }
    return *pt2 == 0 ? (char*)r : 0 ;
}
int strncmpr(char * ch1, char * ch2, int taille){/*Fonction faite par Idrissa SALL*//*fonction pour comparer deux chaines avec de nombre de car en parametre*/

    int x=0 ,y=0,i=0;
    if (taille==0)/*pas necessaire le code marche sans mais il faut laisser comme ca*/
        return 0;
    while(i<taille){
        if(ch1[x] != ch2[y]){
            if(ch1[x] < ch2[y])
                return -9;
            if(ch1[x] > ch2[y])
                return 4;
        }
        x++;
        y++;
        i++;
    }
    return 0;
}
int strinvcmpr(char * ch1, char * ch2, int taille){/*Fonction faite par Idrissa SALL*//*fonction pour comparer deux chaines avec de nombre de carac en parametre depuis la fin de chaine*/
    int x=0 ,y=0,i=0;
    x=strlen(ch1)-1;
    y=strlen(ch2)-1;
    if (taille==0)/*pas necessaire le code marche sans mais il faut laisser comme ca*/
        return 0;
    while(i<taille){
        if(ch1[x] != ch2[y]){
            if(ch1[x] < ch2[y])
                return -9;
            if(ch1[x] > ch2[y])
                return 4;
        }
        x--;
        y--;
        i++;
    }
    return 0;
}
void sauvegarder(){/*Fonction faite par Rémi JARA*/
    char choixsauv[1];
    int choix;
    do{
    printf("Comment voulez-vous sauvegarder les modifications ?\n  - Dans un nouveau fichier --> tapez \"1\"\n  - En ecrasant le fichier actuel --> tapez \"0\"\n");
    scanf("%s",choixsauv);
    }while(!(est_zero_ou_un(choixsauv)));
    choix = atoi(choixsauv);
    int i=0;
    if(choix==0){
        FILE *fichiersauv= fopen(nouveau_chemin,"a+");
        if (fichiersauv == NULL)
        {
            printf("Erreur de lecture du fichier\n"); /*vérification qu'il n'y a aucune erreur avec le fichier*/
            exit(EXIT_FAILURE);
        }
        while (tableau[i].prenom!=NULL){
            if (strcmp(tableau[i].deleted,"deleted")!=0){
                fprintf(fichiersauv,"%s,%s,%s,%s,%s,%s,%s\n",strcmp(tableau[i].prenom,"*Champ vide*")==0 ? "" : tableau[i].prenom,
                                                            strcmp(tableau[i].nom,"*Champ vide*")==0 ? "" : tableau[i].nom,
                                                            strcmp(tableau[i].adresse,"*Champ vide*")==0 ? "" : tableau[i].adresse,
                                                            strcmp(tableau[i].code_postale,"*Champ vide*")==0 ? "" : tableau[i].code_postale,
                                                            strcmp(tableau[i].num,"*Champ vide*")==0 ? "" : tableau[i].num,
                                                            strcmp(tableau[i].mail,"*Champ vide*")==0 ? "" : tableau[i].mail,
                                                            strcmp(tableau[i].profession,"*Champ vide*")==0 ? "" : tableau[i].profession);
                i++;
            }
        }
        fclose(fichiersauv);
        remove(chemin);
        rename(nouveau_chemin, chemin);

    }
    else{

        char nomfichier[200];
        do{
            printf("Choisissez un nom de fichier : ");
            fgets(nomfichier,200,stdin);
        }while(!(est_vide(nomfichier)&&est_fichier(nomfichier)));
        for (i=0;nomfichier[i]!='\n';){
                i++;
        }
        nomfichier[i]=0;
        strcat(nomfichier,".csv");
        printf("\n%s",nomfichier);
        FILE *fichiersauv= fopen(nomfichier,"a+");
        if (fichiersauv == NULL)
        {
            printf("Erreur de lecture du fichier\n"); /*vérification qu'il n'y a aucune erreur avec le fichier*/
            exit(EXIT_FAILURE);
        }
        while (tableau[i].prenom!=NULL){
            if (strcmp(tableau[i].deleted,"deleted")!=0){
                fprintf(fichiersauv,"%s,%s,%s,%s,%s,%s,%s\n",strcmp(tableau[i].prenom,"*Champ vide*")==0 ? "" : tableau[i].prenom,
                                                            strcmp(tableau[i].nom,"*Champ vide*")==0 ? "" : tableau[i].nom,
                                                            strcmp(tableau[i].adresse,"*Champ vide*")==0 ? "" : tableau[i].adresse,
                                                            strcmp(tableau[i].code_postale,"*Champ vide*")==0 ? "" : tableau[i].code_postale,
                                                            strcmp(tableau[i].num,"*Champ vide*")==0 ? "" : tableau[i].num,
                                                            strcmp(tableau[i].mail,"*Champ vide*")==0 ? "" : tableau[i].mail,
                                                            strcmp(tableau[i].profession,"*Champ vide*")==0 ? "" : tableau[i].profession);
                i++;
            }
        }
        fclose(fichiersauv);
    }

}
void menu(){ /*Fonction faite par Rémi JARA */
    do{
        printf("\nChoisis une action a realiser : \n  - Ajout de client --> tapez \"ajout\"\n  - Modifier un client --> tapez \"modifier\" \n  - Supprimer un client --> tapez \"suppr\"\n  - Afficher la base de donnees --> tapez \"afficher\" \n  - Rechercher un client --> tapez \"recherche\"\n  - Quitter l'application --> tapez \"stop\"\n  - Sauvegarder les modifications --> tapez \"sauvegarder\"\n");
        scanf("%s",choix);/*on scan l'action que l'utilisateur veut réaliser*/
        if (strcmpi(choix, "afficher")==0){
            afficher("non");
        }
        else if (strcmpi(choix, "ajout")==0){
            ajout();
        }
        else if (strcmpi(choix, "modifier")==0){
            input(0,1);
        }
        else if(strcmpi(choix,"suppr")==0){
            input(1,0);
        }
        else if (strcmpi(choix,"recherche")==0){
            input(0,0);
        }
        else if (strcmpi(choix,"sauvegarder")==0){
            sauvegarder();
        }
    }while(strcmp(choix,"stop")!=0);
}
