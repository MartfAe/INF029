#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include "controleVenda.h"

// ==================================================
// Funções para Persistência de Dados (arquivo binário)
// ==================================================

void salvarDadosLicores(const char *nomeArquivo, const Licor *licores, int totalLicores) {
    FILE *arquivo = fopen(nomeArquivo, "wb");
    if (arquivo == NULL) {
        printf("Erro ao salvar dados!\n");
        return;
    }
    
    // Escreve todos os licores de uma vez
    fwrite(licores, sizeof(Licor), totalLicores, arquivo);
    fclose(arquivo);
}

void carregarDadosLicores(const char *nomeArquivo, Licor *licores, int *totalLicores) {
    FILE *arquivo = fopen(nomeArquivo, "rb");
    if (arquivo == NULL) {
        printf("Arquivo de dados não encontrado. Iniciando novo.\n");
        return;
    }

    // Lê os dados em blocos
    *totalLicores = fread(licores, sizeof(Licor), MAX_LICORES, arquivo);
    fclose(arquivo);
}

// ==================================================
// Função para Gerar Relatório (arquivo texto)
// ==================================================

void gerarRelatorioLicores(const Licor *licores, int totalLicores, const char *nomeArquivo) {
    setlocale(LC_ALL, "pt_BR.UTF-8");
    FILE *arquivo = fopen(nomeArquivo, "w");

    if (arquivo == NULL) {
        printf("Erro ao criar o arquivo de relatório.\n");
        return;
    }

    fprintf(arquivo, "====== RELATÓRIO DE LICORES ======\n\n");
    float lucroTotal = 0.0;
    float investimentoTotal = 0.0;

    for (int i = 0; i < totalLicores; i++) {
        float lucro = (licores[i].valorVenda - licores[i].valorCusto) * licores[i].qtdVendidos;
        lucroTotal += lucro;
        float investimento = licores[i].valorCusto * licores[i].qtdEstoque;
        investimentoTotal += investimento;

        fprintf(arquivo, "Licor: %s\n", licores[i].sabor);
        fprintf(arquivo, "Estoque atual: %d unidades\n", licores[i].qtdEstoque);
        fprintf(arquivo, "Valor de Custo: R$ %.2f\n", licores[i].valorCusto);
        fprintf(arquivo, "Valor de Venda: R$ %.2f\n", licores[i].valorVenda);
        fprintf(arquivo, "Quantidade vendida: %d\n", licores[i].qtdVendidos);
        fprintf(arquivo, "Lucro com esse sabor: R$ %.2f\n", lucro);
        fprintf(arquivo, "Investimento nesse sabor: R$ %.2f\n", investimento);
        fprintf(arquivo, "----------------------------------\n");
    }

    fprintf(arquivo, "\nInvestimento TOTAL: R$ %.2f\n", investimentoTotal);
    fprintf(arquivo, "\nLucro TOTAL com todos os licores: R$ %.2f\n", lucroTotal);

    fclose(arquivo);
    printf("Relatório gerado com sucesso: %s\n", nomeArquivo);
}
