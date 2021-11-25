#ifndef FONCTION_DOT_H
#define FONCTION_DOT_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define TAILLE_MAX 256
#define MAXTAB 100000

void insertion(int t[],int len_t); /*initialisation de la fonction d'algorithme de tri*/
void ajout();
void afficher();
void filtrer(char *choix_filtre,char *filtre,char * choixchoix_filtre);
int suppr(int supprligne);
int trouver (char * scanprenom,char * scannom,char * scannum, char *scanmail,int checksuppr,int checkmodifier);
int est_num(char *num);
char * strtok_empty (char * str, char const * sep);
int est_mail(char *mail);
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
int est_code_postal(char *code_postale);
int est_zero_ou_un(int choix);
void menu();

#endif
