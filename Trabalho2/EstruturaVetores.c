#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define TAM 10

#include "EstruturaVetores.h"




estruturaAuxiliar estruturaPrincipal[TAM];

// Inicializa a estrutura principal
void inicializar() {
    for (int i = 0; i < TAM; i++) {
        estruturaPrincipal[i].dados = NULL;
        estruturaPrincipal[i].tamanho = 0;
        estruturaPrincipal[i].qtd = 0;
    }
}

// Cria uma estrutura auxiliar
int criarEstruturaAuxiliar(int posicao, int tamanho) {
    if (posicao < 1 || posicao > TAM) {
        return POSICAO_INVALIDA;
    }

    if (tamanho < 1) {
        return TAMANHO_INVALIDO;
    }

    if (estruturaPrincipal[posicao - 1].dados != NULL) {
        return JA_TEM_ESTRUTURA_AUXILIAR;
    }

    estruturaPrincipal[posicao - 1].dados = malloc(tamanho * sizeof(int));
    if (estruturaPrincipal[posicao - 1].dados == NULL) {
        return SEM_ESPACO_DE_MEMORIA;
    }

    estruturaPrincipal[posicao - 1].tamanho = tamanho;
    estruturaPrincipal[posicao - 1].qtd = 0;

    return SUCESSO;
}

// Insere número na estrutura auxiliar
int inserirNumeroEmEstrutura(int posicao, int valor) {
    if (posicao < 1 || posicao > TAM) {
        return POSICAO_INVALIDA;
    }

    if (estruturaPrincipal[posicao - 1].dados == NULL) {
        return SEM_ESTRUTURA_AUXILIAR;
    }

    if (estruturaPrincipal[posicao - 1].qtd >= estruturaPrincipal[posicao - 1].tamanho) {
        return SEM_ESPACO;
    }

    estruturaPrincipal[posicao - 1].dados[estruturaPrincipal[posicao - 1].qtd] = valor;
    estruturaPrincipal[posicao - 1].qtd++;

    return SUCESSO;
}

// Exclui o último número de uma estrutura auxiliar
int excluirNumeroDoFinaldaEstrutura(int posicao) {
    if (posicao < 1 || posicao > TAM) {
        return POSICAO_INVALIDA;
    }

    if (estruturaPrincipal[posicao - 1].dados == NULL) {
        return SEM_ESTRUTURA_AUXILIAR;
    }

    if (estruturaPrincipal[posicao - 1].qtd == 0) {
        return ESTRUTURA_AUXILIAR_VAZIA;
    }

    estruturaPrincipal[posicao - 1].qtd--;

    return SUCESSO;
}

// Exclui um número específico de uma estrutura auxiliar
int excluirNumeroEspecificoDeEstrutura(int posicao, int valor) {
    if (posicao < 1 || posicao > TAM) {
        return POSICAO_INVALIDA;
    }

    if (estruturaPrincipal[posicao - 1].dados == NULL) {
        return SEM_ESTRUTURA_AUXILIAR;
    }

    int encontrado = -1;
    for (int i = 0; i < estruturaPrincipal[posicao - 1].qtd; i++) {
        if (estruturaPrincipal[posicao - 1].dados[i] == valor) {
            encontrado = i;
            break;
        }
    }

    if (encontrado == -1) {
        return NUMERO_INEXISTENTE;
    }

    for (int i = encontrado; i < estruturaPrincipal[posicao - 1].qtd - 1; i++) {
        estruturaPrincipal[posicao - 1].dados[i] = estruturaPrincipal[posicao - 1].dados[i + 1];
    }

    estruturaPrincipal[posicao - 1].qtd--;

    return SUCESSO;
}

/**/
int getDadosEstruturaAuxiliar(int posicao, int vetorAux[]) {
    if (posicao < 1 || posicao > TAM) {
        return POSICAO_INVALIDA;
    }

    if (estruturaPrincipal[posicao - 1].dados == NULL) {
        return SEM_ESTRUTURA_AUXILIAR;
    }

    for (int i = 0; i < estruturaPrincipal[posicao - 1].qtd; i++) {
        vetorAux[i] = estruturaPrincipal[posicao - 1].dados[i];
    }

    return SUCESSO;
}


/*
Objetivo: retorna os números ordenados da estrutura auxiliar da posição 'posicao (1..10)'.
os números devem ser armazenados em vetorAux

Rertono (int)
    SUCESSO - recuperado com sucesso os valores da estrutura na posição 'posicao (1..10)'
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
*/


