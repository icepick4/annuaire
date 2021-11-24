#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fonction.h"
#include <ctype.h>
#define TAILLE_MAX 256
#define chemin "annuaire5000_test.csv"
#define MAXTAB 100000

char * field[8] = {"Id : ","Prenom : ","Nom : ","Adresse : ","Code Postale : ","Numero de telephone : ","Adresse Mail : ","Profession : "},ligne[TAILLE_MAX+1];
const char *sep = ",";
char *token;
sclient tableau[MAXTAB];
void remplir(int modifier, int supprimer,sclient *client){ /*Fonction faite par Rémi JARA*/
    FILE *fichier= fopen(chemin,"a+");
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
                        client[i].prenom = strdup("Champ vide");
                    }
                }
                else if (j==1){
                    if (strlen(token)>0){
                        client[i].nom = strdup(token);
                    }
                    else{
                        client[i].nom = strdup("Champ vide");
                    }
                }
                else if (j==2){
                    if (strlen(token)>0){
                        client[i].adresse = strdup(token);
                    }
                    else{
                        client[i].adresse = strdup("Champ vide");
                    }
                }
                else if (j==3){
                    if (strlen(token)>0){
                        client[i].code_postale = strdup(token);
                    }
                    else{
                        client[i].code_postale = strdup("Champ vide");
                    }
                }
                else if (j==4){
                    if (strlen(token)>0){
                        client[i].num = strdup(token);
                    }
                    else{
                        client[i].num = strdup("Champ vide");
                    }
                }
                else if (j==5){
                    if (strlen(token)>0){
                        client[i].mail = strdup(token);
                    }
                    else{
                        client[i].mail = strdup("Champ vide");
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
                        client[i].profession = strdup("Champ vide");
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

void ajout(char *nom, char *prenom, char *adresse, char *code_postale, char *num, char *mail, char *profession){ /*Fonction faite par Rémi JARA*/
    int i;
    for (i=0;tableau[i].prenom!=NULL;){
        i++;
    }
    tableau[i].id = i+1;
    tableau[i].prenom = prenom;
    tableau[i].nom = nom;
    tableau[i].adresse = adresse;
    tableau[i].code_postale = code_postale;
    tableau[i].num = num;
    tableau[i].mail = mail;
    tableau[i].profession = profession;
    tableau[i].deleted = "ok";
}
void afficher(char *choix_tri){ /*Fonction faite par Rémi JARA*/
    int j,i,k=0;
    for (j=0;tableau[j].prenom!=NULL;){
        j++;
    }
    printf("|%-5s | %-20s | %-26s | %-22s | %-16s | %-23s | %-40s | %-22s \n",field[0],field[1],field[2],field[3],field[4],field[5],field[6],field[7]);

    for (i=0;i<j;i++)
    {
        if (strcmp(choix_tri,"manquant")!=0){

            if (strcmp(tableau[i].deleted,"ok")==0){
                printf("|%-5d | %-20s | %-26s | %-22s | %-16s | %-23s | %-40s | %-22s \n",tableau[i].id,tableau[i].prenom,tableau[i].nom,tableau[i].adresse,tableau[i].code_postale,tableau[i].num,tableau[i].mail,tableau[i].profession);
            }
        }
        else if (strcmp(choix_tri,"manquant")==0){
            if (strcmp(tableau[i].deleted,"ok")==0 && strcmp(tableau[i].prenom,"Champ vide")==0||strcmp(tableau[i].nom,"Champ vide")==0||strcmp(tableau[i].adresse,"Champ vide")==0||strcmp(tableau[i].code_postale,"Champ vide")==0||strcmp(tableau[i].num,"<empty>")==0||strcmp(tableau[i].mail,"<empty>")==0||strcmp(tableau[i].profession,"<empty>")==0){
            printf("|%-5d | %-20s | %-26s | %-22s | %-16s | %-23s | %-40s | %-22s \n",tableau[i].id,tableau[i].prenom,tableau[i].nom,tableau[i].adresse,tableau[i].code_postale,tableau[i].num,tableau[i].mail,tableau[i].profession);
            k++;
            }
        }
    }
    if (strcmp(choix_tri,"manquant")==0){
        printf("Le fichier client contient %d client avec un ou plusieurs champs manquants",k);
    }
}
void filtre_prenom(char *filtre,char *choixchoix_filtre){ /*Fonction faite par Rémi JARA*/
    int j,i;
    for (j=0;tableau[j].prenom!=NULL;){
        j++;
    }
    printf("|%-5s | %-20s | %-26s | %-22s | %-16s | %-23s | %-40s | %-22s \n",field[0],field[1],field[2],field[3],field[4],field[5],field[6],field[7]);

    for (i=0;i<j;i++)
    {   if(strcmp(tableau[i].prenom,filtre)==0){
            if (strcmp(tableau[i].deleted,"ok")==0){
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
    printf("|%-5s | %-20s | %-26s | %-22s | %-16s | %-23s | %-40s | %-22s \n",field[0],field[1],field[2],field[3],field[4],field[5],field[6],field[7]);

    for (i=0;i<j;i++)
    {
        if(strcmp(tableau[i].nom,filtre)==0){
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
    printf("|%-5s | %-20s | %-26s | %-22s | %-16s | %-23s | %-40s | %-22s \n",field[0],field[1],field[2],field[3],field[4],field[5],field[6],field[7]);

    for (i=0;i<j;i++)
    {
        if(strcmp(tableau[i].profession,filtre)==0){
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
    printf("|%-5s | %-20s | %-26s | %-22s | %-16s | %-23s | %-40s | %-22s \n",field[0],field[1],field[2],field[3],field[4],field[5],field[6],field[7]);

    for (i=0;i<j;i++)
    {
        if(strcmp(tableau[i].code_postale,filtre)==0){
            if (strcmp(tableau[i].deleted,"ok")==0){
                printf("|%-5d | %-20s | %-26s | %-22s | %-16s | %-23s | %-40s | %-22s \n",tableau[i].id,tableau[i].prenom,tableau[i].nom,tableau[i].adresse,tableau[i].code_postale,tableau[i].num,tableau[i].mail,tableau[i].profession);
            }
        }
    }
}
int trouver(char * scanprenom,char * scannom,char * scannum, char *scanmail,int checksuppr){ /*Fonction faite par Rémi JARA*/
    int i,j=0,choix;
    int liste[MAXTAB];
    for (i=0;tableau[i].prenom!=NULL;i++){
        if (strcmp(tableau[i].prenom,scanprenom)==0 && strcmp(tableau[i].nom,scannom)==0 && (strcmp(tableau[i].num,scannum)==0 || strcmp(tableau[i].mail,scanmail)==0)){
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
            else{
                printf("Erreur dans la suppression");
                return 0;
            }
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

int est_num(char *num){ /*Fonction faite par Rémi JARA*/
    int i,ctrcheck = 0;
    for (i=0;i<14;i++){
        if (i == 0 || i == 1 || i == 3 || i == 4 || i == 6 || i == 7 || i == 9 || i == 10 || i == 12 || i == 13){
            if (isdigit(num[i])){
                ctrcheck=ctrcheck+1;
            }
        }
        else{
            if (num[i] == '.') {
                ctrcheck=ctrcheck+1;
            }
        }
    }
    if (ctrcheck==14 && strlen(num)==14){
        return 1;
    }
    else{
        return 0;
    }
}
int est_mail(char *mail){ /*Fonction faite par Rémi JARA*/
    int i=0;
    int len_mail = strlen(mail);
    if (i == 0&&!(isalpha(mail[i]))){
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
        return 0;
    }
    if ((point >= (len_mail - 1))){
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
    return 0;
}
