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

typedef struct structclient{
    int id;
    char *prenom;
    char *nom;
    char *adresse;
    char *code_postale;
    char *num;
    char *mail;
    char *profession;
    char *deleted;
}sclient;
sclient tableau[MAXTAB];
void remplir_ligne(char*line, sclient *client,int id){
    char * tab[8];
    char * token = strtok_empty( line, "," );
    int ctr = 0;
    while (token) {
        tab[ctr] = token;
        token = strtok_empty (NULL,",");
        ctr++;
    }

    if (tab[6][strlen(tab[6])-1] == '\n') tab[6][strlen(tab[6])-1] = '\0';
    client->id = id;/*
    if (strlen(tab[0])>0){
        client->prenom = strdup(tab[0]);
    }
    else{
        client->prenom = "<empty>";
    }*/

    client->prenom = strlen(tab[0]) > 0 ? strdup(tab[0]) : "<empty>";
    client->nom = strlen(tab[1]) > 0 ? strdup(tab[1]) : "<empty>";
    client->adresse = strlen(tab[2]) > 0 ? strdup(tab[2]) : "<empty>";
    client->code_postale = strlen(tab[3]) > 0 ? strdup(tab[3]) : "<empty>";
    client->num = strlen(tab[4]) > 0 ? strdup(tab[4]) : "<empty>";
    client->mail = strlen(tab[5]) > 0 ? strdup(tab[5]) : "<empty>";
    client->profession = strlen(tab[6]) > 0 ? strdup(tab[6]) : "<empty>";
    client->deleted = strlen(tab[7]) > 0 ? "ok" : "ok";
}

