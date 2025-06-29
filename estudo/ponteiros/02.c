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
}
else if(ptr1==ptr2){
    printf("Endereço possui o mesmo tamanho\n");
}else{
    printf("Emdndereço de ptr2 é maior");

}

return 0;
}
