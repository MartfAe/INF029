#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define TAM 10

#include "EstruturaVetores.h"


/*
Objetivo: criar estrutura auxiliar na posição 'posicao'.
com tamanho 'tamanho'

Rertono (int)
    SUCESSO - criado com sucesso
    JA_TEM_ESTRUTURA_AUXILIAR - já tem estrutura na posição
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
    SEM_ESPACO_DE_MEMORIA - Sem espaço de memória
    TAMANHO_INVALIDO - o tamanho deve ser maior ou igual a 1
*/

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
    printf("Debug: Criando estrutura auxiliar na posição %d com tamanho %d\n", posicao, tamanho);

    if (posicao < 1 || posicao > TAM) {
        printf("Erro: Posição inválida\n");
        return POSICAO_INVALIDA;
    }

    if (tamanho < 1) {
        printf("Erro: Tamanho inválido\n");
        return TAMANHO_INVALIDO;
    }

    if (estruturaPrincipal[posicao - 1].dados != NULL) {
        printf("Erro: Estrutura auxiliar já existe na posição %d\n", posicao);
        return JA_TEM_ESTRUTURA_AUXILIAR;
    }

    estruturaPrincipal[posicao - 1].dados = malloc(tamanho * sizeof(int));
    if (estruturaPrincipal[posicao - 1].dados == NULL) {
        printf("Erro: Sem espaço de memória\n");
        return SEM_ESPACO_DE_MEMORIA;
    }

    estruturaPrincipal[posicao - 1].tamanho = tamanho;
    estruturaPrincipal[posicao - 1].qtd = 0;

    printf("Sucesso: Estrutura auxiliar criada na posição %d\n", posicao);
    return SUCESSO;
}

/*
Objetivo: inserir número 'valor' em estrutura auxiliar da posição 'posicao'
Rertono (int)
    SUCESSO - inserido com sucesso
    SEM_ESPACO - não tem espaço
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
CONSTANTES
*/

// Insere número na estrutura auxiliar
int inserirNumeroEmEstrutura(int posicao, int valor) {
    printf("Debug: Inserindo número %d na posição %d\n", valor, posicao);

    if (posicao < 1 || posicao > TAM) {
        printf("Erro: Posição inválida\n");
        return POSICAO_INVALIDA;
    }

    if (estruturaPrincipal[posicao - 1].dados == NULL) {
        printf("Erro: Estrutura auxiliar inexistente na posição %d\n", posicao);
        return SEM_ESTRUTURA_AUXILIAR;
    }

    if (estruturaPrincipal[posicao - 1].qtd >= estruturaPrincipal[posicao - 1].tamanho) {
        printf("Erro: Sem espaço na estrutura auxiliar da posição %d\n", posicao);
        return SEM_ESPACO;
    }

    estruturaPrincipal[posicao - 1].dados[estruturaPrincipal[posicao - 1].qtd] = valor;
    estruturaPrincipal[posicao - 1].qtd++;

    printf("Sucesso: Número %d inserido na posição %d\n", valor, posicao);
    return SUCESSO;
}

/*
Objetivo: excluir o numero 'valor' da estrutura auxiliar no final da estrutura.
ex: suponha os valores [3, 8, 7, 9,  ,  ]. Após excluir, a estrutura deve ficar da seguinte forma [3, 8, 7,  ,  ,  ].
Obs. Esta é uma exclusão lógica

Rertono (int)
    SUCESSO - excluido com sucesso
    ESTRUTURA_AUXILIAR_VAZIA - estrutura vazia
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
*/

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

/*
Objetivo: excluir o numero 'valor' da estrutura auxiliar da posição 'posicao'.
Caso seja excluido, os números posteriores devem ser movidos para as posições anteriores
ex: suponha os valores [3, 8, 7, 9,  ,  ] onde deve ser excluido o valor 8. A estrutura deve ficar da seguinte forma [3, 7, 9,  ,  ,  ]
Obs. Esta é uma exclusão lógica
Rertono (int)
    SUCESSO - excluido com sucesso 'valor' da estrutura na posição 'posicao'
    ESTRUTURA_AUXILIAR_VAZIA - estrutura vazia
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    NUMERO_INEXISTENTE - Número não existe
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar

*/

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

/*
Objetivo: retorna os números da estrutura auxiliar da posição 'posicao (1..10)'.
os números devem ser armazenados em vetorAux

Retorno (int)
    SUCESSO - recuperado com sucesso os valores da estrutura na posição 'posicao'
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
*/

