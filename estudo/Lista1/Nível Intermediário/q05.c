#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define tamanho 10
void lerVetor(int vet[]){

    for(int i =0; i <tamanho; i++){
        printf("Digite o %d numero de 10:", i+1);
        scanf("%d", &vet[i]);
    }
}
void inverterVetor(int vet[]){ 
    for(int i = tamanho-1; i >=0; i--){
        printf("%d ", vet[i]);
    }
}
int main() {
    int vet[10];
    lerVetor(vet);
    inverterVetor(vet);

    return 0;
}