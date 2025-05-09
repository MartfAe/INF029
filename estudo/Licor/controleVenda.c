#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <locale.h>
#include "controleVenda.h"




void ToUpperStr(char destino[], const char origem[]) {
    int i = 0;
    while (origem[i] != '\0') {
        destino[i] = toupper(origem[i]);
        i++;
    }
    destino[i] = '\0';
}

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Função para cadastrar um licor
void cadastrarLicor(Licor *licores, int *totalLicores) {
    setlocale(LC_ALL, "pt_BR.UTF-8");

    char saborOriginal[maxNome];
    int i, encontrado = 0;

    printf("Digite o sabor do licor que deseja cadastrar: ");
    fgets(saborOriginal, sizeof(saborOriginal), stdin);
    saborOriginal[strcspn(saborOriginal, "\n")] = '\0';  
    ToUpperStr(saborOriginal, saborOriginal);  // Formatar para maiúsculas

    // Verifica se o licor já existe no relatório
    for (i = 0; i < *totalLicores; i++) {
        if (strcmp(licores[i].sabor, saborOriginal) == 0) {
            encontrado = 1;
            break;
        }
    }

   if (encontrado) {
        // Validação da quantidade adicional
        int qtdAdicional;
        do {
            printf("Digite a quantidade adicional de garrafas (>= 0): ");
            scanf("%d", &qtdAdicional);
        } while (qtdAdicional < 0);
        
        licores[i].qtdEstoque += qtdAdicional;
        limparBuffer();
    } else {
        // Validação do valor de custo
        do {
            printf("Digite o valor de custo (>= 0): ");
            scanf("%f", &licores[*totalLicores].valorCusto);
        } while (licores[*totalLicores].valorCusto < 0);

        // Validação da quantidade em estoque
        do {
            printf("Digite a quantidade de garrafas (>= 0): ");
            scanf("%d", &licores[*totalLicores].qtdEstoque);
        } while (licores[*totalLicores].qtdEstoque < 0);

        // Validação do valor de venda
        do {
            printf("Digite o valor de venda (>= 0): ");
            scanf("%f", &licores[*totalLicores].valorVenda);
        } while (licores[*totalLicores].valorVenda < 0);

        strcpy(licores[*totalLicores].sabor, saborOriginal);
        licores[*totalLicores].qtdVendidos = 0;
        (*totalLicores)++;
    }

    // Salva os dados após cadastro/atualização
    salvarDadosLicores("dados_licores.dat", licores, *totalLicores);
    printf("Licor registrado ou atualizado com sucesso.\n");
}

// Função para registrar uma venda de licor
void vendaLicor(Licor *licores, int totalLicores) {
    char saborBusca[maxNome];
    char saborFormatado[maxNome];
    int qtdVenda;
    int encontrado = 0;

    printf("Digite o sabor vendido: ");
    fgets(saborBusca, sizeof(saborBusca), stdin);
    saborBusca[strcspn(saborBusca, "\n")] = 0;
    ToUpperStr(saborFormatado, saborBusca);

    for (int i = 0; i < totalLicores; i++) {
        if (strcmp(licores[i].sabor, saborFormatado) == 0) {
            encontrado = 1;

            printf("Estoque disponível: %d\n", licores[i].qtdEstoque);
            do {
                printf("Digite a quantidade vendida (1-%d): ", licores[i].qtdEstoque);
                scanf("%d", &qtdVenda);
            } while (qtdVenda <= 0 || qtdVenda > licores[i].qtdEstoque);

            licores[i].qtdEstoque -= qtdVenda;
            licores[i].qtdVendidos += qtdVenda;

            // Salva os dados após a venda
            salvarDadosLicores("dados_licores.dat", licores, totalLicores);
            printf("Venda registrada com sucesso.\n");
            break;  // Interrompe o loop após encontrar
        }
    }

    if (!encontrado) {
        printf("Licor com sabor '%s' não encontrado.\n", saborFormatado);  // Usar saborFormatado
    }
}

// Função para calcular o lucro total geral
float calcularLucroTotalGeral(const Licor *licores, int totalLicores) {
    float lucroTotal = 0.0;

    for (int i = 0; i < totalLicores; i++) {
        lucroTotal += (licores[i].valorVenda - licores[i].valorCusto) * licores[i].qtdVendidos;
    }

    return lucroTotal;
}
