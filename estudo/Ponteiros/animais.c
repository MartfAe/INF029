#include <stdio.h>
#include<stdlib.h>
#include <ctype.h>
#include <string.h>


#define MAX_ANIMAIS 10
#define TAM_NOME 30

typedef struct{
    int dia, mes, ano;
}data;

typedef struct{
    char sexo;
    int idade;
    char nome[TAM_NOME];
    data dataNascimento;
}animal;

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}


void cadastrarAnimal(animal animais[], int *quantidade){
    if(*quantidade >= MAX_ANIMAIS){
        printf("Quantidade máxima atingida.\n");
        return;
    }

    printf("Cadastro do animal %dº:\n", *quantidade + 1);

    // Sempre limpar o buffer APÓS qualquer scanf
    printf("Nome: ");
    fgets(animais[*quantidade].nome, TAM_NOME, stdin);
    size_t len = strlen(animais[*quantidade].nome);
    if (len > 0 && animais[*quantidade].nome[len - 1] == '\n') {
        animais[*quantidade].nome[len - 1] = '\0';
    }

    printf("Data de nascimento (formato: DD MM AAAA): ");
    scanf("%d %d %d", &animais[*quantidade].dataNascimento.dia, &animais[*quantidade].dataNascimento.mes, &animais[*quantidade].dataNascimento.ano);
    limparBuffer();

    printf("Idade: ");
    scanf("%d", &animais[*quantidade].idade);
    limparBuffer();

    printf("Sexo (M/F): ");
    scanf(" %c", &animais[*quantidade].sexo);
    limparBuffer();

    animais[*quantidade].sexo = toupper(animais[*quantidade].sexo);

    while ((animais[*quantidade].sexo != 'F') && (animais[*quantidade].sexo != 'M')) {
        printf("Entrada inválida! Digite 'M' para macho ou 'F' para fêmea: ");
        scanf(" %c", &animais[*quantidade].sexo);
        limparBuffer();
        animais[*quantidade].sexo = toupper(animais[*quantidade].sexo);
    }

    (*quantidade)++;
    printf("Animal cadastrado com sucesso!\n");
}

void listarTodosAnimais(animal animais[], int quantidade){
    if(quantidade == 0){
        printf("Não existem animais cadastrados.\n");
        return;
    }

    printf("\nLista de animais cadastrados:\n");
    for(int i = 0; i < quantidade; i++){
        printf("Animal %d:\n", i + 1);
        printf("- Nome: %s\n", animais[i].nome);
        printf("- Data de nascimento: %02d/%02d/%04d\n",
               animais[i].dataNascimento.dia,
               animais[i].dataNascimento.mes,
               animais[i].dataNascimento.ano);
        printf("- Idade: %d\n", animais[i].idade);
        printf("- Sexo: %c\n\n", animais[i].sexo);
    }
}

void listarAcimaDaMedia(animal animais[], int quantidade){
    if(quantidade ==0){
        printf("Não existe animais cadastrados.");
        return;
    }

    int soma = 0 ;
    for(int i =0; i <quantidade; i++){
        soma +=animais[i].idade;
    }
    float media =soma / (float)quantidade;
    printf("\nIdade média: %.2f\n", media);
    printf("Animais com idade maior ou igual à média:\n");

    for (int i =0; i <quantidade; i++){
        if(animais[i].idade>=media){
            printf("- Nome: %s\n", animais[i].nome);
            printf("  Idade: %d\n", animais[i].idade);
            printf("  Sexo: %c\n", animais[i].sexo);
            printf("  Nascimento: %02d/%02d/%04d\n\n",
                   animais[i].dataNascimento.dia,
                   animais[i].dataNascimento.mes,
                   animais[i].dataNascimento.ano);
        }
    }
}

