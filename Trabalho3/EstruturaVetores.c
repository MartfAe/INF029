#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define TAM 10

#include "EstruturaVetores.h"

estruturaAuxiliar *estruturaPrincipal;

/* Inicializa a estrutura principal, criando o arquivo de dados se necessário,
   aloca dinamicamente o vetor de estruturas e carrega os dados do arquivo. */
   void inicializar() {
    const char *arquivo = "dados.txt";
    FILE *fp = fopen(arquivo, "r");

    if (fp == NULL) {
        fp = fopen(arquivo, "w");
        if (fp == NULL) {
            perror("Erro ao criar o arquivo");
            return;
        }
        printf("Arquivo '%s' criado com sucesso.\n", arquivo);
    } else {
        fclose(fp);
    }

    estruturaPrincipal = (estruturaAuxiliar *)malloc(TAM * sizeof(estruturaAuxiliar));
    if (estruturaPrincipal == NULL) {
        perror("Erro ao alocar memória para a estrutura principal");
        return;
    }

    for (int i = 0; i < TAM; i++) {
        estruturaPrincipal[i].dados = NULL;
        estruturaPrincipal[i].tamanho = 0;
        estruturaPrincipal[i].qtd = 0;
    }

    carregarDadosArquivo(arquivo);
}


/* Cria uma estrutura auxiliar na posição 'posicao' com tamanho 'tamanho' */
int criarEstruturaAuxiliar(int posicao, int tamanho) {
    if (posicao < 1 || posicao > TAM) return POSICAO_INVALIDA; // Verificação direta
    if (estruturaPrincipal[posicao - 1].dados != NULL) return JA_TEM_ESTRUTURA_AUXILIAR;
    if (tamanho < 1) return TAMANHO_INVALIDO;

    estruturaPrincipal[posicao - 1].dados = (int *)malloc(tamanho * sizeof(int));
    if (estruturaPrincipal[posicao - 1].dados == NULL) return SEM_ESPACO_DE_MEMORIA;

    estruturaPrincipal[posicao - 1].tamanho = tamanho;
    estruturaPrincipal[posicao - 1].qtd = 0;
    return SUCESSO;
}


/* Insere o valor 'valor' na estrutura auxiliar da posição 'posicao' */
int inserirNumeroEmEstrutura(int posicao, int valor) {
    if (posicao < 1 || posicao > TAM) return POSICAO_INVALIDA; 
    if (estruturaPrincipal[posicao - 1].dados == NULL) return SEM_ESTRUTURA_AUXILIAR;
    if (estruturaPrincipal[posicao - 1].qtd >= estruturaPrincipal[posicao - 1].tamanho) return SEM_ESPACO;

    estruturaPrincipal[posicao - 1].dados[estruturaPrincipal[posicao - 1].qtd++] = valor;
    salvarDadosArquivo(estruturaPrincipal, TAM, "dados.txt");
    return SUCESSO;
}
/* Exclui o último número da estrutura auxiliar da posição 'posicao' */
int excluirNumeroDoFinaldaEstrutura(int posicao) {
    if (posicao < 1 || posicao > TAM) 
        return POSICAO_INVALIDA;
    if (estruturaPrincipal[posicao - 1].dados == NULL) 
        return SEM_ESTRUTURA_AUXILIAR;
    if (estruturaPrincipal[posicao - 1].qtd == 0) 
        return ESTRUTURA_AUXILIAR_VAZIA;

    estruturaPrincipal[posicao - 1].qtd--;
    salvarDadosArquivo(estruturaPrincipal, TAM, "dados.txt");
    return SUCESSO;
}

/* Exclui o número 'valor' da estrutura auxiliar da posição 'posicao',
   deslocando os elementos subsequentes para ocupar a posição excluída. */
int excluirNumeroEspecificoDeEstrutura(int posicao, int valor) {
    if (posicao < 1 || posicao > TAM)
        return POSICAO_INVALIDA;
    if (estruturaPrincipal[posicao - 1].dados == NULL)
        return SEM_ESTRUTURA_AUXILIAR;

    int posicaoEncontrada = -1;
    for (int i = 0; i < estruturaPrincipal[posicao - 1].qtd; i++) {
        if (estruturaPrincipal[posicao - 1].dados[i] == valor) {
            posicaoEncontrada = i;
            break;
        }
    }
    if (posicaoEncontrada == -1)
        return NUMERO_INEXISTENTE;

    for (int i = posicaoEncontrada; i < estruturaPrincipal[posicao - 1].qtd - 1; i++) {
        estruturaPrincipal[posicao - 1].dados[i] = estruturaPrincipal[posicao - 1].dados[i+1];
    }
    estruturaPrincipal[posicao - 1].qtd--;

    salvarDadosArquivo(estruturaPrincipal, TAM, "dados.txt");
    return SUCESSO;
}

