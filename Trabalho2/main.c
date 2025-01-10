#include <stdio.h>
#include <stdlib.h>

#include "EstruturaVetores.h"

// Função para exibir o menu de opções
int menu() {
    int op;
    printf("\nDigite a opção desejada:\n");
    printf("0 - Sair\n");
    printf("1 - Criar estrutura auxiliar\n");
    printf("2 - Inserir número\n");
    printf("3 - Excluir último número\n");
    printf("4 - Excluir número específico\n");
    printf("5 - Listar números de uma estrutura\n");
    printf("6 - Listar números ordenados de uma estrutura\n");
    printf("7 - Listar todos os números\n");
    printf("8 - Listar todos os números ordenados\n");
    printf("9 - Modificar tamanho de uma estrutura\n");
    printf("10 - Dobrar número (teste de ponteiro)\n");
    printf("Escolha: ");
    scanf("%d", &op);
    return op;
}

// Função auxiliar para dobrar um número
void dobrar(int *x) {
    *x *= 2;
}

int main() {
    inicializar(); // Inicializa as estruturas auxiliares
    int op;
    int sair = 0;

    while (!sair) {
        op = menu();
        switch (op) {
            case 0: { // Sair
                sair = 1;
                finalizar();
                printf("Programa finalizado!\n");
                break;
            }

            case 1: { // Criar estrutura auxiliar
                int posicao, tamanho, retorno;
                printf("Digite a posição (1 a 10): ");
                scanf("%d", &posicao);
                printf("Digite o tamanho da estrutura: ");
                scanf("%d", &tamanho);
                retorno = criarEstruturaAuxiliar(posicao, tamanho);

                if (retorno == SUCESSO) {
                    printf("Estrutura auxiliar criada com sucesso!\n");
                } else if (retorno == POSICAO_INVALIDA) {
                    printf("Posição inválida!\n");
                } else if (retorno == TAMANHO_INVALIDO) {
                    printf("Tamanho inválido!\n");
                } else if (retorno == JA_TEM_ESTRUTURA_AUXILIAR) {
                    printf("Já existe uma estrutura auxiliar nessa posição!\n");
                } else if (retorno == SEM_ESPACO_DE_MEMORIA) {
                    printf("Erro de alocação de memória!\n");
                }
                break;
            }

            case 2: { // Inserir número
                int posicao, valor, retorno;
                printf("Digite a posição (1 a 10): ");
                scanf("%d", &posicao);
                printf("Digite o número a ser inserido: ");
                scanf("%d", &valor);
                retorno = inserirNumeroEmEstrutura(posicao, valor);

                if (retorno == SUCESSO) {
                    printf("Número inserido com sucesso!\n");
                } else if (retorno == SEM_ESPACO) {
                    printf("Sem espaço na estrutura auxiliar!\n");
                } else if (retorno == SEM_ESTRUTURA_AUXILIAR) {
                    printf("Não há estrutura auxiliar na posição informada!\n");
                } else if (retorno == POSICAO_INVALIDA) {
                    printf("Posição inválida!\n");
                }
                break;
            }

            case 3: { // Excluir último número
                int posicao, retorno;
                printf("Digite a posição (1 a 10): ");
                scanf("%d", &posicao);
                retorno = excluirNumeroDoFinaldaEstrutura(posicao);

                if (retorno == SUCESSO) {
                    printf("Último número excluído com sucesso!\n");
                } else if (retorno == ESTRUTURA_AUXILIAR_VAZIA) {
                    printf("A estrutura está vazia!\n");
                } else if (retorno == SEM_ESTRUTURA_AUXILIAR) {
                    printf("Não há estrutura auxiliar na posição informada!\n");
                } else if (retorno == POSICAO_INVALIDA) {
                    printf("Posição inválida!\n");
                }
                break;
            }

            case 4: { // Excluir número específico
                int posicao, valor, retorno;
                printf("Digite a posição (1 a 10): ");
                scanf("%d", &posicao);
                printf("Digite o número a ser excluído: ");
                scanf("%d", &valor);
                retorno = excluirNumeroEspecificoDeEstrutura(posicao, valor);

                if (retorno == SUCESSO) {
                    printf("Número excluído com sucesso!\n");
                } else if (retorno == NUMERO_INEXISTENTE) {
                    printf("Número inexistente na estrutura auxiliar!\n");
                } else if (retorno == SEM_ESTRUTURA_AUXILIAR) {
                    printf("Não há estrutura auxiliar na posição informada!\n");
                } else if (retorno == POSICAO_INVALIDA) {
                    printf("Posição inválida!\n");
                }
                break;
            }

            case 5: { // Listar números de uma estrutura
                int posicao, retorno;
                printf("Digite a posição (1 a 10): ");
                scanf("%d", &posicao);

                int qtd = getQuantidadeElementosEstruturaAuxiliar(posicao);
                if (qtd > 0) {
                    int vetorAux[qtd];
                    retorno = getDadosEstruturaAuxiliar(posicao, vetorAux);

                    if (retorno == SUCESSO) {
                        printf("Números na estrutura: ");
                        for (int i = 0; i < qtd; i++) {
                            printf("%d ", vetorAux[i]);
                        }
                        printf("\n");
                    }
                } else {
                    printf("Estrutura vazia ou inexistente!\n");
                }
                break;
            }

            case 10: { // Dobrar número
                int valor;
                printf("Digite um número: ");
                scanf("%d", &valor);
                dobrar(&valor);
                printf("Número dobrado: %d\n", valor);
                break;
            }

            default: {
                printf("Opção inválida!\n");
            }
        }
    }

    return 0;
}
