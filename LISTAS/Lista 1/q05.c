#include <stdio.h>
#include <stdlib.h>
typedef struct Numeros
{   
    int num[4];
}Numeros;

Numeros ler4Num(){
    Numeros numeros;
    for(int i =0; i<4; i++){
        printf("Digite o valor %d de 4:", i+1);
        scanf("%d", &numeros.num[i]);
    }

    return numeros;
}


int main(){
    Numeros numerosLidos = ler4Num();

    printf("Os 4 numeros lidos sao:");
    for(int i =0; i<4; i++){
        printf("%d ", numerosLidos.num[i]);
    }

    return 0;
}