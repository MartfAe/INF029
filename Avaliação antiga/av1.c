#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define Max 10

void limpaBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int insereCaractere(char vetor[], int *topo) {
    if (*topo < Max) {
        printf("Digite um caractere: ");
        scanf(" %c", &vetor[*topo]);
        (*topo)++;
        printf("Caractere inserido com sucesso\n");
        return 1;
    } else {
        printf("Vetor cheio. Caractere não inserido\n");
        return 0;
    }
}

int trocaCaractere(char vetor[], int topo, char *substituido) {
    char novo;
    printf("Informe o novo caractere: ");
    scanf(" %c", &novo);

    for (int i = 0; i < topo; i++) {
        if (vetor[i] == *substituido) {
            printf("Caractere '%c' será substituído por '%c'\n", vetor[i], novo);
            vetor[i] = novo;
            return 1;
        }
    }

    printf("Caractere substituto não encontrado no vetor.\n");
    return 0;
}

int removerCaractere(char vetor[], int *topo) {
    if (*topo > 0) {
        (*topo)--;
        vetor[*topo] = '\0';
        printf("Caractere removido com sucesso.\n");
        return 1;
    } else {
        printf("Não há caracteres para remover.\n");
        return 0;
    }
}

int listaTodosCaracteres(char vetor[], int *topo) {
    printf("Vetor: ");
    for (int i = 0; i < *topo; i++) {
        printf("%c ", vetor[i]);
    }
    printf("\n");
    return 0;
}

int imprimeCaracteresDistintos(char vetor[], int *topo) {
    if (*topo == 0) {
        printf("Não há caracteres para imprimir.\n");
        return 0;
    }
    int frequencia[256] = {0};
    for (int i = 0; i < *topo; i++) {
        frequencia[(unsigned char)vetor[i]]++;
    }
    printf("Caracteres distintos e frequências:\n");
    for (int i = 0; i < 256; i++) {
        if (frequencia[i] > 0) {
            printf("%c: %d\n", i, frequencia[i]);
        }
    }
    return 0;
}

int main() {
    char vetor[Max];
    int topo = 0;
    int opcao;
    char substituto = '\0';

    while (1) {
        printf("\nMenu:\n");
        printf("'1' - Inserir caractere\n");
        printf("'2' - Trocar caractere\n");
        printf("'3' - Remover caractere\n");
        printf("'4' - Listar todos os caracteres\n");
        printf("'5' - Imprimir caracteres distintos\n");
        printf("'6' - Sair\n");
        printf("Digite a opção desejada: ");
        scanf("%d", &opcao);
        limpaBuffer();

        switch (opcao) {
            case 1:
                insereCaractere(vetor, &topo);
                break;
            case 2:
                printf("Informe o caractere a substituir: ");
                scanf(" %c", &substituto);
                trocaCaractere(vetor, topo, &substituto);
                break;
            case 3:
                removerCaractere(vetor, &topo);
                break;
            case 4:
                listaTodosCaracteres(vetor, &topo);
                break;
            case 5:
                imprimeCaracteresDistintos(vetor, &topo);
                break;
            case 6:
                printf("Saindo...\n");
                exit(0);
            default:
                printf("Opção inválida.\n");
                break;
        }
    }
    return 0;
}
