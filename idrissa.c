#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fonction.h"
#include <ctype.h>
#define T 50
#define MENU 7
#define TAILLE_MAX 256
#define chemin "annuaire5000_test - Copie.csv"
/* ma fontion main qui qui va avec les fonctions
int main()
{
    int o=1;
    while (o !=-1){
        menu();
        o=choose();
    }
    return 0;
}*/


char * field[7] = {"Prenom:","Nom:","Adresse:","Code Postale:","Numero de telephone:","Adresse Mail:","Profession:"},ligne[TAILLE_MAX+1];
typedef struct structclient{
    char prenom[T];
    char nom[T];
    char adresse[T];
    char code_postale[T];
    char num[16];
    char mail[T];
    char profession[T];
}sclient;



void menu()
{
    int i =0;
    char* menu[MENU]={"1:Ajout de client","2:Afficher la base de donnee","3:Modifier un client",
    "4:Supprimer un client","5:Rechercher un client",
    "6:Quitter"};
    for (i=0; i <MENU; i++)
        printf("%s\n",menu[i]);
}
int choose()
{   char choix[3];

    printf("votre choix: ");
    gets(choix);
    switch(*choix)
    {
    case '1':
        ajout();
        return 1;
    case '2':
        printf("Afficher la base de donnee\n");
        afficher_base();
        return 2;
    case '3': printf("Modifier un client\n");
        return 3;
    case '4': printf("Supprimer un client\n");
        return 4;
    case '5': printf("Rechercher un client\n");
        return 5;
    case '6': printf("Au revoir\n\n");
        return -1;
    default: printf("Verifier votre choix\n\n");
        return 0;

    }
return 0;
}

int ajout()/*ajouter un client*/
{
    int i;
    char b[2];
    char str[50];
    /*char * champ[7] = {"Prenom","Nom","Adresse","Code Postale","Numero de telephone","Adresse Mail","Profession"};*/
    FILE *fichier= fopen(chemin,"a+");
    if (fichier==NULL)
    {
        printf("no such file.");
        return 0;
    }
    do{
        printf("Ajouter un client\n");
        fprintf(fichier,"\n");

    for (i=0; i<7; i++)
    {
        printf("Entrer %s ",field[i]);
        gets(str);
        fprintf(fichier,"%s,", str);
    }
        printf("pour quitter taper zero:");
        gets(b);
    }while(*b != '0');
    printf("client enregistre avec succes.\n");
    fclose(fichier);


    return 0;
}

void afficher(char *tab [], int taille)
{
    int i;
    for(i=0; i < taille; i++){
    printf("%s ",tab[i]);
   }
    printf("\n");
}

void commencant(char * tab[], char c[], int taille)/*recherche en debut de mot*/
{
    int t;
    t=strlen(c);
    int i=0;
    for(i=0; i< taille; i++){
        if(strnicmp(tab[i],c,t)==0)/*si on veut faire avec casse on peut utiliser strnicmp. sans casse on utilise ma fonction sntncmpr*/
            printf("%s ",tab[i]);
    }
}
void terminant(char * tab[], char c[], int taille)/*recherche en fin de mot*/
{
    int t;
    t=strlen(c);
    int i=0;
    for(i=0; i< taille; i++){
        if(strinvcmpr(tab[i],c,t)==0)
            printf("%s ",tab[i]);
    }
}
void recherche(char * tab[], char c[], int taille)/*recherche au milieu du mot*/
{
    int i=0;
    for(i=0; i< taille; i++){
        if(strstr(tab[i],c)!=0)
            printf("%s ",tab[i]);
    }
}
void exclu(char * tab[], char c[], int taille)/*exclure la chaine tapée*/
{
    int i=0;
    for(i=0; i< taille; i++){
        if(strstr(tab[i],c)==0)
            printf("%s ",tab[i]);
    }
}
int strcmpr(char * ch1, char * ch2)/*fonction pour comparer deux chaines*/
{
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

int strncmpr(char * ch1, char * ch2, int taille)/*fonction pour comparer deux chaines avec de nombre de car en parametre*/
{
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
int strinvcmpr(char * ch1, char * ch2, int taille)/*fonction pour comparer deux chaines avec de nombre de carac en parametre depuis la fin de chaine*/
{
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


void tri_CRO(char *tab[], int taille)
 {
   char *temp;
   int i, j;

   for (i = 0; i < taille; i++){
    for (j = 0; j < taille; j++){
      if (strcmpi(tab[i], tab[j]) < 0){
          temp = tab[i];
          tab[i] = tab[j];
          tab[j] = temp;
        }
    }
   }
  }
void tri_DEC(char *tab[], int taille)
 {
   char *temp;
   int i, j;

   for (i = 0; i < taille; i++){
    for (j = 0; j < taille; j++){
      if (strcmpi(tab[i], tab[j]) > 0){
          temp = tab[i];
          tab[i] = tab[j];
          tab[j] = temp;
        }
    }
   }
  }
