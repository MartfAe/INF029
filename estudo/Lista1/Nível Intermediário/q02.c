#include <stdio.h>
#include <stdlib.h>

void ler5Numeros(int vet[]){
    for(int i = 0 ; i <5; i++){
        printf("Digite o %d valor:", i+1);
        scanf("%d", &vet[i]);
    }
}

void numeroMaior_Menor(int vet[]){
    int menor, maior;
    menor = vet[0];
    for(int i= 0; i <5; i++){
        if(vet[i]<menor){
            menor = vet[i];
        }
    }
    maior = vet[0];
    for(int i =0; i <5; i++){
        if(vet[i]>maior){
            maior = vet[i];
        }
    }
    printf("\nMaior numero:%d\nMenor num:%d", maior, menor);
}

int main() {

    int vetor[5];
    ler5Numeros(vetor);
    numeroMaior_Menor(vetor);
    
    return 0;
}