#include <stdio.h>
#include <stdlib.h>

void somaVetor(int vet1[], int vet2[], int resultado[]){
    for(int i = 0 ; i <5; i++){
        resultado[i]=vet1[i]+vet2[i];
    }
}

void lerVetor(int vet1[], int vet2[]){
    for(int i =0; i <5; i ++){
        printf("Digite um valor para o vetor 1:");
        scanf("%d", &vet1[i]);
        printf("Digite um valor para o vetor 2:");
        scanf("%d", &vet2[i]);
    }

}

int main() {
    int vet1[5];
    int vet2[5];
    int vetSoma[5];
    lerVetor(vet1, vet2);
    somaVetor(vet1, vet2, vetSoma);
    printf("Resultado:");
    for(int i =0; i <5; i++){
        printf("%d ", vetSoma[i]);
    }
    
    return 0;
}