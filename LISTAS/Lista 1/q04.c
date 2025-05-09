#include <stdio.h>
#include <stdlib.h> 

int ler3Num(int numeros[]){
    for(int i = 0; i < 3; i++){
        printf("Digite o %d numero:", i+1);
        scanf("%d", &numeros[i]);
    }

    printf("Os numeros informados foram:");
    for(int i = 0; i < 3; i++){
        printf("%d ", numeros[i]);
    }
    return 0; // Return a valid integer value
}

int main(){
    int numeros[3]; 
    ler3Num(numeros);
    return 0;
}