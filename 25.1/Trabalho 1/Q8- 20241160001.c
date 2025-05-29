#include <stdio.h>
#include <stdlib.h>
#include <ctype.h> // Para toupper()
#include <string.h> // Para memset() - opcional, mas útil

// Nome da matriz alterado
char grade_jogo[3][3];

// === FUNÇÕES DO JOGO ===


void iniciar_grade() {

    for (int l = 0; l < 3; l++) {
        for (int c = 0; c < 3; c++) {
            grade_jogo[l][c] = ' ';
        }
    }
}


void exibir_grade() {
    printf("\n   _1___2___3_\n"); // Layout ligeiramente alterado
    printf("A | %c | %c | %c |\n", grade_jogo[0][0], grade_jogo[0][1], grade_jogo[0][2]);
    printf("  +---+---+---+\n");
    printf("B | %c | %c | %c |\n", grade_jogo[1][0], grade_jogo[1][1], grade_jogo[1][2]);
    printf("  +---+---+---+\n");
    printf("C | %c | %c | %c |\n\n", grade_jogo[2][0], grade_jogo[2][1], grade_jogo[2][2]);
}


int checar_vencedor(char simbolo) {
    // Verifica linhas e colunas
    for (int i = 0; i < 3; i++) {
        if (grade_jogo[i][0] == simbolo && grade_jogo[i][1] == simbolo && grade_jogo[i][2] == simbolo) return 1;
        if (grade_jogo[0][i] == simbolo && grade_jogo[1][i] == simbolo && grade_jogo[2][i] == simbolo) return 1;
    }
    // Verifica diagonais
    if (grade_jogo[0][0] == simbolo && grade_jogo[1][1] == simbolo && grade_jogo[2][2] == simbolo) return 1;
    if (grade_jogo[0][2] == simbolo && grade_jogo[1][1] == simbolo && grade_jogo[2][0] == simbolo) return 1;

    return 0; // Ninguém ganhou ainda
}

int checar_empate() {
    // Conta quantas casas estão preenchidas
    int preenchidas = 0;
    for (int l = 0; l < 3; l++) {
        for (int c = 0; c < 3; c++) {
            if (grade_jogo[l][c] != ' ') {
                preenchidas++;
            }
        }
    }
    // Se 9 casas estão preenchidas (e ninguém ganhou), é empate.
    return (preenchidas == 9);
}

int traduzir_coordenada(char entrada_linha, int entrada_coluna, int* saida_linha, int* saida_coluna) {
    entrada_linha = toupper(entrada_linha); // Converte para maiúscula

    // Validação da entrada
    if (entrada_linha >= 'A' && entrada_linha <= 'C' && entrada_coluna >= 1 && entrada_coluna <= 3) {
        *saida_linha = entrada_linha - 'A'; // 'A' -> 0, 'B' -> 1, 'C' -> 2
        *saida_coluna = entrada_coluna - 1; // 1 -> 0, 2 -> 1, 3 -> 2
        return 1; // Válido
    }
    return 0; // Inválido
}

// === FUNÇÃO PRINCIPAL ===

int main() {
    int jogador_atual = 1; // Começa com o jogador 1
    char simbolo_atual;
    char input_l;
    int input_c;
    int l_matriz, c_matriz;
    int jogo_terminou = 0; // Flag para controlar o fim do jogo

    iniciar_grade(); // Limpa o tabuleiro

    // Loop principal do jogo
    while (jogo_terminou == 0) {
        exibir_grade();

        simbolo_atual = (jogador_atual == 1) ? 'X' : 'O'; // Define o símbolo do jogador
        printf("Vez do Jogador %d (%c). Informe a jogada (ex: C2): ", jogador_atual, simbolo_atual);
        
        // Loop para garantir uma jogada válida
        int jogada_valida = 0;
        while (!jogada_valida) {
            // Lê a entrada do usuário
            if (scanf(" %c%d", &input_l, &input_c) != 2) {
                 printf("Formato de entrada incorreto. Use LetraNumero (ex: A1). Tente de novo: ");
                 // Limpa o buffer de entrada em caso de erro
                 while (getchar() != '\n'); 
                 continue;
            }

            // Tenta converter e validar a coordenada
            if (!traduzir_coordenada(input_l, input_c, &l_matriz, &c_matriz)) {
                printf("Jogada fora do tabuleiro! Use A, B ou C e 1, 2 ou 3. Tente de novo: ");
            } 
            // Verifica se a posição já está ocupada
            else if (grade_jogo[l_matriz][c_matriz] != ' ') {
                printf("Essa casa ja foi escolhida! Tente de novo: ");
            } 
            // Se chegou aqui, a jogada é válida
            else {
                jogada_valida = 1;
            }
        }

        // Realiza a jogada
        grade_jogo[l_matriz][c_matriz] = simbolo_atual;

        // Verifica se houve vitória
        if (checar_vencedor(simbolo_atual)) {
            exibir_grade();
            printf("Vitoria do Jogador %d (%c)! Fim de jogo!\n", jogador_atual, simbolo_atual);
            jogo_terminou = 1;
        } 
        // Verifica se houve empate
        else if (checar_empate()) {
            exibir_grade();
            printf("O jogo terminou em empate! (Velha)\n");
            jogo_terminou = 1;
        } 
        // Se não terminou, troca o jogador
        else {
            jogador_atual = (jogador_atual == 1) ? 2 : 1;
        }
    }

    return 0; // Fim do programa
}