/* Copia os dados da estrutura auxiliar da posição 'posicao' para vetorAux */
int getDadosEstruturaAuxiliar(int posicao, int vetorAux[]) {
    if (posicao < 1 || posicao > TAM)
        return POSICAO_INVALIDA;
    if (estruturaPrincipal[posicao - 1].dados == NULL)
        return SEM_ESTRUTURA_AUXILIAR;

    for (int i = 0; i < estruturaPrincipal[posicao - 1].qtd; i++) {
        vetorAux[i] = estruturaPrincipal[posicao - 1].dados[i];
    }


    return SUCESSO;
}

/* Copia os dados da estrutura auxiliar da posição 'posicao' para vetorAux
   e os ordena (usando Selection Sort) */
int getDadosOrdenadosEstruturaAuxiliar(int posicao, int vetorAux[]) {
    if (posicao < 1 || posicao > TAM)
        return POSICAO_INVALIDA;
    if (estruturaPrincipal[posicao - 1].dados == NULL)
        return SEM_ESTRUTURA_AUXILIAR;

    int qtd = estruturaPrincipal[posicao - 1].qtd;
    for (int i = 0; i < qtd; i++) {
        vetorAux[i] = estruturaPrincipal[posicao - 1].dados[i];
    }
    for (int i = 0; i < qtd - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < qtd; j++) {
            if (vetorAux[j] < vetorAux[minIndex])
                minIndex = j;
        }
        if (minIndex != i) {
            int temp = vetorAux[i];
            vetorAux[i] = vetorAux[minIndex];
            vetorAux[minIndex] = temp;
        }
    }
    return SUCESSO;
}

/* Percorre todas as estruturas auxiliares, copiando seus dados para vetorAux */
int getDadosDeTodasEstruturasAuxiliares(int vetorAux[]) {
    int indice = 0;
    for (int i = 0; i < TAM; i++) {
        if (estruturaPrincipal[i].dados != NULL && estruturaPrincipal[i].qtd > 0) {
            for (int j = 0; j < estruturaPrincipal[i].qtd; j++) {
                vetorAux[indice++] = estruturaPrincipal[i].dados[j];
            }
        }
    }
    if (indice == 0)
        return TODAS_ESTRUTURAS_AUXILIARES_VAZIAS;
    return SUCESSO;
}

/* Percorre todas as estruturas auxiliares, copia seus dados para vetorAux,
   e ordena o vetor resultante (usando Bubble Sort) */