void atualizarAnimal(animal animais[], int quantidade){
    if(quantidade == 0){
        printf("Não existe animais cadastrados!\n");
        return;
    }

    int indice;
    printf("Digite o número do animal que deseja atualizar (de 1 a %d):", quantidade);
    scanf("%d", &indice);
    if (indice<1 || indice>quantidade){
        printf("Indice inválido!\n");
        return;
    }
    indice --;
    animal *a= &animais[indice];
    printf("Atualizando dados do animal: %s\n", a->nome);

    printf("Novo nome (Enter para manter): ");
    while(getchar() != '\n'){};
        char novoNome[TAM_NOME];
        fgets(novoNome, TAM_NOME, stdin);
        if(novoNome[0] != '\n'){
            novoNome[strcspn(novoNome, "\n")] = '\0';
            strcpy(a->nome, novoNome);
        }
    
    char linha[100];
    printf("Nova data de nascimento (DD MM AAAA ou Enter para manter): ");
    fgets(linha, sizeof(linha), stdin);
    if (linha[0] != '\n') {
        int dia, mes, ano;
        if (sscanf(linha, "%d %d %d", &dia, &mes, &ano) == 3) {
            a->dataNascimento.dia = dia;
            a->dataNascimento.mes = mes;
            a->dataNascimento.ano = ano;
        }
    }


    printf("Nova idade (ou Enter para manter): ");
    fgets(linha, sizeof(linha), stdin);
    if (linha[0] != '\n') {
        int idade;
        if (sscanf(linha, "%d", &idade) == 1) {
            a->idade = idade;
        }
    }

    printf("Novo sexo (M/F ou Enter para manter): ");
    fgets(linha, sizeof(linha), stdin);
    if (linha[0] != '\n') {
        char sexo;
        if (sscanf(linha, " %c", &sexo) == 1) {
            sexo = toupper(sexo);
            while (sexo != 'M' && sexo != 'F') {
                printf("Entrada inválida! Digite 'M' para macho ou 'F' para fêmea: ");
                fgets(linha, sizeof(linha), stdin);
                if (linha[0] == '\n') break;
                if (sscanf(linha, " %c", &sexo) == 1) {
                    sexo = toupper(sexo);
                }
            }
            if (sexo == 'M' || sexo == 'F') {
                a->sexo = sexo;
            }
        }
    }

    printf("Dados atualizados com sucesso!\n");
}

void excluirAnimal(animal animais[], int *quantidade) {
    if (*quantidade == 0) {
        printf("Nenhum animal cadastrado.\n");
        return;
    }

    int indice;
    printf("\nDigite o número do animal que deseja excluir (1 a %d): ", *quantidade);
    scanf("%d", &indice);

    if (indice < 1 || indice > *quantidade) {
        printf("Índice inválido!\n");
        return;
    }

    indice--;
    printf("Excluindo o animal: %s\n", animais[indice].nome);

    for (int i = indice; i < *quantidade - 1; i++) {
        animais[i] = animais[i + 1];
    }

    (*quantidade)--;
    printf("Animal excluído com sucesso!\n");
}

void exibirMenu() {
    printf("\nMenu:\n");
    printf("1 - Cadastrar animal\n");
    printf("2 - Listar todos os animais\n");
    printf("3 - Listar animais com idade >= média\n");
    printf("4 - Excluir animal\n");
    printf("5 - Atualizar animal\n");
    printf("6 - Limpar tela\n");
    printf("7 - Sair\n");
    printf("Escolha uma opção: ");
}

void limparTela() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}




int main() {
    animal animais[MAX_ANIMAIS];
    int quantidade = 0;
    int opcao;

    do {
        exibirMenu();
        scanf("%d", &opcao);
        limparBuffer();

        switch (opcao) {
            case 1:
                cadastrarAnimal(animais, &quantidade);
                break;
            case 2:
                listarTodosAnimais(animais, quantidade);
                break;
            case 3:
                listarAcimaDaMedia(animais, quantidade);
                break;
            case 4:
                excluirAnimal(animais, &quantidade);
                break;
            case 5:
                atualizarAnimal(animais, quantidade);
                break;
            case 6:
                limparTela();
                break;
            case 7:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while (opcao != 7);
}