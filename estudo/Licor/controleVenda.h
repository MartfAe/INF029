#ifndef CONTROLEVENDA_H
#define CONTROLEVENDA_H


#define maxNome 30 
#define MAX_LICORES 100

typedef struct{
    char sabor[maxNome];
    float valorCusto;
    float valorVenda;
    int qtdVendidos;
    int qtdEstoque; 
} Licor;


void ToUpperStr(char destino[], const char origem[]);

void limparBuffer();

void cadastrarLicor(Licor *licores, int *totalLicores);

void vendaLicor(Licor *licores, int totalLicores);

float calcularLucroTotalGeral(const Licor *licores, int totalLicores);

void lerRelatorioLicores(const char *nomeArquivo, Licor *licores, int *totalLicores);

void salvarDadosLicores(const char *nomeArquivo, const Licor *licores, int totalLicores);

void carregarDadosLicores(const char *nomeArquivo, Licor *licores, int *totalLicores);

void gerarRelatorioLicores(const Licor *licores, int totalLicores, const char *nomeArquivo);

#endif


