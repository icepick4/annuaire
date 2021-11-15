#include <stdio.h>
#include <stdlib.h>
#define TAILLE_MAX 256
int insertion(int t[],int len_t);
int insertion (int t[],int len_t){
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
    return t;
}
int main(){
    int tab[7] = {25,13,2,14,36,15,1};
    insertion(tab,(sizeof tab / sizeof tab[0]));
    return 0;
}
