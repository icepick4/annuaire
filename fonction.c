#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fonction.h"
#define TAILLE_MAX 256
#define chemin "annuaire5000_test.csv"
char * field[7] = {"Prenom : ","Nom : ","Adresse : ","Code Postale : ","Numero de telephone : ","Adresse Mail : ","Profession : "},ligne[TAILLE_MAX+1];
const char *sep = ",";
char *token;
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
    FILE *fichier= fopen(chemin,"a+");
    fprintf(fichier,"%s,%s,%s,%s,%s,%s,%s\n",nom,prenom,adresse,code_postale,num,mail,profession);
    fclose(fichier);
}
void afficher(){
    FILE *fichier= fopen(chemin,"a+");
    if (fichier == NULL)
    {
        printf("Erreur de lecture du fichier\n");
        exit(EXIT_FAILURE);
    }
    while(fgets(ligne,TAILLE_MAX+1,fichier))
        {
            int i = 0;
            printf("----------------------------------------------------\n\n");
            token = strtok_empty(ligne,",");
            while(token!=NULL)
            {
                i++;
                printf("%s%s\n",field[i-1], *token ? token : "<empty>");
                token  = strtok_empty(NULL, ",");
            }

        }
    fclose(fichier);
}
void suppr(char * num){
    FILE *fichier= fopen(chemin,"a+")/*,*temp_fichier = fopen()*/;
    if (fichier == NULL)
    {
        printf("Erreur de lecture du fichier\n");
        exit(EXIT_FAILURE);
    }

    while(fgets(ligne,TAILLE_MAX+1,fichier)){
        char *temp[TAILLE_MAX+1];
        strcpy(temp,ligne);
        token = strtok(ligne,",");
        while(token!=NULL)
        {
            /*printf("%s\n",token);*/
            if(strcmp(token,num)==0){
                printf("Bingo");
                printf("%s",&temp);
            }
            token  = strtok(NULL, ",");
        }
    }
    fclose(fichier);
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
