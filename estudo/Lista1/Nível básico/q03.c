#include <stdio.h>
#include <stdlib.h>

int main(){
    float n1, n2, n3;

    printf("Digite suas 3 notas:\n");
    scanf("%f", &n1);
    scanf("%f", &n2);
    scanf("%f", &n3);
    float media = (n1+n2+n3)/3;
    printf("Media = %.1f", media);
}