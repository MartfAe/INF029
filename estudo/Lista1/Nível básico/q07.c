#include <stdio.h>
#include <stdlib.h>

int main() {
    int n;
    printf("Digite um numero para ver sua tabuada: ");
    scanf("%d", &n);
    
    printf("---Tabuada---\n");
    for(int i = 0; i <=10; i++){//Tabuada começa no zero e termina no 10.
        printf("%d x %d = %d", n, i, n*i);
        printf("\n");
    }
    return 0;
}