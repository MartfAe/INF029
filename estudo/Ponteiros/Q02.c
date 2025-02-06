#include <stdio.h>
#include <stdlib.h>

int main(){
    int vetor [5]= {1, 2, 3, 4, 5};
    int *vetorPtr = vetor;
    printf("Vetor antes da mudança:\n");
    for(int i = 0; i <5; i++){
        printf("%d ", vetor[i]);
    }
    printf("\n");
    printf("Vetor depois da mudança:\n");
    for(int i = 0; i <5; i++){
        *(vetorPtr + i) = *(vetorPtr + i) * 2;
        printf("%d ", vetor[i]);
    }

}