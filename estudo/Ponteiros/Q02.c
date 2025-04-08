#include <stdio.h>
#include <stdlib.h>



int main(){
    int vet[5];
    printf("O vetor tem 5 elementos, vamos preenche-lo.\n");
    for(int i=0; i <5; i++){
        printf("Digite o valor %d do vetor:", i+1);
        scanf("%d", &vet[i]);
    }
    printf("Vetor: ");
    for(int i =0; i <5; i++){
        printf("%d ", vet[i]);
    }

}