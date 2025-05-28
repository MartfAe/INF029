#include <stdio.h>
#include <stdlib.h>

int subtrai(int v1, int v2, int v3){
    int sub = v1 - v2 - v3; 
    return sub;
}

int main() {
    int v1, v2,v3;
    printf("Digite 3 valores:\n");
    scanf("%d", &v1);
    scanf("%d", &v2);
    scanf("%d", &v3);
    int resultado = subtrai(v1,v2,v3);
    printf("Resultado = %d", resultado);
    return 0;
}