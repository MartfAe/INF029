#include <stdio.h>
#include <stdlib.h>


void ler3Numeros(int vet[]){
    for(int i =0; i <3; i++){
        printf("Digite o %d numero do vetor:", i +1);
        scanf("%d", &vet[i]);
    }

}
int main() {
    int vetor[3];
    ler3Numeros(vetor);

    printf("Números lidos:");
    for(int i =0; i <3; i++){
        printf("%d ", vetor[i]);
    }
    return 0;
}