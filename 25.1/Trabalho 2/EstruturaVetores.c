#include <stdio.h>
#include <stdlib.h>
#define TAM 10

#include "EstruturaVetores.h"


typedef struct{
    int *dados; //Ponteiro para o vetor que armazena
    int tamanho; //Tamanho definido ao ser inicializada
    int inseridos; //Números já inseridos
}estruturaAuxiliar;

estruturaAuxiliar vetorPrincipal[TAM];

/*
Objetivo: inicializa o programa. deve ser chamado ao inicio do programa 

*/

void inicializar()
{
    for(int i =0; i < TAM; i++){
        vetorPrincipal[i].dados= NULL;
        vetorPrincipal[i].tamanho = 0;
        vetorPrincipal[i].inseridos = 0;
    }
}

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
int criarEstruturaAuxiliar(int posicao, int tamanho)
{
    if(posicao<1 || posicao>TAM){
        return POSICAO_INVALIDA;
    }
    if(tamanho<1){
        return TAMANHO_INVALIDO;
    }
    if(vetorPrincipal[posicao-1].dados!=NULL){
        return JA_TEM_ESTRUTURA_AUXILIAR;
    }
    
    vetorPrincipal[posicao-1].dados = malloc(tamanho * sizeof(int));
    if(vetorPrincipal[posicao-1].dados ==NULL){
        return SEM_ESPACO_DE_MEMORIA;
    }

    vetorPrincipal[posicao-1].tamanho = tamanho;
    vetorPrincipal[posicao-1].inseridos = 0;
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

int inserirNumeroEmEstrutura(int posicao, int valor) {
    if (posicao < 1 || posicao > TAM) {
        return POSICAO_INVALIDA;
    }

    if (vetorPrincipal[posicao - 1].dados == NULL) {
        return SEM_ESTRUTURA_AUXILIAR;
    }

    if (vetorPrincipal[posicao - 1].inseridos >= vetorPrincipal[posicao - 1].tamanho) {
        return SEM_ESPACO;
    }

    vetorPrincipal[posicao - 1].dados[vetorPrincipal[posicao - 1].inseridos] = valor;
    vetorPrincipal[posicao - 1].inseridos++;

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
int excluirNumeroDoFinaldaEstrutura(int posicao)
{
    if (posicao <1 || posicao> TAM){
        return POSICAO_INVALIDA;
    }

    if(vetorPrincipal[posicao-1].dados == NULL){
        return POSICAO_INVALIDA;
    }
    if(vetorPrincipal[posicao-1].inseridos ==0){
        return ESTRUTURA_AUXILIAR_VAZIA;
    }
    vetorPrincipal[posicao - 1].inseridos--;
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
int excluirNumeroEspecificoDeEstrutura(int posicao, int valor)
{
    if (posicao < 1 || posicao > TAM) {
        return POSICAO_INVALIDA;
    }

    if (vetorPrincipal[posicao - 1].dados == NULL) {
        return SEM_ESTRUTURA_AUXILIAR;
    }
    int encontrado = -1;
    for (int i = 0; i < vetorPrincipal[posicao - 1].inseridos; i++) {
        if (vetorPrincipal[posicao - 1].dados[i] == valor) {
            encontrado = i;
            break;
        }
    }

    if (encontrado == -1) {
        return NUMERO_INEXISTENTE;
    }

    for (int i = encontrado; i < vetorPrincipal[posicao - 1].inseridos - 1; i++) {
        vetorPrincipal[posicao - 1].dados[i] = vetorPrincipal[posicao - 1].dados[i + 1];
    }

    vetorPrincipal[posicao - 1].inseridos--;

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
//Jenni
int getDadosEstruturaAuxiliar(int posicao, int vetorAux[])
{
 if (posicao < 1 || posicao > TAM) {
        return POSICAO_INVALIDA;
    }

    if (vetorPrincipal[posicao - 1].dados == NULL) {
        return SEM_ESTRUTURA_AUXILIAR;
    }

    for (int i = 0; i < vetorPrincipal[posicao - 1].inseridos; i++) {
        vetorAux[i] = vetorPrincipal[posicao - 1].dados[i];
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
int getDadosOrdenadosEstruturaAuxiliar(int posicao, int vetorAux[])
{
    if(posicao < 1 || posicao>TAM){
        return POSICAO_INVALIDA;
    }

    if(vetorPrincipal[posicao - 1].dados == NULL){
        return SEM_ESTRUTURA_AUXILIAR;
    }

    for(int i =0; i < vetorPrincipal[posicao-1].inseridos; i++){
        vetorAux[i] = vetorPrincipal[posicao-1].dados[i];
    }
    int inseridos= vetorPrincipal[posicao - 1].inseridos;
    for(int i = 0; i < inseridos -1; i++){
        for(int j =i+1; j<inseridos; j++){
            if(vetorAux[i]>vetorAux[j]){
                int temp = vetorAux[i];
                vetorAux[i]= vetorAux[j];
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
//Jenni
int getDadosDeTodasEstruturasAuxiliares(int vetorAux[])
{
 int indice = 0;

    for (int i = 0; i < TAM; i++) {
        if (vetorPrincipal[i].dados != NULL && vetorPrincipal[i].inseridos > 0) {
            for (int j = 0; j < vetorPrincipal[i].inseridos; j++) {
                vetorAux[indice++] = vetorPrincipal[i].dados[j];
            }
        }
    }

    if (indice == 0) {
        return TODAS_ESTRUTURAS_AUXILIARES_VAZIAS;
    }

    return SUCESSO;
}

/*
Objetivo: retorna os números ordenados de todas as estruturas auxiliares.
os números devem ser armazenados em vetorAux

Rertono (int)
    SUCESSO - recuperado com sucesso os valores da estrutura na posição 'posicao'
    TODAS_ESTRUTURAS_AUXILIARES_VAZIAS - todas as estruturas auxiliares estão vazias
*/
//Jenni
int getDadosOrdenadosDeTodasEstruturasAuxiliares(int vetorAux[])
{
int indice = 0;

    for (int i = 0; i < TAM; i++) {
        if (vetorPrincipal[i].dados != NULL && vetorPrincipal[i].inseridos > 0) {
            for (int j = 0; j < vetorPrincipal[i].inseridos; j++) {
                vetorAux[indice++] = vetorPrincipal[i].dados[j];
            }
        }
    }

    if (indice == 0) {
        return TODAS_ESTRUTURAS_AUXILIARES_VAZIAS;
    }

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
//Jenni
int modificarTamanhoEstruturaAuxiliar(int posicao, int novoTamanho)
{
 if (posicao < 1 || posicao > TAM) {
        return POSICAO_INVALIDA;
    }

    if (vetorPrincipal[posicao - 1].dados == NULL) {
        return SEM_ESTRUTURA_AUXILIAR;
    }

    if (vetorPrincipal[posicao - 1].tamanho + novoTamanho < 1) {
        return NOVO_TAMANHO_INVALIDO;
    }

    int novoTamanhoFinal = vetorPrincipal[posicao - 1].tamanho + novoTamanho;
    int *novoDados = realloc(vetorPrincipal[posicao - 1].dados, novoTamanhoFinal * sizeof(int));

    if (novoDados == NULL) {
        return SEM_ESPACO_DE_MEMORIA;
    }

    vetorPrincipal[posicao - 1].dados = novoDados;
    vetorPrincipal[posicao - 1].tamanho = novoTamanhoFinal;

    if (vetorPrincipal[posicao - 1].inseridos > novoTamanhoFinal) {
        vetorPrincipal[posicao - 1].inseridos = novoTamanhoFinal;
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
// Jenni
int getQuantidadeElementosEstruturaAuxiliar(int posicao)
{
if (posicao < 1 || posicao > TAM) {
        return POSICAO_INVALIDA;
    }

    if (vetorPrincipal[posicao - 1].dados == NULL) {
        return SEM_ESTRUTURA_AUXILIAR;
    }

    return vetorPrincipal[posicao - 1].inseridos;
}

/*
Objetivo: montar a lista encadeada com cabeçote com todos os números presentes em todas as estruturas.

Retorno (No*)
    NULL, caso não tenha nenhum número nas listas
    No*, ponteiro para o início da lista com cabeçote
*/
//Jenni
void inserirNoFim(No **cabecote, int valor){
 No *novo = (No *)malloc(sizeof(No));
    if (novo == NULL) {
        printf("Erro ao alocar memória.\n");
        return;
    }

    novo->conteudo = valor;
    novo->prox = NULL;

    if (*cabecote == NULL) {
        *cabecote = novo;
        return;
    }

    No *aux = *cabecote;
    while (aux->prox != NULL) {
        aux = aux->prox;
    }
    aux->prox = novo;
}
No *montarListaEncadeadaComCabecote()
{
No *cabecote = NULL;

    for (int i = 0; i < TAM; i++) {
        if (vetorPrincipal[i].dados != NULL && vetorPrincipal[i].inseridos > 0) {
            for (int j = 0; j < vetorPrincipal[i].inseridos; j++) {
                inserir_no_fim(&cabecote, vetorPrincipal[i].dados[j]);
            }
        }
    }

    return cabecote;
}

/*
Objetivo: retorna os números da lista enceada com cabeçote armazenando em vetorAux.
Retorno void
*/
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
void destruirListaEncadeadaComCabecote(No **inicio){
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

void finalizar(){
    for (int i = 0; i < TAM; i++) {
        if (vetorPrincipal[i].dados != NULL) {
            free(vetorPrincipal[i].dados);
            vetorPrincipal[i].dados = NULL;
        }
    }
}
