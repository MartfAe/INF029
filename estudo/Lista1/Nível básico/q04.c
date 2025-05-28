#include <stdio.h>
#include <stdlib.h>

int main() {
    int v1;
    printf("Digite um valor:");
    scanf("%d", &v1);
    if(v1%2==0){
        printf("Numero par!");
    }else{
        printf("Numero impar");
    }
    return 0;
}