int getDadosOrdenadosDeTodasEstruturasAuxiliares(int vetorAux[]) {
    int indice = 0;
    for (int i = 0; i < TAM; i++) {
        if (estruturaPrincipal[i].dados != NULL && estruturaPrincipal[i].qtd > 0) {
            for (int j = 0; j < estruturaPrincipal[i].qtd; j++) {
                vetorAux[indice++] = estruturaPrincipal[i].dados[j];
            }
        }
    }
    if (indice == 0)
        return TODAS_ESTRUTURAS_AUXILIARES_VAZIAS;

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

/* Modifica o tamanho da estrutura auxiliar da posição 'posicao'.
   O novo tamanho será o atual somado a novoTamanho (deve ser >= 1). */
int modificarTamanhoEstruturaAuxiliar(int posicao, int novoTamanho) {
    if (posicao < 1 || posicao > TAM)
        return POSICAO_INVALIDA;
    if (estruturaPrincipal[posicao - 1].dados == NULL)
        return SEM_ESTRUTURA_AUXILIAR;

    int novoTam = estruturaPrincipal[posicao - 1].tamanho + novoTamanho;
    if (novoTam < 1)
        return NOVO_TAMANHO_INVALIDO;

    int *novoDados = realloc(estruturaPrincipal[posicao - 1].dados, novoTam * sizeof(int));
    if (novoDados == NULL)
        return SEM_ESPACO_DE_MEMORIA;

    estruturaPrincipal[posicao - 1].dados = novoDados;
    estruturaPrincipal[posicao - 1].tamanho = novoTam;
    if (estruturaPrincipal[posicao - 1].qtd > novoTam)
        estruturaPrincipal[posicao - 1].qtd = novoTam;

    salvarDadosArquivo(estruturaPrincipal, TAM, "dados.txt");
    return SUCESSO;
}

/* Retorna a quantidade de elementos preenchidos da estrutura auxiliar da posição 'posicao' */
int getQuantidadeElementosEstruturaAuxiliar(int posicao) {
    if (posicao < 1 || posicao > TAM)
        return POSICAO_INVALIDA;
    if (estruturaPrincipal[posicao - 1].dados == NULL)
        return SEM_ESTRUTURA_AUXILIAR;
    return estruturaPrincipal[posicao - 1].qtd;
}

/* FUNÇÕES PARA MANIPULAÇÃO DA LISTA ENCADEADA */

/* Insere um novo nó com o valor 'valor' no final da lista encadeada */
void inserir_no_fim(No **cabecote, int valor) {
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

/* Monta uma lista encadeada com todos os números presentes em todas as estruturas auxiliares */
No *montarListaEncadeadaComCabecote() {
    No *cabecote = NULL;
    for (int i = 0; i < TAM; i++) {
        if (estruturaPrincipal[i].dados != NULL && estruturaPrincipal[i].qtd > 0) {
            for (int j = 0; j < estruturaPrincipal[i].qtd; j++) {
                inserir_no_fim(&cabecote, estruturaPrincipal[i].dados[j]);
            }
        }
    }
    return cabecote;
}

/* Copia os dados da lista encadeada para vetorAux */
void getDadosListaEncadeadaComCabecote(No *inicio, int vetorAux[]) {
    if (inicio == NULL) {
        printf("A lista encadeada está vazia.\n");
        return;
    }
    int i = 0;
    No *aux = inicio;
    while (aux != NULL) {
        vetorAux[i++] = aux->conteudo;
        aux = aux->prox;
    }
}

/* Destroi a lista encadeada e define o ponteiro para NULL */
void destruirListaEncadeadaComCabecote(No **inicio) {
    if (*inicio == NULL)
        return;
    No *aux = *inicio;
    while (aux != NULL) {
        No *temp = aux;
        aux = aux->prox;
        free(temp);
    }
    *inicio = NULL;
}

/* FUNÇÕES PARA SALVAR E CARREGAR DADOS */

/* Carrega os dados do arquivo 'nomeArquivo' para as estruturas auxiliares.
   Para cada linha, lê o tamanho e a quantidade de elementos, cria a estrutura
   e insere os elementos lidos. */
   int carregarDadosArquivo(const char *nomeArquivo){
    FILE *fp = fopen(nomeArquivo, "r");
    if (fp == NULL) {
        printf("Erro ao abrir o arquivo para leitura.\n");
        return 0;
    }

    int posicao, qtd, tamanho, valor;
    while (fscanf(fp, "%d %d %d", &posicao, &qtd, &tamanho) == 3) {
        if (posicao < 1 || posicao > TAM || tamanho < 0 || qtd < 0 || qtd > tamanho) {
            printf("Dados inválidos no arquivo.\n");
            fclose(fp);
            return 0;
        }

        criarEstruturaAuxiliar(posicao, tamanho);
        for (int i = 0; i < qtd; i++) {
            if (fscanf(fp, "%d", &valor) != 1) {
                printf("Erro ao ler valor do arquivo.\n");
                fclose(fp);
                return 0;
            }
            inserirNumeroEmEstrutura(posicao, valor);
        }
    }

    fclose(fp);
    return 1;
}

/* Salva os dados das estruturas auxiliares no arquivo 'nomeArquivo'.
   Cada linha contém o tamanho, a quantidade de elementos e os elementos da estrutura. */
   void salvarDadosArquivo(estruturaAuxiliar *estrutura, int tamanho, const char *nomeArquivo) {
    FILE *fp = fopen(nomeArquivo, "w");
    if (fp == NULL) {
        perror("Erro ao abrir o arquivo para salvar dados");
        return;
    }

    for (int i = 0; i < tamanho; i++) {
        fprintf(fp, "%d %d %d", i + 1, estrutura[i].qtd, estrutura[i].tamanho);
        for (int j = 0; j < estrutura[i].qtd; j++) {
            fprintf(fp, " %d", estrutura[i].dados[j]);
        }
        fprintf(fp, "\n");
    }

    fclose(fp);
}


/* Finaliza o programa salvando os dados em arquivo e liberando toda a memória alocada */
void finalizar() {
    const char *arquivo = "dados.txt";
    salvarDadosArquivo(estruturaPrincipal, TAM, arquivo);

    for (int i = 0; i < TAM; i++) {
        if (estruturaPrincipal[i].dados != NULL) {
            free(estruturaPrincipal[i].dados);
            estruturaPrincipal[i].dados = NULL;
        }
    }
    free(estruturaPrincipal);
    estruturaPrincipal = NULL;
}