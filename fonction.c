#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fonction.h"
#include <ctype.h>
#define TAILLE_MAX 256
#define chemin "annuaire5000_test.csv"
#define MAXTAB 100000
char choix[TAILLE_MAX+1],choix_tri[TAILLE_MAX+1],choix_affiche[TAILLE_MAX+1],
choixchoix_filtre[TAILLE_MAX+1],choix_filtre[TAILLE_MAX+1],filtre[TAILLE_MAX+1];
char * field[8] = {"Id : ","Prenom : ","Nom : ","Adresse : ","Code Postale : ","Numero de telephone : ","Adresse Mail : ","Profession : "},ligne[TAILLE_MAX+1];
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
void ajout(){ /*Fonction faite par Rémi JARA*/
    char nom[TAILLE_MAX+1],prenom[TAILLE_MAX+1],adresse[TAILLE_MAX+1],code_postale[TAILLE_MAX+1],num[TAILLE_MAX+1],mail[TAILLE_MAX+1],profession[TAILLE_MAX+1];
    printf("Prenom : ");
    scanf("%s",&prenom);
    printf("Nom : ");
    scanf("%s",&nom);
    printf("Ville : ");
    scanf("%s",&adresse);
    scan_ajout_codepostale : printf("Code postale : ");
    scanf("%s",&code_postale);
    if (!(est_code_postal(code_postale))){
        printf("\nCode postale non valide\nNorme des codes postaux : 00000\n");
        goto scan_ajout_codepostale;
    }
    scan_ajout_num : printf("Numero de telephone : ");
    scanf("%s",&num);
    if (!(est_num(num))){
        printf("\nNumero de telephone non valide\nNorme des numeros de telephone : 00.00.00.00.00\n");
        goto scan_ajout_num;
    }
    scan_ajout_mail : printf("Adresse email : ");
    scanf("%s",&mail);
    if (!(est_mail(mail))){
        printf("\nEmail non valide\nNorme des adresses email : ---@---.---\n");
        goto scan_ajout_mail;
    }
    printf("Profession : ");
    scanf("%s",&profession);
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
    printf("Le client a bien ete ajoute\n");
}
void afficher(char *choix_tri){ /*Fonction faite par Rémi JARA*/
    printf("Voulez vous afficher les donnees avec un filtre ou un tri ? \n  - Pour un filtre --> tapez \"filtre\" \n  - Pour un tri --> tapez \"tri\" \n  - Si vous voulez uniquement afficher la base de donnees --> tapez \"non\" \n");
    scanf("%s",choix_affiche);
    if (strcmp(choix_affiche,"tri")==0){
        /*choisir le tri voulu*/
    }
    else if (strcmp(choix_affiche,"filtre")==0){
        choixchoixfiltre : printf("Voulez vous filtrer avec la premiere lettre ou un champ precis ?\n  - Pour une seule lettre --> tapez \"oui\" \n  - Pour un champ precis --> tapez \"non\"\n");
        scanf("%s",&choixchoix_filtre);
        if (strcmp(choixchoix_filtre,"oui")!=0&&strcmp(choixchoix_filtre,"non")!=0){
            printf("\nErreur de selection\n");
            goto choixchoixfiltre;
        }
        choixchampfiltre : printf("Par quel champ voulez vous filtrer ? \n  - Pour un filtre par prenom --> tapez \"prenom\" \n  - Pour un filtre par nom --> tapez \"nom\" \n  - Pour un filtre par profession --> tapez \"profession\"\n  - Pour un filtre par code postale --> tapez \"code_postale\" \n");
        scanf("%s",&choix_filtre);
        if (strcmp(choix_filtre,"prenom")!=0&&strcmp(choix_filtre,"nom")!=0&&strcmp(choix_filtre,"profession")!=0&&strcmp(choix_filtre,"code_postale")!=0){
            printf("\nErreur de selection de filtre\n");
            goto choixchampfiltre;
        }
        choixfiltre : printf("Indiquez le filtre que vous souhaitez appliquer : ");
        scanf("%s",&filtre);
        if (strcmp(choix_filtre,"code_postale")==0&&strcmp(choixchoix_filtre,"oui")!=0){
            if (est_code_postal(filtre)){
                filtre_code_postale(filtre);
            }
            else{
                printf("\nCode postale non valide\nNorme des codes postaux : 00000\n");
                goto choixfiltre;
            }
        }
        else if (strcmp(choix_filtre,"prenom")==0){
            filtre_prenom(filtre,choixchoix_filtre);
        }
        else if (strcmp(choix_filtre,"nom")==0){
            filtre_nom(filtre,choixchoix_filtre);
        }
        else if (strcmp(choix_filtre,"profession")==0){
            filtre_profession(filtre,choixchoix_filtre);
        }
    }
    else{
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
void modifier(){
    input(0,1);
}
void modifierclient(int modifierligne){
    char newchamp[TAILLE_MAX+1];
    int tableauChoix[7],i=0,j,choix;
    printf("Quel champs voulez vous modifier ?\n");
    printf("Prenom ? \"1\" / \"0\" : ");
    scanf("%d",&choix);
    tableauChoix[i] = choix;
    i++;
    printf("Nom ? \"1\" / \"0\" : ");
    scanf("%d",&choix);
    tableauChoix[i] = choix;
    i++;
    printf("Adresse ? \"1\" / \"0\" : ");
    scanf("%d",&choix);
    tableauChoix[i] = choix;
    i++;
    printf("Code postale ? \"1\" / \"0\" : ");
    scanf("%d",&choix);
    tableauChoix[i] = choix;
    i++;
    printf("Numero de telephone ? \"1\" / \"0\" : ");
    scanf("%d",&choix);
    tableauChoix[i] = choix;
    i++;
    printf("Adresse email ? \"1\" / \"0\" : ");
    scanf("%d",&choix);
    tableauChoix[i] = choix;
    i++;
    printf("Profession ? \"1\" / \"0\" : ");
    scanf("%d",&choix);
    tableauChoix[i] = choix;
    for (j=0;j<7;j++){
        if (tableauChoix[j]){
            printf("%s",field[j+1]);
            gets(newchamp);
            if (j==0){
                tableau[modifierligne].prenom=newchamp;
                printf("%s",tableau[modifierligne].prenom);
            }
            if (j==1){
                tableau[modifierligne].nom= newchamp;
            }
            if (j==2){
                tableau[modifierligne].adresse= newchamp;
            }
            if (j==3){
                tableau[modifierligne].code_postale= newchamp;
            }
            if (j==4){
                tableau[modifierligne].num= newchamp;
            }
            if (j==5){
                tableau[modifierligne].mail= newchamp;
            }
            if (j==6){
                tableau[modifierligne].profession= newchamp;
            }

        }
    }
    return 1;
}
int trouver(char * scanprenom,char * scannom,char * scannum, char *scanmail,int checksuppr,int checkmodifier){ /*Fonction faite par Rémi JARA*/
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
void input(int checksuppr,int checkmodifier){
    char verif[TAILLE_MAX+1];
    char num[TAILLE_MAX+1],mail[TAILLE_MAX+1],nom[TAILLE_MAX+1],prenom[TAILLE_MAX+1];
    printf("Entrez le prenom du client que vous cherchez : ");
    scanf("%s",&prenom);
    printf("Entrez le nom du client que vous cherchez : ");
    scanf("%s",&nom);
    scan_critere : printf("Souhaitez vous entrer son email ou son numero de telephone ? \nPour l'email--> tapez \"mail\"\nPour le numero de telephone --> tapez \"tel\"\n");
    scanf("%s",&verif);
    if (strcmp(verif,"mail")==0){
        scanmail : printf("Entrez le mail du client que vous cherchez : ");
        scanf("%s",&mail);
        if (est_mail(mail)){
            if (checksuppr){
                trouver(prenom,nom,"0",mail,1,0);
            }
            else if (checkmodifier){
                trouver(prenom,nom,"0",mail,0,1);
            }
            else{
                trouver(prenom,nom,"0",mail,0,0);
            }
        }
        else{
            printf("\nEmail non valide\nNorme des adresses email : ---@---.---\n");
            goto scanmail;
        }
    }
    else if (strcmp(verif,"tel")==0){
        scannum : printf("Entrez le numero de telephone du client que vous cherchez: ");
        scanf("%s",&num);
        if (est_num(num)){
            if (checksuppr){
                trouver(prenom,nom,"0",mail,1,0);
            }
            else if (checkmodifier){
                trouver(prenom,nom,"0",mail,0,1);
            }
            else{
                trouver(prenom,nom,"0",mail,0,0);
            }
        }
        else{
            printf("\nNumero de telephone non valide\nNorme des numeros de telephone : 00.00.00.00.00\n");
            goto scannum;
        }
    }
    else{
        printf("\nErreur dans la selection\n");
        goto scan_critere;
    }
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

void menu(){ /*Fonction faite par Rémi JARA */
    debut : printf("\nChoisis une action a realiser : \n  - Ajout de client --> tapez \"ajout\" \n  - Afficher la base de donnees --> tapez \"afficher\" \n  - Supprimer un client --> tapez \"suppr\"\n  - Rechercher un client --> tapez \"recherche\"\n  - Afficher tous les clients auquels il manque un ou plusieurs champ(s) --> tapez \"manquant\" \n ");
    scanf("%s",&choix);
    if (strcmp(choix, "afficher")==0){
        afficher("non");
        goto debut;
    }
    else if (strcmp(choix, "ajout")==0){
        ajout();
        goto debut;
    }
    else if (strcmp(choix, "modifier")==0){
        modifier();
        goto debut;
    }
    else if(strcmp(choix,"suppr")==0){
        input(1,0);
        goto debut;
    }
    else if(strcmp(choix,"stop")==0){
    }
    else if (strcmp(choix,"recherche")==0){
        input(0,0);
        goto debut;
    }
    else if (strcmp(choix,"manquant")==0){
        afficher("manquant");
        goto debut;
    }
    else{
        goto debut;
    }
}
