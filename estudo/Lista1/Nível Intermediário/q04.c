#include <stdio.h>
#include <stdlib.h>

void lerVetor(int vet[]){
    for(int i =0; i <15; i++){
        printf("Digite o %d numero de 15:", i+1);
        scanf("%d", &vet[i]);
    }
}

int totalPar(int vet[]){
    int pares = 0;
    for(int i =0; i <15; i++){
        if(vet[i]%2 ==0){
            pares++;
        }
    }
    return pares;
}
int main() {
    int vetor[15];
    lerVetor(vetor);
    int qtdPares = totalPar(vetor);
    printf("Total de pares:%d", qtdPares);
    return 0;
}