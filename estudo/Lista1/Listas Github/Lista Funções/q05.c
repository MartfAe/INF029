#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int numeros[4];
}QuatroNumeros;

QuatroNumeros ler4Numeros(){
    QuatroNumeros numerosLidos;
    for(int i =0; i <4; i++){
        printf("Digite o %dº numero de 4:", i+1);
        scanf("%d", &numerosLidos.numeros[i]);
    }
    return numerosLidos;
}

int main() {
    QuatroNumeros numerosLidos;

    numerosLidos= ler4Numeros();
    printf("Numeros lidos:\n");

    for(int i =0; i<4;i++){
        printf("%d", numerosLidos.numeros[i]);
    }

    
    return 0;
}