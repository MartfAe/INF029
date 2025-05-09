#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include "controleVenda.h"

int main() {
    setlocale(LC_ALL, "pt_BR.UTF-8");
    
    Licor licores[MAX_LICORES];
    int totalLicores = 0;
    int opcao;

    carregarDadosLicores("dados_licores.dat", licores, &totalLicores);

    do {
        printf("\n==== MENU LICORARIA ====\n");
        printf("1. Cadastrar licor\n");
        printf("2. Registrar venda\n");
        printf("3. Gerar relatório (TXT)\n");
        printf("4. Gerar relatório (PDF)\n");  // Nova opção
        printf("0. Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        limparBuffer();

        switch (opcao) {
            case 1:
                cadastrarLicor(licores, &totalLicores); 
                break;
            case 2:
                vendaLicor(licores, totalLicores);
                break;
            case 3:
                gerarRelatorioLicores(licores, totalLicores, "relatorio_licores.txt");
                break;
            case 4:  // Gera PDF
                // Primeiro gera o TXT
                gerarRelatorioLicores(licores, totalLicores, "relatorio_licores.txt");
                
                // Comando para chamar o script Python
                system("python gerar_pdf.py relatorio_licores.txt relatorio_licores.pdf");
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida.\n");
        }

    } while (opcao != 0);

    return 0;
}