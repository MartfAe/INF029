#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void inverter(char data[]){
   int tamanho = strlen(data);
   for(int i = tamanho-1; i >=0;i--){
    printf("%c", data[i]);
   }
}
int main() {
    char data[11];
    printf("Digite uma data:");
    scanf("%10s", data);
    printf("Original: %s\n", data);
    printf("Invertida:");
    inverter(data);
    return 0;
}