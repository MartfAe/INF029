#include <stdio.h>
#include <stdlib.h>

void ler10Numeros(int vet[]){
    for(int i =0; i<10; i++){
        printf("Digite o %dº numero de 10:", i+1);
        scanf("%d", &vet[i]);
    }
}

int main() {
    int vetor[10];
    ler10Numeros(vetor);
    printf("Numeros lidsos:");
    for(int i =0; i<10; i++){
        printf("%d ", vetor[i]);
    }
    return 0;
}   