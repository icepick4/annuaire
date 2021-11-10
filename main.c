#include <stdio.h>

int selection(int t[], int len_t){
    int i,j,c,mini;
    for (i=0;i<len_t;i++){
        printf("itération %d",i);
        mini=i;
        for (j=0;i+1<len_t;j++){
            if (t[j]<t[mini]){
                mini=j;
            }
        }
        c = t[i];
        t[i]=t[mini];
        t[mini]=c;

    int h;
    for (h = 0; h < len_t; h++) {
      printf("\ntableau[%d] = %d", h, t[i]);
   }
/*def Insertion(t,n):
    for i in range(1,n):
        while (i>0)and(t[i]<t[i-1]):
            c = t[i]
            t[i] = t[i-1]
            t[i-1] = c
            i = i-1
    return t*/
}}
int main(){
    int tab[7] = {25,13,2,14,36,15,1};
    selection(tab,7);
}
