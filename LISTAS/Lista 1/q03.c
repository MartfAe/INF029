#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <locale.h>


//Cálculo do fatorial
int fatorial(int n){

int fat;
if(n<0){
    printf("Nao e possivel calcular o fatorial de um numero negativo.");
    return -1;
    }
for(fat=1; n>1; n=n-1){
            fat = fat*n ;
     }
     return(fat);
}

int main(){
    int num, resultado;

    printf("Digite um valor para calcular o seu fatorial:");
    scanf("%d", &num);
    resultado = fatorial(num);

    if(resultado!= -1){
        printf("O fatorial de %d é: %d", num, resultado);
    }else{
        printf("Nao foi possível calcular o fatorial.");
    }
}