void remplir(int modifier, int supprimer){
    FILE *fichier= fopen(chemin,"a+");
    int i=0;
    if (modifier == 0 && supprimer == 0){
        if (fichier == NULL)
        {
            printf("Erreur de lecture du fichier\n");
            exit(EXIT_FAILURE);
        }
        while(fgets(ligne,TAILLE_MAX+1,fichier)){
            remplir_ligne(ligne,&tableau[i],i+1);
            i++;
        }
        tableau[i].prenom=NULL;
        fclose(fichier);
    }
}
void insertion (int t[],int len_t){
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
char * strtok_empty (char * str, char const * sep){
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

void ajout(char *nom, char *prenom, char *adresse, char *code_postale, char *num, char *mail, char *profession){
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
void afficher(char *choix_tri){
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
            if (strcmp(tableau[i].deleted,"ok")==0 && strcmp(tableau[i].prenom,"<empty>")==0||strcmp(tableau[i].nom,"<empty>")==0||strcmp(tableau[i].adresse,"<empty>")==0||strcmp(tableau[i].code_postale,"<empty>")==0||strcmp(tableau[i].num,"<empty>")==0||strcmp(tableau[i].mail,"<empty>")==0||strcmp(tableau[i].profession,"<empty>")==0){
            printf("|%-5d | %-20s | %-26s | %-22s | %-16s | %-23s | %-40s | %-22s \n",tableau[i].id,tableau[i].prenom,tableau[i].nom,tableau[i].adresse,tableau[i].code_postale,tableau[i].num,tableau[i].mail,tableau[i].profession);
            k++;
            }
        }
    }
    if (strcmp(choix_tri,"manquant")==0){
        printf("Le fichier client contient %d client avec un ou plusieurs champs manquants",k);
    }
}
void filtrer(char *choix_filtre,char *filtre,char *choixchoix_filtre){
    int j,i;
    for (j=0;tableau[j].prenom!=NULL;){
        j++;
    }
    printf("|%-5s | %-20s | %-26s | %-22s | %-16s | %-23s | %-40s | %-22s \n",field[0],field[1],field[2],field[3],field[4],field[5],field[6],field[7]);

    for (i=0;i<j;i++)
    {

        if (strcmp(choixchoix_filtre,"non")==0){
            if (strcmp(choix_filtre,"prenom")==0){
                if(strcmp(tableau[i].prenom,filtre)==0){
                    if (strcmp(tableau[i].deleted,"ok")==0){
                        printf("|%-5d | %-20s | %-26s | %-22s | %-16s | %-23s | %-40s | %-22s \n",tableau[i].id,tableau[i].prenom,tableau[i].nom,tableau[i].adresse,tableau[i].code_postale,tableau[i].num,tableau[i].mail,tableau[i].profession);
                    }
                }
            }
            else if (strcmp(choix_filtre,"nom")==0){
                if(strcmp(tableau[i].nom,filtre)==0){
                    if (strcmp(tableau[i].deleted,"ok")==0){
                        printf("|%-5d | %-20s | %-26s | %-22s | %-16s | %-23s | %-40s | %-22s \n",tableau[i].id,tableau[i].prenom,tableau[i].nom,tableau[i].adresse,tableau[i].code_postale,tableau[i].num,tableau[i].mail,tableau[i].profession);

                    }
                }
            }
            else if (strcmp(choix_filtre,"profession")==0){
                if(strcmp(tableau[i].profession,filtre)==0){
                    if (strcmp(tableau[i].deleted,"ok")==0){
                        printf("|%-5d | %-20s | %-26s | %-22s | %-16s | %-23s | %-40s | %-22s \n",tableau[i].id,tableau[i].prenom,tableau[i].nom,tableau[i].adresse,tableau[i].code_postale,tableau[i].num,tableau[i].mail,tableau[i].profession);
                    }
                }
            }
            else if (strcmp(choix_filtre,"code_postale")==0){
                if(strcmp(tableau[i].code_postale,filtre)==0){
                    if (strcmp(tableau[i].deleted,"ok")==0){
                        printf("|%-5d | %-20s | %-26s | %-22s | %-16s | %-23s | %-40s | %-22s \n",tableau[i].id,tableau[i].prenom,tableau[i].nom,tableau[i].adresse,tableau[i].code_postale,tableau[i].num,tableau[i].mail,tableau[i].profession);
                    }
                }
            }
        }
        else{
            if (strcmp(choix_filtre,"prenom")==0){
                if(strcmp(tableau[i].prenom,filtre)==0){
                    printf("OUI");
                    if (strcmp(tableau[i].deleted,"ok")==0){
                    printf("%-10d | %-20s | %-26s | %-30s | %-10s | %-20s | %-40s | %-22s \n",tableau[i].id,tableau[i].prenom,tableau[i].nom,tableau[i].adresse,tableau[i].code_postale,tableau[i].num,tableau[i].mail,tableau[i].profession);
                    }
                }
            }
            else if (strcmp(choix_filtre,"nom")==0){
                if(strcmp(tableau[i].nom,filtre)==0){
                    if (strcmp(tableau[i].deleted,"ok")==0){
                    printf("%-10d | %-20s | %-26s | %-30s | %-10s | %-20s | %-40s | %-22s \n",tableau[i].id,tableau[i].prenom,tableau[i].nom,tableau[i].adresse,tableau[i].code_postale,tableau[i].num,tableau[i].mail,tableau[i].profession);
                    }
                }
            }
            else if (strcmp(choix_filtre,"profession")==0){
                if(strcmp(tableau[i].profession,filtre)==0){
                    if (strcmp(tableau[i].deleted,"ok")==0){
                    printf("%-10d | %-20s | %-26s | %-30s | %-10s | %-20s | %-40s | %-22s \n",tableau[i].id,tableau[i].prenom,tableau[i].nom,tableau[i].adresse,tableau[i].code_postale,tableau[i].num,tableau[i].mail,tableau[i].profession);
                    }
                }
            }
        }
    }
}
int trouver(char * scanprenom,char * scannom,char * scannum, char *scanmail,int checksuppr){
    int i,j=0,choix;
    int liste[MAXTAB];
    for (i=0;tableau[i].prenom!=NULL;i++){
        if (strcmp(tableau[i].prenom,scanprenom)==0 && strcmp(tableau[i].nom,scannom)==0 && strcmp(tableau[i].num,scannum)==0 || strcmp(tableau[i].mail,scanmail)==0){
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
}
int suppr(int supprligne){
    tableau[supprligne].deleted = "deleted";
    return 1;

}

int est_num(char *num){
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
int est_mail(char *mail){
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
int est_code_postal(char *code_postale){
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
