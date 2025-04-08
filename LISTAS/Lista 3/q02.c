#include <stdio.h>
#include <stdlib.h>

int fibonnaci(int x);

int main(){
    int nEsimoNum, resultado;

    printf("Digite a posição do número de Fibonacci que deseja saber: ");
    scanf("%d", &nEsimoNum);

    resultado = fibonnaci(nEsimoNum);
    printf("O %dº número de Fibonacci é %d\n", nEsimoNum, resultado);

}

int fibonnaci(int x){
    if(x ==0){
        return 0;
    }
    if(x == 1){
        return 1;
    }
    else{
        return fibonnaci(x-1) + fibonnaci(x-2);
    }
}