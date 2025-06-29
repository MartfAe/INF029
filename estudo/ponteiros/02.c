#include <stdio.h>
#include <stdlib.h>

int main(){
    int v1= 504;
    int v2= 100;
    int *ptr1;
    int *ptr2;
    ptr1= &v1;
    ptr2= &v2;

    if(ptr1>ptr2){
        printf("Endereço do ponteiro 1 é maior\n");
        printf("Conteúdo do maior endereço: %d\n", *ptr1);
    }
    else if(ptr1==ptr2){
        printf("Endereços possuem o mesmo valor\n");
        printf("Conteúdo: %d\n", *ptr1);
    }else{
        printf("Endereço do ponteiro 2 é maior.\n");
        printf("Conteúdo do maior endereço: %d\n", *ptr2);
    }
    return 0;
}