int getDadosOrdenadosEstruturaAuxiliar(int posicao, int vetorAux[]) {
    if (posicao < 1 || posicao > TAM) {
        return POSICAO_INVALIDA;
    }

    if (estruturaPrincipal[posicao - 1].dados == NULL) {
        return SEM_ESTRUTURA_AUXILIAR;
    }

    // Copia os dados para vetorAux
    for (int i = 0; i < estruturaPrincipal[posicao - 1].qtd; i++) {
        vetorAux[i] = estruturaPrincipal[posicao - 1].dados[i];
    }

    // Ordena os dados no vetorAux
    int qtd = estruturaPrincipal[posicao - 1].qtd;
    for (int i = 0; i < qtd - 1; i++) {
        for (int j = i + 1; j < qtd; j++) {
            if (vetorAux[i] > vetorAux[j]) {
                int temp = vetorAux[i];
                vetorAux[i] = vetorAux[j];
                vetorAux[j] = temp;
            }
        }
    }

    return SUCESSO;
}

/*
Objetivo: retorna os números de todas as estruturas auxiliares.
os números devem ser armazenados em vetorAux

Rertono (int)
    SUCESSO - recuperado com sucesso os valores da estrutura na posição 'posicao'
    TODAS_ESTRUTURAS_AUXILIARES_VAZIAS - todas as estruturas auxiliares estão vazias
*/

int getDadosDeTodasEstruturasAuxiliares(int vetorAux[]) {
    int indice = 0;

    // Percorre todas as posições da estrutura principal
    for (int i = 0; i < TAM; i++) {
        // Verifica se existe uma estrutura auxiliar e se ela contém elementos
        if (estruturaPrincipal[i].dados != NULL && estruturaPrincipal[i].qtd > 0) {
            // Copia os elementos da estrutura auxiliar para vetorAux
            for (int j = 0; j < estruturaPrincipal[i].qtd; j++) {
                vetorAux[indice++] = estruturaPrincipal[i].dados[j];
            }
        }
    }

    // Verifica se há elementos nas estruturas auxiliares
    if (indice == 0) {
        return TODAS_ESTRUTURAS_AUXILIARES_VAZIAS;
    }

    return SUCESSO; // Dados copiados com sucesso
}

/*
Objetivo: retorna os números ordenados de todas as estruturas auxiliares.
os números devem ser armazenados em vetorAux

Rertono (int)
    SUCESSO - recuperado com sucesso os valores da estrutura na posição 'posicao'
    TODAS_ESTRUTURAS_AUXILIARES_VAZIAS - todas as estruturas auxiliares estão vazias
*/
int getDadosOrdenadosDeTodasEstruturasAuxiliares(int vetorAux[]) {
    int indice = 0;

    // Copia os dados de todas as estruturas auxiliares
    for (int i = 0; i < TAM; i++) {
        if (estruturaPrincipal[i].dados != NULL && estruturaPrincipal[i].qtd > 0) {
            for (int j = 0; j < estruturaPrincipal[i].qtd; j++) {
                vetorAux[indice++] = estruturaPrincipal[i].dados[j];
            }
        }
    }

    if (indice == 0) {
        return TODAS_ESTRUTURAS_AUXILIARES_VAZIAS;
    }

    // Ordena o vetorAux
    for (int i = 0; i < indice - 1; i++) {
        for (int j = i + 1; j < indice; j++) {
            if (vetorAux[i] > vetorAux[j]) {
                int temp = vetorAux[i];
                vetorAux[i] = vetorAux[j];
                vetorAux[j] = temp;
            }
        }
    }

    return SUCESSO;
}



/*
Objetivo: modificar o tamanho da estrutura auxiliar da posição 'posicao' para o novo tamanho 'novoTamanho' + tamanho atual
Suponha o tamanho inicial = x, e novo tamanho = n. O tamanho resultante deve ser x + n. Sendo que x + n deve ser sempre >= 1

Rertono (int)
    SUCESSO - foi modificado corretamente o tamanho da estrutura auxiliar
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
    NOVO_TAMANHO_INVALIDO - novo tamanho não pode ser negativo
    SEM_ESPACO_DE_MEMORIA - erro na alocação do novo valor
*/
int modificarTamanhoEstruturaAuxiliar(int posicao, int novoTamanho) {
    if (posicao < 1 || posicao > TAM) {
        return POSICAO_INVALIDA;
    }

    if (estruturaPrincipal[posicao - 1].dados == NULL) {
        return SEM_ESTRUTURA_AUXILIAR;
    }

    if (estruturaPrincipal[posicao - 1].tamanho + novoTamanho < 1) {
        return NOVO_TAMANHO_INVALIDO;
    }

    // Realoca a memória
    int novoTamanhoFinal = estruturaPrincipal[posicao - 1].tamanho + novoTamanho;
    int *novoDados = realloc(estruturaPrincipal[posicao - 1].dados, novoTamanhoFinal * sizeof(int));

    if (novoDados == NULL) {
        return SEM_ESPACO_DE_MEMORIA;
    }

    estruturaPrincipal[posicao - 1].dados = novoDados;
    estruturaPrincipal[posicao - 1].tamanho = novoTamanhoFinal;

    // Caso o novo tamanho seja menor, ajusta a quantidade de elementos armazenados
    if (estruturaPrincipal[posicao - 1].qtd > novoTamanhoFinal) {
        estruturaPrincipal[posicao - 1].qtd = novoTamanhoFinal;
    }

    return SUCESSO;
}



