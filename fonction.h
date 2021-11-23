void insertion(int t[],int len_t); /*initialisation de la fonction d'algorithme de tri*/
void ajout(char *nom, char *prenom, char *adresse, char *code_postale, char *num, char *mail, char *profession);
void afficher(char *choix_tri);
void filtrer(char *choix_filtre,char *filtre,char * choixchoix_filtre);
int suppr(int supprligne);
int trouver (char * scanprenom,char * scannom,char * scannum, char *scanmail,int checksuppr);
int est_num(char *num);
char * strtok_empty (char * str, char const * sep);
int est_mail(char *mail);

