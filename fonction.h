#ifndef FONCTION_DOT_H
#define FONCTION_DOT_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define TAILLE_MAX 256
#define MAXTAB 100000

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

char *copie(char *str);
char * strtok_empty (char * str, char const * sep);
void ajout();
void menu();
void afficher();
void filtrer(char *choix_filtre,char *filtre,char * choixchoix_filtre);
void modifierclient(int modifierligne);
void remplir(int modifier, int supprimer, sclient *client);
void filtre_prenom(char *filtre,char *choixchoix_filtre);
void filtre_nom(char *filtre,char *choixchoix_filtre);
void filtre_profession(char *filtre,char *choixchoix_filtre);
void filtre_code_postale(char *filtre);
void tri_prenom(int choix_sens_tri);
void tri_code_postale(int choix_sens_tri);
void tri_nom(int choix_sens_tri);
void tri_profession(int choix_sens_tri);
void input(int checksuppr,int checkmodifier);
int suppr(int supprligne);
int trouver (char * scanprenom,char * scannom,char * scannum, char *scanmail,int checksuppr,int checkmodifier);
int est_code_postal(char *code_postale);
int est_zero_ou_un(char * choix);
int est_champ(char * choix_filtre);
int est_num(char *num);
int est_mail(char *mail);

#endif
