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
    char *suppr;
}sclient;
sclient tableau[MAXTAB];
char *strdupp (const char *s);
char *copie(char *str);
char * strtok_empty (char * str, char const * sep);
void ajout();
void menu();
void afficher();
void filtrer(char *choix_filtre,char *filtre,char * choixchoix_filtre);
void modifierclient(int modifierligne);
void remplir(int modifier, int supprimer, sclient *client);
void tri_prenom(int choix_sens_tri);
void tri_code_postale(int choix_sens_tri);
void tri_nom(int choix_sens_tri);
void tri_profession(int choix_sens_tri);
void sauvegarder();
int strcmpr(char * ch1, char * ch2);
void commencant(char c[],int paramfiltre);
void terminant(char c[],int paramfiltre);
void recherche(char c[],int paramfiltre);
void exclu(char c[],int paramfiltre);
void afficher_client(sclient *tableau,int i);
int strncmpr(char * ch1, char * ch2, int taille);
int strcmpi(const char*,const char*);
int strnicmp(const char*,const char*, size_t);
int strinvcmpr(char * ch1, char * ch2, int taille);
char* strcase( const char* ch1, const char* ch2 );
void saisie_client(int verif_suppr,int verif_modifier);
int supprimer(int supprligne);
int trouver (char scanprenom[],char scannom[],char scannum[], char scanmail[],int verif_suppr,int verif_modifier);
int est_code_postal(char *code_postale);
int est_choix_filtre(char *choix);
int est_vide (char *mot);
int est_fichier(char fichier[]);
int est_zero_ou_un(char * choix);
int est_champ(char * choix_filtre);
int est_num(char *num);
int est_mail(char *mail);
char *majuscule_nom(char *mot);
char *majuscule_adresse(char *mot);

#endif
