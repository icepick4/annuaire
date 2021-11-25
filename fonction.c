#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fonction.h"
#include <ctype.h>
#define TAILLE_MAX 256
#define chemin "annuaire5000_test.csv"
#define MAXTAB 100000
char choix[TAILLE_MAX+1],choix_tri[TAILLE_MAX+1],choix_affiche[TAILLE_MAX+1],
choixchoix_filtre[TAILLE_MAX+1],choix_filtre[TAILLE_MAX+1],filtre[TAILLE_MAX+1],choix_affichage[TAILLE_MAX+1];
char * champ[8] = {"Id : ","Prenom : ","Nom : ","Adresse : ","Code Postale : ","Numero de telephone : ","Adresse Mail : ","Profession : "},ligne[TAILLE_MAX+1];
const char *sep = ",";
char *token;
sclient tableau[MAXTAB];
void remplir(int modifier, int supprimer,sclient *client){ /*Fonction faite par Rémi JARA*/
    FILE *fichier= fopen(chemin,"a+"); /*On ouvre le fichier csv*/
    int i=0;
    if (modifier == 0 && supprimer == 0){
        if (fichier == NULL)
        {
            printf("Erreur de lecture du fichier\n");
            exit(EXIT_FAILURE);
        }
        while(fgets(ligne,TAILLE_MAX+1,fichier)){
            char * token = strtok_empty(ligne, "," );
            int j = 0;
            while (token){

                if (j==0){
                    if (strlen(token)>0){
                        client[i].prenom = strdup(token);
                    }
                    else{
                        client[i].prenom = strdup("*Champ vide*");
                    }
                }
                else if (j==1){
                    if (strlen(token)>0){
                        client[i].nom = strdup(token);
                    }
                    else{
                        client[i].nom = strdup("*Champ vide*");
                    }
                }
                else if (j==2){
                    if (strlen(token)>0){
                        client[i].adresse = strdup(token);
                    }
                    else{
                        client[i].adresse = strdup("*Champ vide*");
                    }
                }
                else if (j==3){
                    if (strlen(token)>0){
                        client[i].code_postale = strdup(token);
                    }
                    else{
                        client[i].code_postale = strdup("*Champ vide*");
                    }
                }
                else if (j==4){
                    if (strlen(token)>0){
                        client[i].num = strdup(token);
                    }
                    else{
                        client[i].num = strdup("*Champ vide*");
                    }
                }
                else if (j==5){
                    if (strlen(token)>0){
                        client[i].mail = strdup(token);
                    }
                    else{
                        client[i].mail = strdup("*Champ vide*");
                    }
                }
                else if (j==6){
                    if (token[strlen(token)-1]=='\n'){
                        token[strlen(token)-1]='\0';
                    }
                    if (strlen(token)>0){
                        client[i].profession = strdup(token);
                    }
                    else{
                        client[i].profession = strdup("*Champ vide*");
                    }
                }
                j++;
                token = strtok_empty (NULL,",");
            }
            client[i].deleted = strdup("ok");
            client[i].id = i+1;
            i++;
        }
        tableau[i].prenom=NULL;
        fclose(fichier);
    }
}
void insertion (int t[],int len_t){ /*Fonction faite par Rémi JARA*/
    int i,h,c;
    for(i=1;i<len_t;i++){
        while((i>0) && (t[i]<t[i-1])){
            c=t[i];
            t[i]=t[i-1];
            t[i-1]=c;
            i=i-1;
        }
    }
    for (h = 0; h < len_t; h++) {
      printf("\ntableau[%d] = %d", h, t[h]);
   }
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
    char nom[TAILLE_MAX+1],prenom[TAILLE_MAX+1],adresse[TAILLE_MAX+1],code_postale[TAILLE_MAX+1],num[TAILLE_MAX+1],mail[TAILLE_MAX+1],profession[TAILLE_MAX+1];
    printf("Prenom : ");
    scanf("%s",&prenom);
    printf("Nom : ");
    scanf("%s",&nom);
    printf("Ville : ");
    scanf("%s",&adresse);
    do{
        printf("Code postale : ");
        scanf("%s",&code_postale);
    }while(!(est_code_postal(code_postale)));
    do{
        printf("Numero de telephone : ");
        scanf("%s",&num);
    }while(!(est_num(num)));
    do{
        printf("Adresse email : ");
        scanf("%s",&mail);
    }while(!(est_mail(mail)));
    printf("Profession : ");
    scanf("%s",&profession);
    int i;
    for (i=0;tableau[i].prenom!=NULL;){
        i++;
    }
    tableau[i].id = i+1;
    tableau[i].prenom = strdup(prenom);
    tableau[i].nom = strdup(nom);
    tableau[i].adresse = strdup(adresse);
    tableau[i].code_postale = strdup(code_postale);
    tableau[i].num = strdup(num);
    tableau[i].mail = strdup(mail);
    tableau[i].profession = strdup(profession);
    tableau[i].deleted = strdup("ok");
    printf("Le client a bien ete ajoute\n");
}
void afficher(){ /*Fonction faite par Rémi JARA*/
    printf("Voulez vous afficher les donnees avec un filtre ou un tri ? \n  - Pour un filtre --> tapez \"filtre\" \n  - Pour un tri --> tapez \"tri\" \n  - Si vous voulez uniquement afficher la base de donnees --> tapez \"non\" \n  - Si vous voulez afficher les clients auquels il manque un ou plusieurs champs --> tapez \"manquant\"\n");
    scanf("%s",choix_affiche);
    if (strcmpi(choix_affiche,"tri")==0){
        choixtri : printf("Par quel champ souhaitez vous trier les clients ? \n  - Pour trier par leur prenom --> tapez \"prenom\"\n  - Pour trier par leur nom --> tapez \"nom\"\n  - Pour trier par leur code postaux --> tapez \"code_postale\"\n  - Pour trier par leur profession --> tapez \"profession\"\n");
        scanf("%s",&choix_tri);
        if (strcmpi(choix_tri,"prenom")==0){
            int choix_sens_tri;
            printf("Souhaitez vous un affichage croissant (1) ou décroissant (0) ? : ");
            scanf("%d",&choix_sens_tri);
            switch(choix_sens_tri){
                case 0:
                    tri_prenom(0);
                    break;
                case 1:
                    tri_prenom(1);
                default:
                    printf("Erreur dans la sélection");
                    goto choixtri;
            }
        }
        else if (strcmpi(choix_tri,"nom")==0){
            int choix_sens_tri;
            printf("Souhaitez vous un affichage croissant (1) ou décroissant (0) ? : ");
            scanf("%d",&choix_sens_tri);
            switch(choix_sens_tri){
                case 0:
                    tri_nom(0);
                    break;
                case 1:
                    tri_nom(1);
                default:
                    printf("Erreur dans la sélection");
                    goto choixtri;
            }
        }
        else if (strcmpi(choix_tri,"code_postale")==0){
            int choix_sens_tri;
            printf("Souhaitez vous un affichage croissant (1) ou décroissant (0) ? : ");
            scanf("%d",&choix_sens_tri);
            switch(choix_sens_tri){
                case 0:
                    tri_code_postale(0);
                    break;
                case 1:
                    tri_code_postale(1);
                    break;
                default:
                    printf("Erreur dans la sélection");
                    goto choixtri;
            }
        }
        else if (strcmpi(choix_tri,"profession")==0){
            int choix_sens_tri;
            printf("Souhaitez vous un affichage croissant (1) ou décroissant (0) ? : ");
            scanf("%d",&choix_sens_tri);
            switch(choix_sens_tri){
                case 0:
                    tri_profession(0);
                    break;
                case 1:
                    printf("oui");
                    tri_profession(1);
                default:
                    printf("Erreur dans la sélection");
                    goto choixtri;
            }
        }
        else{
            printf("Erreur dans la sélection");
            goto choixtri;
        }
    }
    else if (strcmpi(choix_affiche,"filtre")==0){

        choixchoixfiltre : printf("Voulez vous filtrer avec la premiere lettre ou un champ precis ?\n  - Pour une seule lettre --> tapez \"oui\" \n  - Pour un champ precis --> tapez \"non\"\n");
        scanf("%s",&choixchoix_filtre);
        if (strcmpi(choixchoix_filtre,"oui")!=0&&strcmpi(choixchoix_filtre,"non")!=0){
            printf("\nErreur de selection\n");
            goto choixchoixfiltre;
        }
        choixchampfiltre : printf("Par quel champ voulez vous filtrer ? \n  - Pour un filtre par prenom --> tapez \"prenom\" \n  - Pour un filtre par nom --> tapez \"nom\" \n  - Pour un filtre par profession --> tapez \"profession\"\n  - Pour un filtre par code postale --> tapez \"code_postale\" \n");
        scanf("%s",&choix_filtre);
        if (strcmpi(choix_filtre,"prenom")!=0&&strcmpi(choix_filtre,"nom")!=0&&strcmpi(choix_filtre,"profession")!=0&&strcmpi(choix_filtre,"code_postale")!=0){
            printf("\nErreur de selection de filtre\n");
            goto choixchampfiltre;
        }
        choixfiltre : printf("Indiquez le filtre que vous souhaitez appliquer : ");
        scanf("%s",&filtre);
        if (strcmpi(choix_filtre,"code_postale")==0&&strcmpi(choixchoix_filtre,"oui")!=0){
            if (est_code_postal(filtre)){
                filtre_code_postale(filtre);
            }
            else{
                printf("\nCode postale non valide\nNorme des codes postaux : 00000\n");
                goto choixfiltre;
            }
        }
        else if (strcmpi(choix_filtre,"prenom")==0){
            filtre_prenom(filtre,choixchoix_filtre);
        }
        else if (strcmpi(choix_filtre,"nom")==0){
            filtre_nom(filtre,choixchoix_filtre);
        }
        else if (strcmpi(choix_filtre,"profession")==0){
            filtre_profession(filtre,choixchoix_filtre);
        }
    }
    else{
        int j,i,k=0;
        for (j=0;tableau[j].prenom!=NULL;){
            j++;
        }
        printf("|%-5s | %-20s | %-26s | %-22s | %-16s | %-23s | %-40s | %-22s \n",champ[0],champ[1],champ[2],champ[3],champ[4],champ[5],champ[6],champ[7]);

        for (i=0;i<j;i++)
        {
            if (strcmpi(choix_affiche,"manquant")!=0){

                if (strcmpi(tableau[i].deleted,"ok")==0){
                    printf("|%-5d | %-20s | %-26s | %-22s | %-16s | %-23s | %-40s | %-22s \n",tableau[i].id,tableau[i].prenom,tableau[i].nom,tableau[i].adresse,tableau[i].code_postale,tableau[i].num,tableau[i].mail,tableau[i].profession);
                }
            }
            else if (strcmpi(choix_affiche,"manquant")==0){
                if (strcmp(tableau[i].deleted,"ok")==0 && strcmp(tableau[i].prenom,"*Champ vide*")==0||strcmp(tableau[i].nom,"*Champ vide*")==0||strcmp(tableau[i].adresse,"*Champ vide*")==0||strcmp(tableau[i].code_postale,"*Champ vide*")==0||strcmp(tableau[i].num,"*Champ vide*")==0||strcmp(tableau[i].mail,"*Champ vide*")==0||strcmp(tableau[i].profession,"*Champ vide*")==0){
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
void filtre_prenom(char *filtre,char *choixchoix_filtre){ /*Fonction faite par Rémi JARA*/
    int j,i;
    for (j=0;tableau[j].prenom!=NULL;){
        j++;
    }
    printf("|%-5s | %-20s | %-26s | %-22s | %-16s | %-23s | %-40s | %-22s \n",champ[0],champ[1],champ[2],champ[3],champ[4],champ[5],champ[6],champ[7]);

    for (i=0;i<j;i++)
    {   if(strcmpi(tableau[i].prenom,filtre)==0){
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
void modifierclient(int modifierligne){

    int tableauChoix[7],i=0,j,choix;
    printf("Quel champs voulez vous modifier ?\n");
    do{
    printf("Prenom ?\n  - Oui --> tapez \"1\"\n  - Non --> tapez \"0\"\n");
    scanf("%d",&choix);
    }while(!(est_zero_ou_un(choix)));
    tableauChoix[i] = choix;
    i++;
    printf("Nom ?\n  - Oui --> tapez \"1\"\n  - Non --> tapez \"0\"\n");
    scanf("%d",&choix);
    tableauChoix[i] = choix;
    i++;
    printf("Adresse ?\n  - Oui --> tapez \"1\"\n  - Non --> tapez \"0\"\n");
    scanf("%d",&choix);
    tableauChoix[i] = choix;
    i++;
    printf("Code postale ?\n  - Oui --> tapez \"1\"\n  - Non --> tapez \"0\"\n");
    scanf("%d",&choix);
    tableauChoix[i] = choix;
    i++;
    printf("Numero de telephone ?\n  - Oui --> tapez \"1\"\n  - Non --> tapez \"0\"\n");
    scanf("%d",&choix);
    tableauChoix[i] = choix;
    i++;
    printf("Adresse email ?\n  - Oui --> tapez \"1\"\n  - Non --> tapez \"0\"\n");
    scanf("%d",&choix);
    tableauChoix[i] = choix;
    i++;
    printf("Profession ?\n  - Oui --> tapez \"1\"\n  - Non --> tapez \"0\"\n");
    scanf("%d",&choix);
    tableauChoix[i] = choix;
    for (j=0;j<7;j++){
        if (tableauChoix[j]){
            char newchamp[TAILLE_MAX+1];
            if (j==0){
                printf("%s",champ[j+1]);
                scanf("%s",&newchamp);
                tableau[modifierligne].prenom= strdup(newchamp);
            }
            if (j==1){
                printf("%s",champ[j+1]);
                scanf("%s",&newchamp);
                tableau[modifierligne].nom= strdup(newchamp);
            }
            if (j==2){
                printf("%s",champ[j+1]);
                scanf("%s",&newchamp);
                tableau[modifierligne].adresse= strdup(newchamp);
            }
            if (j==3){
                do{
                    printf("%s",champ[j+1]);
                    scanf("%s",&newchamp);
                }while (!(est_code_postal(newchamp)));
                tableau[modifierligne].code_postale= strdup(newchamp);
            }
            if (j==4){
                do{
                    printf("%s",champ[j+1]);
                    scanf("%s",&newchamp);
                }while (!(est_num(newchamp)));
                tableau[modifierligne].num= strdup(newchamp);
            }
            if (j==5){
                do{
                    printf("%s",champ[j+1]);
                    scanf("%s",&newchamp);
                }while (!(est_mail(newchamp)));
                tableau[modifierligne].mail= strdup(newchamp);
            }
            if (j==6){
                tableau[modifierligne].profession= strdup(newchamp);
            }
        }
    }
}
int trouver(char * scanprenom,char * scannom,char * scannum, char *scanmail,int checksuppr,int checkmodifier){ /*Fonction faite par Rémi JARA*/
    int i,j=0,choix;
    int liste[MAXTAB];
    for (i=0;tableau[i].prenom!=NULL;i++){
        if (strcmpi(tableau[i].prenom,scanprenom)==0 && strcmpi(tableau[i].nom,scannom)==0 && (strcmp(tableau[i].num,scannum)==0 || strcmpi(tableau[i].mail,scanmail)==0)){
            liste[j] = tableau[i].id - 1;
            j++;
        }
    }
    int k;
    if (j>0){
        for(k=0;k<j;k++){
            printf("\nClient numero %d : %-3d %-20s | %-26s | %-20s | %-10s | %-20s | %-40s | %-22s \n",k,tableau[liste[k]].id,tableau[liste[k]].prenom,tableau[liste[k]].nom,tableau[liste[k]].adresse,tableau[liste[k]].code_postale,tableau[liste[k]].num,tableau[liste[k]].mail,tableau[liste[k]].profession);
        }
        if (checksuppr){
            printf("\nIndiquez quel client vous souhaitez supprimer en rentrant son indice ecrit ci-dessus : ");
            scanf("%d",&choix);
            if (suppr(liste[choix])){
                printf("Le client a bien ete supprime");
                return 1;
            }
        }
        else if(checkmodifier){
            printf("\nIndiquez quel client vous souhaitez modifier en rentrant son indice ecrit ci-dessus : ");
            scanf("%d",&choix);
            modifierclient(liste[choix]);
            printf("Le client a bien ete Modifier");
            return 1;
        }
    }
    else{
        printf("Aucun client ne rempli ces criteres\nVous pouvez l'ajouter si vous le souhaitez");
        return 0;
    }
    return 0;
}
int suppr(int supprligne){ /*Fonction faite par Rémi JARA*/
    tableau[supprligne].deleted = "deleted";
    return 1;
}
void input(int checksuppr,int checkmodifier){ /*Fonction faite par Rémi JARA*/
    char verif[TAILLE_MAX+1];
    char num[TAILLE_MAX+1]="0",mail[TAILLE_MAX+1]="0",nom[TAILLE_MAX+1],prenom[TAILLE_MAX+1];
    printf("Entrez le prenom du client que vous cherchez : ");
    scanf("%s",&prenom);
    printf("Entrez le nom du client que vous cherchez : ");
    scanf("%s",&nom);
    do{
    printf("Souhaitez vous entrer son email ou son numero de telephone ? \nPour l'email--> tapez \"mail\"\nPour le numero de telephone --> tapez \"tel\"\n");
    scanf("%s",&verif);
    }while(strcmpi(verif,"mail")!=0 && strcmpi(verif,"tel")!=0);
    if (strcmpi(verif,"mail")==0){
        do{
        printf("Entrez le mail du client que vous cherchez : ");
        scanf("%s",&mail);
        }while(!(est_mail(mail)));
        trouver(prenom,nom,num,mail,checksuppr,checkmodifier);
    }
    else{
        do{
        printf("Entrez le numero de telephone du client que vous cherchez: ");
        scanf("%s",&num);
        }while(!(est_num(num)));
        trouver(prenom,nom,num,mail,checksuppr,checkmodifier);
    }
}
int est_zero_ou_un(int choix){
    if (choix==0 || choix==1){
        return 1;
    }
    return 0;
}
int est_num(char *num){ /*Fonction faite par Rémi JARA*/
    int i,ctrcheck = 0;
    for (i=0;i<14;i++){
        if (i!=2&&i!=5&&i!=8&&i!=11){
            if (isdigit(num[i])){
                ctrcheck++;
            }
        }
        else{
            if (num[i]==46){
                ctrcheck++;
            }
        }
    }
    if (ctrcheck==14 && strlen(num)==14){
        return 1;
    }
    else{
        printf("\nNumero de telephone non valide\nNorme des numeros de telephone : 00.00.00.00.00\n");
        return 0;
    }
}
int est_mail(char *mail){ /*Fonction faite par Rémi JARA*/
    int i=0;
    int len_mail = strlen(mail);
    if (!(isalpha(mail[i]))){
        printf("\nEmail non valide\nNorme des adresses email : ---@---.---\n");
        return 0;
    }
    int at=-1,point=-1;
    for (i=0;i<len_mail;i++){
        if (mail[i]==64){
            at = i;
        }
        else if (mail[i]==46){
            point = i;
        }
    }
    if (point==-1||at==-1){
        printf("\nEmail non valide\nNorme des adresses email : ---@---.---\n");
        return 0;
    }
    if ((point >= (len_mail - 1))){
        printf("\nEmail non valide\nNorme des adresses email : ---@---.---\n");
        return 0;
    }
    return 1;
}
int est_code_postal(char *code_postale){ /*Fonction faite par Rémi JARA*/
    int i,ctr=0;
    for (i=0;i<strlen(code_postale);i++){
        if (isdigit(code_postale[i])){
            ctr++;
        }
    }
    if (ctr==5){
        return 1;
    }
    printf("\nCode postale non valide\nNorme des codes postaux : 00000\n");
    return 0;
}
void tri_prenom(int choix_sens_tri){
    char *tempprenom, *tempnom, *tempadresse, *tempcode_postale, *tempnum, *tempmail, *tempprofession, *tempdeleted;
    int i,j,k,tempid;
    for (k=0;tableau[k].prenom!=NULL;){
        k++;
    }
    for (i = 0; i < k; i++){
        for (j = 0; j < k; j++){
            if(choix_sens_tri){
                if (strcmpi(tableau[i].prenom, tableau[j].prenom) < 0&& strcmp(tableau[i].prenom, "*Champ vide*")!=0){
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
void tri_nom(int choix_sens_tri){
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
void tri_profession(int choix_sens_tri){
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
void tri_code_postale(int choix_sens_tri){

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
void menu(){ /*Fonction faite par Rémi JARA */
    debut : printf("\nChoisis une action a realiser : \n  - Ajout de client --> tapez \"ajout\"\n  - Modifier un client --> tapez \"modifier\" \n  - Supprimer un client --> tapez \"suppr\"\n  - Afficher la base de donnees --> tapez \"afficher\" \n  - Rechercher un client --> tapez \"recherche\"\n");
    scanf("%s",&choix);
    if (strcmpi(choix, "afficher")==0){
        afficher("non");
        goto debut;
    }
    else if (strcmpi(choix, "ajout")==0){
        ajout();
        goto debut;
    }
    else if (strcmpi(choix, "modifier")==0){
        input(0,1);
        goto debut;
    }
    else if(strcmpi(choix,"suppr")==0){
        input(1,0);
        goto debut;
    }
    else if(strcmpi(choix,"stop")==0){
    }
    else if (strcmpi(choix,"recherche")==0){
        input(0,0);
        goto debut;
    }
    else{
        goto debut;
    }
}