int getDadosEstruturaAuxiliar(int posicao, int vetorAux[]) {
    printf("Debug: Obtendo dados da estrutura auxiliar na posição %d\n", posicao);

    if (posicao < 1 || posicao > TAM) {
        printf("Erro: Posição inválida\n");
        return POSICAO_INVALIDA;
    }

    if (estruturaPrincipal[posicao - 1].dados == NULL) {
        printf("Erro: Estrutura auxiliar inexistente na posição %d\n", posicao);
        return SEM_ESTRUTURA_AUXILIAR;
    }

    for (int i = 0; i < estruturaPrincipal[posicao - 1].qtd; i++) {
        vetorAux[i] = estruturaPrincipal[posicao - 1].dados[i];
    }

    printf("Sucesso: Dados obtidos da posição %d\n", posicao);
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
    int retorno = getDadosEstruturaAuxiliar(posicao, vetorAux);
    if (retorno != SUCESSO) {
        return retorno;
    }

    int qtd = estruturaPrincipal[posicao - 1].qtd;

    // Ordena os dados no vetor auxiliar
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
    printf("Debug: Entrou na função getDadosDeTodasEstruturasAuxiliares\n");

    int indice = 0;
    for (int i = 0; i < TAM; i++) {
        if (estruturaPrincipal[i].dados != NULL && estruturaPrincipal[i].qtd > 0) {
            printf("Debug: Copiando dados da posição %d\n", i + 1);
            for (int j = 0; j < estruturaPrincipal[i].qtd; j++) {
                vetorAux[indice++] = estruturaPrincipal[i].dados[j];
            }
        }
    }

    if (indice == 0) {
        printf("Debug: Todas as estruturas auxiliares estão vazias\n");
        return TODAS_ESTRUTURAS_AUXILIARES_VAZIAS;
    }

    printf("Debug: Dados copiados com sucesso, total de %d números\n", indice);
    return SUCESSO;
}


/*
Objetivo: retorna os números ordenados de todas as estruturas auxiliares.
os números devem ser armazenados em vetorAux

Rertono (int)
    SUCESSO - recuperado com sucesso os valores da estrutura na posição 'posicao'
    TODAS_ESTRUTURAS_AUXILIARES_VAZIAS - todas as estruturas auxiliares estão vazias
*/
int getDadosOrdenadosDeTodasEstruturasAuxiliares(int vetorAux[]) {
    int retorno = getDadosDeTodasEstruturasAuxiliares(vetorAux);
    if (retorno != SUCESSO) {
        return retorno;
    }

    int qtd = 0;
    for (int i = 0; i < TAM; i++) {
        if (estruturaPrincipal[i].dados != NULL) {
            qtd += estruturaPrincipal[i].qtd;
        }
    }

    // Ordena os dados
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
    printf("Debug: Modificando tamanho da estrutura auxiliar na posição %d para %d\n", posicao, novoTamanho);

    if (posicao < 1 || posicao > TAM) {
        printf("Erro: Posição inválida\n");
        return POSICAO_INVALIDA;
    }

    if (estruturaPrincipal[posicao - 1].dados == NULL) {
        printf("Erro: Estrutura auxiliar inexistente na posição %d\n", posicao);
        return SEM_ESTRUTURA_AUXILIAR;
    }

    if (estruturaPrincipal[posicao - 1].tamanho + novoTamanho < 1) {
        printf("Erro: Novo tamanho inválido\n");
        return NOVO_TAMANHO_INVALIDO;
    }

    int *novoDados = realloc(estruturaPrincipal[posicao - 1].dados, (estruturaPrincipal[posicao - 1].tamanho + novoTamanho) * sizeof(int));
    if (novoDados == NULL) {
        printf("Erro: Sem espaço de memória para realocar\n");
        return SEM_ESPACO_DE_MEMORIA;
    }

    estruturaPrincipal[posicao - 1].dados = novoDados;
    estruturaPrincipal[posicao - 1].tamanho += novoTamanho;

    if (estruturaPrincipal[posicao - 1].qtd > estruturaPrincipal[posicao - 1].tamanho) {
        estruturaPrincipal[posicao - 1].qtd = estruturaPrincipal[posicao - 1].tamanho;
    }

    printf("Sucesso: Tamanho modificado na posição %d\n", posicao);
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
 