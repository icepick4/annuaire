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
void remplir(int modifier, int supprimer,sclient *client){ /*Fonction faite par Remi JARA*/
    FILE *fichier= fopen(chemin,"a+"); /*On ouvre le fichier csv*/
    int i=0; /* compteur qui correspond à l'id d'un client*/
    if (modifier == 0 && supprimer == 0){
        if (fichier == NULL)
        {
            printf("Erreur de lecture du fichier\n"); /*verification qu'il n'y a aucune erreur avec le fichier*/
            exit(EXIT_FAILURE);
        }
        while(fgets(ligne,TAILLE_MAX+1,fichier)){/* on recupère chaque ligne du fichier dans la variable ligne*/
            char * token = strtok_empty(ligne, "," ); /*on separe chaque champ de la ligne avec le separateur "," pour les recuperer dans la variable token*/
            int j = 0; /*compteur qui correspond à l'indice du champ actuel, respectivement : prenom, nom, adresse, code postale, numero de tel, mail, metier*/
            while (token){ /*on boucle tant que le token n'est pas vide*/
                /*condition permettant de remplir le bon attribut de la structure client passe en argument*/
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
                else if (j==6){/*pour le metier, on s'assure que s'il est vide, son dernier caractères devienne un '\0'*/
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
                j++;/*on incremente de 1 a chaque token recupere*/
                token = strtok_empty (NULL,",");
            }
            client[i].suppr = copie("ok"); /*remplissage de l'id du client et de son etat de suppression*/
            client[i].id = i+1;
            i++;
        }
        tableau[i].prenom=NULL; /*on attribut au dernier client (inexistant) un prenom null pour s'en servir plus tard en tant que condition*/
        fclose(fichier);/*on ferme notre fichier il est desormais rempli*/
    }
}
char *copie(char *str){/*Fonction trouvé sur internet, implémentation de la fonction strdup*/
    int len_str = strlen(str) + 1;
    char *copie = malloc(len_str);
    if(copie)
    {
        strcpy(copie, str);
    }
    return copie;
}
char * strtok_empty (char * str, char const * sep){ /*Fonction trouve sur internet*/
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
void ajout(){ /*Fonction faite par Remi JARA*/
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
        fgets(nom,TAILLE_MAX+1,stdin); /*on verifie que les champs entres ne sont pas vide avec la fonction est_vide*/
    }while(!(est_vide(nom)));
    for (j=0;nom[j]!='\n';){
        j++;/*on trouve l'index du dernier caractère*/
    }
    nom[j] = 0;/*on retire le '\n' du champ entre*/
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
        printf("Numero de telephone : ");/*pour ceux qui en ont besoin, on verifie qu'ils sont correspondant avec le champ avec des do while*/
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
    tableau[i].adresse = copie(adresse);/*on remplit à la dernière place du tableau chaque attribut du client avec ceux scanes*/
    tableau[i].code_postale = copie(code_postale);
    tableau[i].num = copie(num);
    tableau[i].mail = copie(mail);
    tableau[i].profession = copie(profession);
    tableau[i].suppr = copie("ok");
    printf("Le client a bien ete ajoute\n");
}
void afficher(){ /*Fonction faite par Remi JARA*/
    int i;
    do{
        printf("Voulez vous afficher les donnees avec un filtre ou un tri ? \n  - Pour un filtre --> tapez \"filtre\" \n  - Pour un tri --> tapez \"tri\" \n  - Si vous voulez uniquement afficher la base de donnees --> tapez \"non\" \n  - Si vous voulez afficher les clients auquels il manque un ou plusieurs champs --> tapez \"manquant\"\n");
        scanf("%s",choix_affiche);
    }while(strcmpi(choix_affiche,"filtre")!=0&&strcmpi(choix_affiche,"tri")!=0&&strcmpi(choix_affiche,"non")!=0&&strcmpi(choix_affiche,"manquant")!=0); /*scan du choix d'affichage avec verification*/
    if (strcmpi(choix_affiche,"tri")==0){
        do{
            printf("Par quel champ souhaitez vous trier les clients ? \n  - Pour trier par leur prenom --> tapez \"prenom\"\n  - Pour trier par leur nom --> tapez \"nom\"\n  - Pour trier par leur code postaux --> tapez \"code_postale\"\n  - Pour trier par leur profession --> tapez \"profession\"\n");
            scanf("%s",choix_tri);/*scan du type de tri avec verification*/
        }while(!(est_champ(choix_tri)));
        if (strcmpi(choix_tri,"prenom")==0){
            char choix_sens_tri[TAILLE_MAX+1];
            int temp;
            do{
            printf("Souhaitez vous un affichage croissant (1) ou decroissant (0) ? : ");
            scanf("%s",choix_sens_tri);/*scan du sens du tri avec verification*/
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
            printf("Souhaitez vous un affichage croissant (1) ou decroissant (0) ? : ");
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
            printf("Souhaitez vous un affichage croissant (1) ou decroissant (0) ? : ");
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
            printf("Souhaitez vous un affichage croissant (1) ou decroissant (0) ? : ");
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
        printf("Quel filtre souhaitez-vous ? \n  - Champ commencant par le filtre --> tapez \"0\"\n  - Champ contenant le filtre --> tapez \"1\"\n  - Champ se terminant par le filtre --> tapez \"2\"\n  - Champ ne contenant pas le filtre --> tapez \"3\"\n");
        scanf("%s",param_filtre);
        }while(!(est_choix_filtre(param_filtre)));
        temp = atoi(param_filtre);
        if (strcmpi(choix_filtre,"code_postale")==0){
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
                    commencant(filtre,2);
                    break;
                case 1:
                    recherche(filtre,2);
                    break;
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
                    break;
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
            j++;                                /*on recupère le nombre de client dans le tableau */
        }
        printf("|%-5s | %-20s | %-26s | %-22s | %-16s | %-23s | %-40s | %-22s \n",champ[0],champ[1],champ[2],champ[3],champ[4],champ[5],champ[6],champ[7]);
        /*on print les champs pour plus de comprehension*/
        printf("%s",choix_affiche);
        for (i=0;i<j;i++) /*boucle allant de i valant 0 à j vallant le nombre de client dans le tableau*/
        {
            if (strcmpi(choix_affiche,"manquant")!=0){
                afficher_client(tableau,i);
            }
            else if(strcmpi(choix_affiche,"manquant")==0){
                /*si on a indique l'option "manquant" on affiche uniquement si un des champs est vide en comparant avec la chaine : "*Champ vide*"*/
                if ((strcmp(tableau[i].suppr,"ok")==0 && strcmp(tableau[i].prenom,"*Champ vide*")==0)||(strcmp(tableau[i].nom,"*Champ vide*")==0)||(strcmp(tableau[i].adresse,"*Champ vide*")==0)||(strcmp(tableau[i].code_postale,"*Champ vide*")==0)||(strcmp(tableau[i].num,"*Champ vide*")==0)||(strcmp(tableau[i].mail,"*Champ vide*")==0)||(strcmp(tableau[i].profession,"*Champ vide*")==0)){
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
void afficher_client(sclient *tableau,int i){/*Fonction faite par Remi JARA*/
    if (strcmpi(tableau[i].suppr,"ok")==0){/*on affiche chaque champ de chaque client du tableau*/
        printf("|%-5d | %-20s | %-26s | %-22s | %-16s | %-23s | %-40s | %-22s \n",tableau[i].id,tableau[i].prenom,tableau[i].nom,tableau[i].adresse,tableau[i].code_postale,tableau[i].num,tableau[i].mail,tableau[i].profession);
    }
}
void modifierclient(int modifierligne){/*Fonction faite par Remi JARA*/
    int tableauChoix[7],i=0,j,nouveau_choix;/*on initialise un tableau permettant de savoir quel(s) champ(s) modifier et deux compteur
                                        et la variable nouveau_choix qui permet de selectionner les champ à modifier en amont*/
    char choix[TAILLE_MAX+1];
    printf("Quel champs voulez vous modifier ?\n");
    do{
    printf("Prenom ?\n  - Oui --> tapez \"1\"\n  - Non --> tapez \"0\"\n");
    scanf("%s",choix);
    }while(!(est_zero_ou_un(choix)));
    nouveau_choix = atoi(choix);
    tableauChoix[i] = nouveau_choix;
    i++;
    do{
    printf("Nom ?\n  - Oui --> tapez \"1\"\n  - Non --> tapez \"0\"\n");       /*si on veut modifier le champ demande, on rentre 1, sinon 0*/
    scanf("%s",choix);                                                        /*cette valeur est alors envoye dans le tableau à son indice correspondant*/
    }while(!(est_zero_ou_un(choix)));
    nouveau_choix = atoi(choix);
    tableauChoix[i] = nouveau_choix;
    i++;
    do{
    printf("Adresse ?\n  - Oui --> tapez \"1\"\n  - Non --> tapez \"0\"\n");
    scanf("%s",choix);
    }while(!(est_zero_ou_un(choix)));
    nouveau_choix = atoi(choix);
    tableauChoix[i] = nouveau_choix;
    i++;
    do{
    printf("Code postale ?\n  - Oui --> tapez \"1\"\n  - Non --> tapez \"0\"\n");
    scanf("%s",choix);
    }while(!(est_zero_ou_un(choix)));
    nouveau_choix = atoi(choix);
    tableauChoix[i] = nouveau_choix;
    i++;
    do{
    printf("Numero de telephone ?\n  - Oui --> tapez \"1\"\n  - Non --> tapez \"0\"\n");
    scanf("%s",choix);
    }while(!(est_zero_ou_un(choix)));
    nouveau_choix = atoi(choix);
    tableauChoix[i] = nouveau_choix;
    i++;
    do{
    printf("Adresse email ?\n  - Oui --> tapez \"1\"\n  - Non --> tapez \"0\"\n");
    scanf("%s",choix);
    }while(!(est_zero_ou_un(choix)));
    nouveau_choix = atoi(choix);
    tableauChoix[i] = nouveau_choix;
    i++;
    do{
    printf("Profession ?\n  - Oui --> tapez \"1\"\n  - Non --> tapez \"0\"\n");
    gets(choix);
    }while(!(est_zero_ou_un(choix)));
    nouveau_choix = atoi(choix);
    tableauChoix[i] = nouveau_choix;
    for (j=0;j<7;j++){/*boucle faisant 7 iterations (nombre de champ) avec j qui equivaut au champ actuel*/
        int k;
        if (tableauChoix[j]){/*si la valeur du tableau vaut 1, on rentre dans le if*/
            char nouveau_champ[TAILLE_MAX+1]={"vide"};
            if (j==0){
                do{
                    printf("Prenom : ");
                    fgets(nouveau_champ,TAILLE_MAX+1,stdin);
                }while(!(est_vide(nouveau_champ)) && strcmp("vide",nouveau_champ)!=0);
                for (k=0;nouveau_champ[k]!='\n';){
                    k++;
                }
                nouveau_champ[k] = 0;                         /*si j vaut 0 : on modifie le prenom, si j vaut 1 : on modifie le nom etc...*/
                tableau[modifierligne].prenom= copie(nouveau_champ);
            }
            if (j==1){
                do{
                    printf("Nom : ");
                    fgets(nouveau_champ,TAILLE_MAX+1,stdin);
                }while(!(est_vide(nouveau_champ)));
                for (k=0;nouveau_champ[k]!='\n';){
                    k++;
                }
                nouveau_champ[k] = 0;
                tableau[modifierligne].nom= copie(nouveau_champ);
            }
            if (j==2){
                do{
                    printf("Adresse : ");
                    fgets(nouveau_champ,TAILLE_MAX+1,stdin);
                }while(!(est_vide(nouveau_champ)));
                for (k=0;nouveau_champ[k]!='\n';){
                    k++;
                }
                nouveau_champ[k] = 0;
                tableau[modifierligne].adresse= copie(nouveau_champ);
            }
            if (j==3){
                do{
                    printf("%s",champ[j+1]);
                    scanf("%s",nouveau_champ);
                }while (!(est_code_postal(nouveau_champ)));
                tableau[modifierligne].code_postale= copie(nouveau_champ);
            }
            if (j==4){
                do{
                    printf("%s",champ[j+1]);
                    /*scanf("%s",nouveau_champ);*/
                    gets(nouveau_champ);
                }while (!(est_num(nouveau_champ)));
                tableau[modifierligne].num= copie(nouveau_champ);
            }
            if (j==5){
                do{
                    printf("%s",champ[j+1]);
                    scanf("%s",nouveau_champ);
                }while (!(est_mail(nouveau_champ)));
                tableau[modifierligne].mail= copie(nouveau_champ);
            }
            if (j==6){
                do{
                    printf("Profession : ");
                    fgets(nouveau_champ,TAILLE_MAX+1,stdin);
                }while(!(est_vide(nouveau_champ)));
                for (k=0;nouveau_champ[k]!='\n';){
                    k++;
                }
                nouveau_champ[k] = 0;
                tableau[modifierligne].profession= copie(nouveau_champ);
            }
        }
    }
}
int trouver(char scanprenom[],char scannom[],char scannum[], char scanmail[],int verif_suppr,int verif_modifier){ /*Fonction faite par Remi JARA*/
    int i,j=0,choix;/*initialisation des compteurs et du choix de client*/
    int liste[MAXTAB];/*initialisation du tableau qui va contenir les clients correspondant à la recherche*/
    for (i=0;tableau[i].prenom!=NULL;i++){
        if (strcmpi(tableau[i].prenom,scanprenom)==0 && strcmpi(tableau[i].nom,scannom)==0 && (strcmpi(tableau[i].num,scannum)==0 || strcmpi(tableau[i].mail,scanmail)==0)){
            liste[j] = tableau[i].id - 1;/*en parcourant tout le tableau, si on verifie les conditions de recherche (nom*prenom*(mail+mail)) on rentre l'id des clients dans notre liste*/
            j++;/*on incremente j pour obtenir la taille de la liste plus facilement*/
        }
    }
    int k;
    if (j>0){
        for(k=0;k<j;k++){/*on affiche tout les clients correspondant à la recherche*/
            printf("\nClient numero %d : %-3d %-20s | %-26s | %-20s | %-10s | %-20s | %-40s | %-22s \n",k,tableau[liste[k]].id,tableau[liste[k]].prenom,tableau[liste[k]].nom,tableau[liste[k]].adresse,tableau[liste[k]].code_postale,tableau[liste[k]].num,tableau[liste[k]].mail,tableau[liste[k]].profession);
        }
        if (verif_suppr){/*si on est dans le cas d'une suppression, on appelle la fonction correspondante*/
            do{
                printf("\nIndiquez quel client vous souhaitez supprimer en rentrant son indice ecrit ci-dessus : ");
                scanf("%d",&choix);
            }while(choix<0 || choix>j+1);
            supprimer(liste[choix]);
            printf("Le client a bien ete supprime");
            return 1;
        }
        else if(verif_modifier){/*si on est dans le cas d'une modification, on appelle la fonction correspondante*/
            do{
                printf("\nIndiquez quel client vous souhaitez modifier en rentrant son indice ecrit ci-dessus : ");
                scanf("%d",&choix);
            }while(choix<0 || choix>j+1);
            modifierclient(liste[choix]);
            printf("Le client a bien ete modifie");
            return 1;
        }
    }
    else{/*si la longueur de la liste vaut 0, la recherche n'a pas ete concluante*/
        printf("Aucun client ne rempli ces criteres\nVous pouvez l'ajouter si vous le souhaitez");
        return 0;
    }
    return 0;
}
int supprimer(int supprligne){/*Fonction faite par Remi JARA*/
    int i,j;/*Fonction faite par Remi JARA*/
    for (i=0;tableau[i].prenom!=NULL;){
        i++;                                /*boucle for permettant de trouver le nombre de client dans le tableau*/
    }
    tableau[supprligne].suppr = "suppr";/*on ajout l'etat suppr au client ayant l'id entre en argument*/
    for (j=supprligne;j<i;j++){
        tableau[j].id=tableau[j].id-1;
    }
    return 1;
}
void saisie_client(int verif_suppr,int verif_modifier){ /*Fonction faite par Remi JARA*/
    char verif[TAILLE_MAX+1];/*fonction permettant de recuperer un nom un prenom et une adresse mail ou un numero de telephone pour faire des recherches*/
    char num[TAILLE_MAX+1]="0",mail[TAILLE_MAX+1]="0",nom[TAILLE_MAX+1],prenom[TAILLE_MAX+1];
    int i;
    printf("Entrez le prenom du client que vous cherchez : ");
    fgets(prenom,TAILLE_MAX+1,stdin);
    printf("Entrez le nom du client que vous cherchez : ");
    fgets(nom,TAILLE_MAX+1,stdin);/*on scan le prenom et le nom du client voulu*/
    if(prenom[0]=='\n'){
        strcpy(prenom,"*Champ vide*");
    }
    else{
        for (i=0;prenom[i]!='\n';){
            i++;
        }
        prenom[i] = 0;
    }
    if(nom[0]=='\n'){
        strcpy(nom,"*Champ vide*");
    }
    else{
        for (i=0;nom[i]!='\n';){
            i++;
        }
        nom[i] = 0;
    }
    do{
    printf("Souhaitez vous entrer son email ou son numero de telephone ? \nPour l'email--> tapez \"mail\"\nPour le numero de telephone --> tapez \"tel\"\n");
    scanf("%s",verif);
    }while(strcmpi(verif,"mail")!=0 && strcmpi(verif,"tel")!=0);/*l'utilisateur veut il chercher avec le mail ou le numero de tel ? verification*/
    if (strcmpi(verif,"mail")==0){
        do{
        printf("Entrez le mail du client que vous cherchez : ");
        scanf("%s",mail);
        }while(!(est_mail(mail)));
        trouver(prenom,nom,num,mail,verif_suppr,verif_modifier);/*on lance la fonction permettant de trouver le client voulu avec soit un mail soit un numero de tel*/
    }                                                         /*les arguments verif_suppr et verif_modifier permettent de savoir dans quel cas nous nous trouvons*/
    else{                                                     /* (1,0) pour une suppression, (0,1) pour une modification, (0,0) pour une simple recherche*/
        do{
        printf("Entrez le numero de telephone du client que vous cherchez: ");
        scanf("%s",num);
        }while(!(est_num(num)));
        trouver(prenom,nom,num,mail,verif_suppr,verif_modifier);
    }
}
int est_champ(char * choix_filtre){/*Fonction faite par Remi JARA*//*fonction qui renvoit 1 si la valeur passe en argument est un champ valide, 0 sinon*/
    if (strcmpi(choix_filtre,"prenom")!=0&&strcmpi(choix_filtre,"nom")!=0&&strcmpi(choix_filtre,"profession")!=0&&strcmpi(choix_filtre,"code_postale")!=0){
        printf("\nErreur de selection de champ a filtrer\n");/* si l'un des champs entré n'est pas l'un des demandé, on renvoit une erreur et répète la demande*/
        return 0;
    }
    return 1;
}
int est_vide (char *mot){/*Fonction faite par Remi JARA*/
    int i,j=0;
    if (strcmp(mot,"\n")==0 || mot == NULL){
        return 0;/*si le mot vaut NULL ou retour à la ligne, il est vide*/
    }
    for(i=0;i<strlen(mot);i++){
        if (isspace(mot[i])){
            j++;
        }
    }
    if (j==strlen(mot)){/*si le mot contient autant d'espaces qu'il a de caractère, il est vide*/
        return 0;
    }
    return 1;/*sinon c'est bon il est valide*/
}
int est_zero_ou_un(char *choix){/*Fonction faite par Idrissa SALL*//*fonction qui renvoit 1 si la valeur passe en argument est un 0 ou un 1, renvoit 0 sinon*/
    if (strcmp(choix,"0")==0 || strcmp(choix,"1")==0 ){
        return 1;/*si le choix est soit un 1 soit un 2, c'est valide, sinon non*/
    }
    printf("\nErreur dans la selection\n");
    return 0;
}
int est_choix_filtre(char *choix){/*Fonction faite par Idrissa SALL*//*fonction qui renvoit 1 si la valeur passe en argument est un 0, 1, 2 ou 3 renvoit 0 sinon*/
    if (strcmp(choix,"0")==0 || strcmp(choix,"1")==0 || strcmp(choix,"2")==0 || strcmp(choix,"3")==0 ){
        return 1;/*si le choix est entre 0 et 3 compris, c'est valide, sinon non*/
    }
    printf("\nErreur dans la selection\n");
    return 0;
}
int est_num(char *num){ /*Fonction faite par Remi JARA*/
    int i,ctrverif = 0;/*fonction qui renvoit 1 si la valeur passe en argument est un numero de telephone valide, 0 sinon*/
    for (i=0;i<14;i++){/*boucle qui parcourt le numero*/
        if (i!=2&&i!=5&&i!=8&&i!=11){/*si on est a l'emplacement d'un chiffre on rentre dans le if*/
            if (isdigit(num[i])){
                ctrverif++;/*si c'est bien un chiffre, on incremente le compteur de verification*/
            }
        }
        else{
            if (num[i]==46){
                ctrverif++;/* si on est à l'emplacement d'un point, et que c'est bien un point, on incremente le commpteur de verification*/
            }
        }
    }
    if (ctrverif==14 && strlen(num)==14){/*si on a incremente 14 fois (nombre de caractère d'un numero, le numero est valide*/
        return 1;
    }
    else{
        printf("\nNumero de telephone non valide\nNorme des numeros de telephone : 00.00.00.00.00\n");/*sinon on renvoie un message d'erreur*/
        return 0;
    }
}
int est_mail(char *mail){ /*Fonction faite par Remi JARA*/
    int i=0;/*fonction qui renvoit 1 si la valeur passe en argument est une adresse mail valide, 0 sinon*/
    int taille_mail = strlen(mail);
    if (!(isalpha(mail[i]))){/*si le premier caractère n'est pas une lettre, l'email n'est pas valide*/
        printf("\nEmail non valide\nNorme des adresses email : ---@---.---\n");
        return 0;
    }
    int at=-1,point=-1;
    for (i=0;i<taille_mail;i++){
        if (mail[i]==64){
            at = i;
        }
        else if (mail[i]==46){/*boucle qui parcourt le mail, et qui verifie la presence d'un @ et d'un point*/
            point = i;
        }
    }
    if (point==-1||at==-1){/*si il n'y a pas de @ iu pas de point, l'email n'est pas valide*/
        printf("\nEmail non valide\nNorme des adresses email : ---@---.---\n");
        return 0;
    }
    if ((point >= (taille_mail - 1))){/*si le point est en dernière position*/
        printf("\nEmail non valide\nNorme des adresses email : ---@---.---\n");
        return 0;
    }
    return 1;/*l'email est bien valide*/
}
int est_code_postal(char *code_postale){ /*Fonction faite par Remi JARA*/
    int i,ctr=0;
    for (i=0;i<strlen(code_postale);i++){/*on incremente le compteur si chaque caractère du code postale est un chiffre*/
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
int est_fichier(char fichier[]){/*Fonction faite par Remi JARA*/
    int i;
    char *carac="<>:\"|?*\\/";/*on initialise une chaine contenant tout les caractères interdit pour un nom de fichier par windows*/
    for(i=0;i<strlen(fichier);i++){
        if (strchr(carac,fichier[i])!=NULL){/*si le nom du fichier contient l'un des caractères, on arrête la boucle et on indique l'erreur*/
            printf("Erreur dans la selection du nom du fichier\nLe nom ne peut pas contenir les caractères suivants : / \\ : ? : | < > * \"\n");
            return 0;
        }
    }
    return 1;
}
char *majuscule_nom(char *mot){/*Fonction faite par Idrissa SALL*/
    mot[0] = toupper(mot[0]);/*on met en majuscule le premier caractère du nom*/
    return mot;
}
char *majuscule_adresse(char *mot){/*Fonction faite par Idrissa SALL*/
    int i;
    for(i=0;i<strlen(mot);i++){
        mot[i]=toupper(mot[i]);/*on met en majuscule chaque caractère de la chaine de l'adresse*/
    }
    return mot;
}
void tri_prenom(int choix_sens_tri){/*Fonction faite par Idrissa SALL*/
    char *tempprenom, *tempnom, *tempadresse, *tempcode_postale, *tempnum, *tempmail, *tempprofession, *tempsuppr;
    int i,j,k,tempid;
    for (k=0;tableau[k].prenom!=NULL;){
        k++;
    }
    for (i = 0; i < k; i++){
        for (j = 0; j < k; j++){
            if(choix_sens_tri){
            /*le choix sens du tri permet de faire soit un tri croissant ou un tri decroissant*/
                if (strcmpi(tableau[i].prenom, tableau[j].prenom) < 0&& strcmp(tableau[i].prenom, "*Champ vide*")!=0){
                    tempid = tableau[i].id;
                    tempsuppr = tableau[i].suppr;
                    tempprenom = tableau[i].prenom;
                    tempnom = tableau[i].nom;
                    tempadresse = tableau[i].adresse;
                    tempcode_postale = tableau[i].code_postale;
                    tempnum = tableau[i].num;
                    tempmail = tableau[i].mail;
                    tempprofession = tableau[i].profession;
                    tableau[i] = tableau[j];
                    tableau[j].id = tempid;
                    tableau[j].suppr = tempsuppr;
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
                    tempsuppr = tableau[i].suppr;
                    tempprenom = tableau[i].prenom;
                    tempnom = tableau[i].nom;
                    tempadresse = tableau[i].adresse;
                    tempcode_postale = tableau[i].code_postale;
                    tempnum = tableau[i].num;
                    tempmail = tableau[i].mail;
                    tempprofession = tableau[i].profession;
                    tableau[i] = tableau[j];
                    tableau[j].id = tempid;
                    tableau[j].suppr = tempsuppr;
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
        if (strcmp(tableau[i].suppr,"ok")==0){
            printf("|%-5d | %-20s | %-26s | %-22s | %-16s | %-23s | %-40s | %-22s \n",tableau[i].id,tableau[i].prenom,tableau[i].nom,tableau[i].adresse,tableau[i].code_postale,tableau[i].num,tableau[i].mail,tableau[i].profession);
        }
    }
}
void tri_nom(int choix_sens_tri){/*Fonction faite par Idrissa SALL*/
    char *tempprenom, *tempnom, *tempadresse, *tempcode_postale, *tempnum, *tempmail, *tempprofession, *tempsuppr;
    int i, j,k,tempid;
    for (k=0;tableau[k].prenom!=NULL;){
        k++;
    }
    for (i = 0; i < k; i++){
        for (j = 0; j < k; j++){
            if(choix_sens_tri){
                if (strcmpi(tableau[i].nom, tableau[j].nom) < 0&& strcmp(tableau[i].nom, "*Champ vide*")!=0){
                    tempid = tableau[i].id;
                    tempsuppr = tableau[i].suppr;
                    tempprenom = tableau[i].prenom;
                    tempnom = tableau[i].nom;
                    tempadresse = tableau[i].adresse;
                    tempcode_postale = tableau[i].code_postale;
                    tempnum = tableau[i].num;
                    tempmail = tableau[i].mail;
                    tempprofession = tableau[i].profession;
                    tableau[i] = tableau[j];
                    tableau[j].id = tempid;
                    tableau[j].suppr = tempsuppr;
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
                    tempsuppr = tableau[i].suppr;
                    tempprenom = tableau[i].prenom;
                    tempnom = tableau[i].nom;
                    tempadresse = tableau[i].adresse;
                    tempcode_postale = tableau[i].code_postale;
                    tempnum = tableau[i].num;
                    tempmail = tableau[i].mail;
                    tempprofession = tableau[i].profession;
                    tableau[i] = tableau[j];
                    tableau[j].id = tempid;
                    tableau[j].suppr = tempsuppr;
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
        if (strcmp(tableau[i].suppr,"ok")==0){
            printf("|%-5d | %-20s | %-26s | %-22s | %-16s | %-23s | %-40s | %-22s \n",tableau[i].id,tableau[i].prenom,tableau[i].nom,tableau[i].adresse,tableau[i].code_postale,tableau[i].num,tableau[i].mail,tableau[i].profession);
        }
    }
}
void tri_profession(int choix_sens_tri){/*Fonction faite par Idrissa SALL*/
    char *tempprenom, *tempnom, *tempadresse, *tempcode_postale, *tempnum, *tempmail, *tempprofession, *tempsuppr;
    int i, j,k,tempid;
    for (k=0;tableau[k].prenom!=NULL;){
        k++;
    }
    for (i = 0; i < k; i++){
        for (j = 0; j < k; j++){
            if(choix_sens_tri){
                if (strcmpi(tableau[i].profession, tableau[j].profession) < 0 && strcmp(tableau[i].profession, "*Champ vide*")!=0){
                    tempid = tableau[i].id;
                    tempsuppr = tableau[i].suppr;
                    tempprenom = tableau[i].prenom;
                    tempnom = tableau[i].nom;
                    tempadresse = tableau[i].adresse;
                    tempcode_postale = tableau[i].code_postale;
                    tempnum = tableau[i].num;
                    tempmail = tableau[i].mail;
                    tempprofession = tableau[i].profession;
                    tableau[i] = tableau[j];
                    tableau[j].id = tempid;
                    tableau[j].suppr = tempsuppr;
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
                    tempsuppr = tableau[i].suppr;
                    tempprenom = tableau[i].prenom;
                    tempnom = tableau[i].nom;
                    tempadresse = tableau[i].adresse;
                    tempcode_postale = tableau[i].code_postale;
                    tempnum = tableau[i].num;
                    tempmail = tableau[i].mail;
                    tempprofession = tableau[i].profession;
                    tableau[i] = tableau[j];
                    tableau[j].id = tempid;
                    tableau[j].suppr = tempsuppr;
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
        if (strcmp(tableau[i].suppr,"ok")==0){
            printf("|%-5d | %-20s | %-26s | %-22s | %-16s | %-23s | %-40s | %-22s \n",tableau[i].id,tableau[i].prenom,tableau[i].nom,tableau[i].adresse,tableau[i].code_postale,tableau[i].num,tableau[i].mail,tableau[i].profession);
        }
    }
}
void tri_code_postale(int choix_sens_tri){/*Fonction faite par Idrissa SALL*/
    char *tempprenom, *tempnom, *tempadresse, *tempcode_postale, *tempnum, *tempmail, *tempprofession, *tempsuppr;
    int i, j,k,tempid;
    for (k=0;tableau[k].prenom!=NULL;){
        k++;
    }
    for (i = 0; i < k; i++){
        for (j = 0; j < k; j++){
            if(choix_sens_tri){
                if (strcmpi(tableau[i].code_postale, tableau[j].code_postale) < 0&& strcmp(tableau[i].code_postale, "*Champ vide*")!=0){
                    tempid = tableau[i].id;
                    tempsuppr = tableau[i].suppr;
                    tempprenom = tableau[i].prenom;
                    tempnom = tableau[i].nom;
                    tempadresse = tableau[i].adresse;
                    tempcode_postale = tableau[i].code_postale;
                    tempnum = tableau[i].num;
                    tempmail = tableau[i].mail;
                    tempprofession = tableau[i].profession;
                    tableau[i] = tableau[j];
                    tableau[j].id = tempid;
                    tableau[j].suppr = tempsuppr;
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
                    tempsuppr = tableau[i].suppr;
                    tempprenom = tableau[i].prenom;
                    tempnom = tableau[i].nom;
                    tempadresse = tableau[i].adresse;
                    tempcode_postale = tableau[i].code_postale;
                    tempnum = tableau[i].num;
                    tempmail = tableau[i].mail;
                    tempprofession = tableau[i].profession;
                    tableau[i] = tableau[j];
                    tableau[j].id = tempid;
                    tableau[j].suppr = tempsuppr;
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
        if (strcmp(tableau[i].suppr,"ok")==0){
            printf("|%-5d | %-20s | %-26s | %-22s | %-16s | %-23s | %-40s | %-22s \n",tableau[i].id,tableau[i].prenom,tableau[i].nom,tableau[i].adresse,tableau[i].code_postale,tableau[i].num,tableau[i].mail,tableau[i].profession);
        }
    }
}
int strcmpr(char * ch1, char * ch2){/*Fonction faite par Idrissa SALL*//*fonction pour comparer deux chaines*/

    int x=0 ,y=0;
    while(ch1[x] || ch2[y]){/*tant qu'une des deux chaines n'est pas vide on continue la comparaison*/
        if(ch1[x] != ch2[y]){/*condition pour arreter la comparaison de caractere. si rien ne se passe c'est à dire aucun arret,
                on retourne 0*/
            if(ch1[x] < ch2[y])/*par contre si ch1[x] < ch2[y] on retourne une valeur negative*/
                return -9;
            if(ch1[x] > ch2[y])/*et si ch1[x] > ch2[y] on retourne une valeur negative*/
                return 4;
        }
        if(ch1[x] != '\0')
            x++;
        if(ch2[y] != '\0')
            y++;
        /*les variables x et y s'incrementent si le caractere est different du caractere nul*/
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
    switch(paramfiltre){/*selon les choix de filtre de l'utilisateur on cherche là où se trouve sa chaine de caractere*/
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
                if(strnicmp(tableau[i].code_postale,c,t)==0&& strcmp(tableau[i].code_postale,"*Champ vide*")!=0){/*si on veut faire avec casse on peut utiliser strnicmp. sans casse on utilise ma fonction sntncmpr*/
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
    switch(paramfiltre){/*selon les choix de filtre de l'utilisateur on cherche là où se trouve sa chaine de caractere*/
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
    /*cette fonction permet de trouver la chaine passee en paramatre en milieu de mot*/
    /*contraire de la fonction exlu*/
    int j;
    for (j=0;tableau[j].prenom!=NULL;){
        j++;                                /*boucle for permettant de trouver le nombre de client dans le tableau*/
    }
    int i=0;
    switch(paramfiltre){
        case 0:
            for(i=0; i< j; i++){
                if(strcase(tableau[i].prenom,c)!=0&& strcmp(tableau[i].prenom,"*Champ vide*")!=0){/*si on veut faire avec casse on peut utiliser strstr. sans casse on utilise ma fonction strcase*/
                    afficher_client(tableau,i);
                }
            }
            break;
        case 1:
            for(i=0; i< j; i++){
                if(strcase(tableau[i].nom,c)!=0&& strcmp(tableau[i].nom,"*Champ vide*")!=0){/*si on veut faire avec casse on peut utiliser strstr. sans casse on utilise ma fonction strcase*/
                    afficher_client(tableau,i);
                }
            }
            break;
        case 2:
            for(i=0; i< j; i++){
                if(strcase(tableau[i].code_postale,c)!=0&& strcmp(tableau[i].code_postale,"*Champ vide*")!=0){/*si on veut faire avec casse on peut utiliser strstr. sans casse on utilise ma fonction sntncmpr*/ /*on affiche chaque champ de chaque client du tableau*/
                    afficher_client(tableau,i);
                }
            }
            break;
        case 3:
            for(i=0; i< j; i++){
                if(strcase(tableau[i].profession,c)!=0&& strcmp(tableau[i].profession,"*Champ vide*")!=0){/*si on veut faire avec casse on peut utiliser strstr. sans casse on utilise ma fonction sntncmpr*/

                    afficher_client(tableau,i);
                }
            }
            break;
        default:
            break;
    }
}
void exclu(char c[],int paramfiltre){/*Fonction faite par Idrissa SALL*//*exclure la chaine tapee*/
    /*la fonction permet d'exclure le caractere  qu'on a passé en parametre*/
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
char* strcase( const char* chaine1, const char* chaine2 ){/*Fonction faite par Idrissa SALL*/
    const char *pt1 = chaine1 , *pt2 = chaine2 ;
    const char *r = *pt2 == 0 ? chaine1 : 0 ;/*char* r est egal ch1 si (*pt2==0) sinon c'est egale à 0*/

    while( *pt1 != 0 && *pt2 != 0 ){
            /*tolower permet de convertir les majuscule en minuscule et se trouve dans <ctype.h>*/
        if( tolower( (unsigned char)*pt1 ) == tolower( (unsigned char)*pt2 ) ){
        /*on entre dans le if lorsque pt1 et pt2 sont egaux en minuscle*/
            if( r == 0 )/*lorsque r n'est pas egale à ch1*/
                r = pt1 ;/*on l'affecte pt1 et puis on incremente pt2*/
            pt2++ ;
        }
        else{/*dans le cas où pt1 n'est pas egal en pt2 apres conversion en minuscle*/
            pt2 = chaine2 ;
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
    /*fonction similaire à stricmp dans la bibliotheque string.h*/
    int x=0 ,y=0,i=0;
    if (taille==0)/*pas necessaire le code marche sans mais il faut laisser comme ca*/
        return 0;
    while(i<taille){
        if(ch1[x] != ch2[y]){/*condition d'arret de la comparaison et retourne une valeur differente de 0 selon quelle chaine est superieur à l'autre*/
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
    /*une fontion similaire à strncmpr sauf que celle ci compare les fin de caractere de la chaine*/
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
void sauvegarder(){/*Fonction faite par Remi JARA*/
    char choixsauv[1];
    int choix;
    do{
    printf("Comment voulez-vous sauvegarder les modifications ?\n  - Dans un nouveau fichier --> tapez \"1\"\n  - En ecrasant le fichier actuel --> tapez \"0\"\n");
    scanf("%s",choixsauv);
    }while(!(est_zero_ou_un(choixsauv)));/*on choisit le type de modification avec vérification*/
    choix = atoi(choixsauv);
    int i=0;
    if(choix==0){/*modification avec suppression du fichier actuel*/
        FILE *fichiersauv= fopen(nouveau_chemin,"a+");
        printf("bingo");
        if (fichiersauv == NULL)
        {
            printf("Erreur de lecture du fichier\n"); /*verification qu'il n'y a aucune erreur avec le fichier créé*/
            exit(EXIT_FAILURE);
        }
        while (tableau[i].prenom!=NULL){/*on parcours chaque client*/
            if (strcmp(tableau[i].suppr,"suppr")!=0){/*si le client a été supprimé on ne l'écrit pas dans le fichier csv*/
                fprintf(fichiersauv,"%s,%s,%s,%s,%s,%s,%s\n",strcmp(tableau[i].prenom,"*Champ vide*")==0 ? "" : tableau[i].prenom,
                                                            strcmp(tableau[i].nom,"*Champ vide*")==0 ? "" : tableau[i].nom,
                                                            strcmp(tableau[i].adresse,"*Champ vide*")==0 ? "" : tableau[i].adresse,
                                                            strcmp(tableau[i].code_postale,"*Champ vide*")==0 ? "" : tableau[i].code_postale,
                                                            strcmp(tableau[i].num,"*Champ vide*")==0 ? "" : tableau[i].num,
                                                            strcmp(tableau[i].mail,"*Champ vide*")==0 ? "" : tableau[i].mail,
                                                            strcmp(tableau[i].profession,"*Champ vide*")==0 ? "" : tableau[i].profession);

            }
            i++;
            printf("%d",i);
        }
        printf("bingofin");
        fclose(fichiersauv);
        remove(chemin);/*on ferme le nouveau fichier, supprime l'ancien et renomme le nouveau avec le nom d'origine*/
        rename(nouveau_chemin, chemin);
    }
    else{
        char nomfichier[200]={"vide"};
        do{
            if (strcmp(nomfichier,"vide")!=0)printf("Choisissez un nom de fichier : ");
            fgets(nomfichier,200,stdin);
        }while(!(est_vide(nomfichier)&&est_fichier(nomfichier)));/*vérification du nom du fichier*/
        for (i=0;nomfichier[i]!='\n';){
            i++;
        }
        nomfichier[i]=0;
        strcat(nomfichier,".csv");
        FILE *fichiersauv= fopen(nomfichier,"a+");
        if (fichiersauv == NULL)
        {
            printf("Erreur de lecture du fichier\n"); /*verification qu'il n'y a aucune erreur avec le fichier*/
            exit(EXIT_FAILURE);
        }
        i=0;
        while (tableau[i].prenom!=NULL){
            if (strcmp(tableau[i].suppr,"suppr")!=0){/*si le client a été supprimé on ne l'écrit pas dans le fichier csv*/
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
        printf("\nVotre fichier %s a bien ete enregistre\n",nomfichier);
    }
}
void menu(){ /*Fonction faite par Remi JARA */
    do{
        printf("\nChoisis une action a realiser : \n  - Ajout de client --> tapez \"ajout\"\n  - Modifier un client --> tapez \"modifier\" \n  - Supprimer un client --> tapez \"suppr\"\n  - Afficher la base de donnees --> tapez \"afficher\" \n  - Rechercher un client --> tapez \"recherche\"\n - Sauvegarder les modifications --> tapez \"sauvegarder\"\n - Quitter l'application --> tapez \"stop\"\n");
        /*on scan l'action que l'utilisateur veut realiser*/
        gets(choix);
        if (strcmpi(choix, "afficher")==0){
            afficher();
        }
        else if (strcmpi(choix, "ajout")==0){
            ajout();
        }
        else if (strcmpi(choix, "modifier")==0){
            saisie_client(0,1);
        }
        else if(strcmpi(choix,"suppr")==0){
            saisie_client(1,0);
        }
        else if (strcmpi(choix,"recherche")==0){
            saisie_client(0,0);
        }
        else if (strcmpi(choix,"sauvegarder")==0){
            sauvegarder();
        }
    }while(strcmpi(choix,"stop")!=0);
}
/*norme c90*/
