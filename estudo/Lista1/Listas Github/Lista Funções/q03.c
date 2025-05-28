#include <stdio.h>
#include <stdlib.h>


int fatorial(int n){
    int fat=1;
    if(n<=0){
       return -1;
    }else{
        for(int i =1; i <=n; i++){
            fat *= i ;
        }
    }
    return fat;
}
int main() {
    int n, fat;
    printf("Digite um numero para calcular o fatorial: ");
    scanf("%d", &n);
    fat = fatorial(n);
    printf("Resultado do fatorial:%d", fat);
    return 0;
}