#include <stdio.h> 
#include <stdlib.h>


int fatorial(int x);

int main(void){
    int numero, resultado;
    
    printf("Digite um numero inteiro: ");
    scanf("%d", &numero);
    resultado = fatorial(numero);
    printf("O fatorial de %d e %d\n", numero, fatorial(numero));

    return 0;
}

int (fatorial(int x)){
    int vfat;
      if (x <=1){
        return 1;
      }else{
        vfat = x * fatorial(x-1);
        return vfat;
      }
    }

    
