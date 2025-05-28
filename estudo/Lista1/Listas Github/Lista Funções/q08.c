#include <stdio.h>
#include <stdlib.h>

typedef struct{
    char nome[80];
    char dataNascimento[20];
    char sexo;
    char cpf[20];
}Cliente;

Cliente cadastrarCliente(){
    Cliente dadosCliente;
    printf("Digite o nome do cliente:");
    scanf("%79s", &dadosCliente.nome);

    printf("Digite sua data de nascimento: (DD/MM/AAAA)\n");
    scanf("%19s", &dadosCliente.dataNascimento);
    
    printf("Digite o seu sexo:");
    scanf("%c", &dadosCliente.sexo);

    printf("Digite seu cpf:");
    scanf("%19s", &dadosCliente.cpf);
}
int main() {
    
    return 0;
}
