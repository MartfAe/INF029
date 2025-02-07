#ifndef TRABALHO2_ESTRUTURAVETORES_H
#define TRABALHO2_ESTRUTURAVETORES_H

// Constantes e enumerações
enum { 
    TODAS_ESTRUTURAS_AUXILIARES_VAZIAS = -11, 
    NOVO_TAMANHO_INVALIDO, 
    NUMERO_INEXISTENTE,
    ESTRUTURA_AUXILIAR_VAZIA, 
    TAMANHO_INVALIDO, 
    SEM_ESPACO_DE_MEMORIA, 
    POSICAO_INVALIDA,
    JA_TEM_ESTRUTURA_AUXILIAR, 
    SEM_ESTRUTURA_AUXILIAR, 
    SEM_ESPACO, 
    SUCESSO 
};

#define TAM 10

// Estrutura para lista encadeada
typedef struct reg {
    int conteudo;
    struct reg *prox;
} No;

// Definição da estrutura auxiliar
typedef struct {
    int *dados;
    int tamanho;
    int qtd; 
} estruturaAuxiliar;

// Ponteiro para a estrutura principal (alocação dinâmica)
extern estruturaAuxiliar *estruturaPrincipal;

/* Declaração das funções */

// Inicialização e finalização
void inicializar();
void finalizar();

// Operações com estruturas auxiliares
int criarEstruturaAuxiliar(int posicao, int tamanho);
int inserirNumeroEmEstrutura(int posicao, int valor);
int excluirNumeroDoFinaldaEstrutura(int posicao);
int excluirNumeroEspecificoDeEstrutura(int posicao, int valor);

// Recuperação dos dados das estruturas auxiliares
int getDadosEstruturaAuxiliar(int posicao, int vetorAux[]);
int getDadosOrdenadosEstruturaAuxiliar(int posicao, int vetorAux[]);
int getDadosDeTodasEstruturasAuxiliares(int vetorAux[]);
int getDadosOrdenadosDeTodasEstruturasAuxiliares(int vetorAux[]);

// Modificação e consulta do tamanho da estrutura auxiliar
int modificarTamanhoEstruturaAuxiliar(int posicao, int novoTamanho);
int getQuantidadeElementosEstruturaAuxiliar(int posicao);

// Operações com lista encadeada
No *montarListaEncadeadaComCabecote();
void getDadosListaEncadeadaComCabecote(No *inicio, int vetorAux[]);
void destruirListaEncadeadaComCabecote(No **inicio);

// Funções para salvar e carregar dados
estruturaAuxiliar *carregarDadosArquivo(const char *nomeArquivo);
void salvarDadosArquivo(estruturaAuxiliar *estrutura, int tamanho, const char *nomeArquivo);

#endif // TRABALHO2_ESTRUTURAVETORES_H