/*
Objetivo: retorna a quantidade de elementos preenchidos da estrutura auxiliar da posição 'posicao'.

Retorno (int)
    POSICAO_INVALIDA - posição inválida
    SEM_ESTRUTURA_AUXILIAR - sem estrutura auxiliar
    ESTRUTURA_AUXILIAR_VAZIA - estrutura auxiliar vazia
    Um número int > 0 correpondente a quantidade de elementos preenchidos da estrutura
*/
int getQuantidadeElementosEstruturaAuxiliar(int posicao) {
    if (posicao < 1 || posicao > TAM) {
        return POSICAO_INVALIDA;
    }

    if (estruturaPrincipal[posicao - 1].dados == NULL) {
        return SEM_ESTRUTURA_AUXILIAR;
    }

    return estruturaPrincipal[posicao - 1].qtd;
}

/*
Objetivo: montar a lista encadeada com cabeçote com todos os números presentes em todas as estruturas.

Retorno (No*)
    NULL, caso não tenha nenhum número nas listas
    No*, ponteiro para o início da lista com cabeçote
*/
void inserir_no_fim(No **cabecote, int valor) {
    No *novo = (No *)malloc(sizeof(No)); // Aloca memória para o novo nó
    if (novo == NULL) {
        printf("Erro ao alocar memória.\n");
        return;
    }

    novo->conteudo = valor;
    novo->prox = NULL;

    // Se a lista estiver vazia
    if (*cabecote == NULL) {
        *cabecote = novo;
        return;
    }

    // Caso contrário, insere no final
    No *aux = *cabecote;
    while (aux->prox != NULL) {
        aux = aux->prox;
    }
    aux->prox = novo;
}

No *montarListaEncadeadaComCabecote() {
    No *cabecote = NULL;

    // Verifica todas as posições da estrutura principal
    for (int i = 0; i < TAM; i++) {
        // Verifica se a estrutura auxiliar existe e não está vazia
        if (estruturaPrincipal[i].dados != NULL && estruturaPrincipal[i].qtd > 0) {
            for (int j = 0; j < estruturaPrincipal[i].qtd; j++) {
                inserir_no_fim(&cabecote, estruturaPrincipal[i].dados[j]);
            }
        }
    }

    // Se não houver elementos em nenhuma estrutura auxiliar, retorna NULL
    if (cabecote == NULL) {
        return NULL;
    }

    return cabecote; // Retorna a lista encadeada
}

void getDadosListaEncadeadaComCabecote(No *inicio, int vetorAux[]) {
    if (inicio == NULL) {
        printf("A lista encadeada está vazia.\n");
        return;
    }

    int i = 0;
    No *aux = inicio;

    // Percorre a lista encadeada e armazena os valores no vetor
    while (aux != NULL) {
        vetorAux[i] = aux->conteudo;
        aux = aux->prox;
        i++;
    }
}

/*
Objetivo: Destruir a lista encadeada com cabeçote a partir de início.
O ponteiro inicio deve ficar com NULL.

Retorno 
    void.
*/
void destruirListaEncadeadaComCabecote(No **inicio) {
    if (*inicio == NULL) {
        return;
    }

    No *aux = *inicio;
    while (aux != NULL) {
        No *temp = aux;
        aux = aux->prox;
        free(temp);
    }
    *inicio = NULL;
}


/*
Objetivo: finaliza o programa. deve ser chamado ao final do programa 
para poder liberar todos os espaços de memória das estruturas auxiliares.

*/

void finalizar() {
    for (int i = 0; i < TAM; i++) {
        if (estruturaPrincipal[i].dados != NULL) {
            free(estruturaPrincipal[i].dados);
            estruturaPrincipal[i].dados = NULL;
        }
    }
}