#include <stdio.h>
#include <stdlib.h>

void comerBolo(int fatias){
    char resposta;
    if(fatias ==0){
        printf("O bolo acabou!\n");
        return;
    }
    
int idade;
    printf("Quantas fatias de bolo você quer comer?\n");
    scanf("%d", &fatias);
    comerBolo(fatias);
    printf("Deseja comer mais bolo? (s/n)\n");
    scanf(" %c", &resposta);
    if(resposta == 's'){
        comerBolo(fatias);
    }
    else{
        printf("Você comeu %d fatias de bolo.\n", fatias);
    }
}
int main(){}