#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

#define DIM 3
#define JOGADOR1 'X'
#define JOGADOR2 'O'

void limparTabuleiro(char tab[DIM][DIM]);
void exibirTabuleiro(char tab[DIM][DIM]);
int verificarVitoria(char tab[DIM][DIM], char simbolo);
int tabuleiroCheio(char tab[DIM][DIM]);
int entradaValida(const char entrada[]);
int posicaoValida(char tab[DIM][DIM], int l, int c);
void jogadaCPU(char tab[DIM][DIM], char simbolo, int nivel);
int jogadaEstrategica(char tab[DIM][DIM], char simbolo, int *l_ptr, int *c_ptr);

// ------------------- Funções principais --------------------

void limparTabuleiro(char tab[DIM][DIM]) {
    for (int l = 0; l < DIM; l++)
        for (int c = 0; c < DIM; c++)
            tab[l][c] = ' ';
}

void exibirTabuleiro(char tab[DIM][DIM]) {
    printf("\n    1   2   3\n");
    printf("   -----------\n");
    for (int l = 0; l < DIM; l++) {
        printf("%c |", 'A' + l);
        for (int c = 0; c < DIM; c++)
            printf(" %c |", tab[l][c]);
        printf("\n   -----------\n");
    }
    printf("\n");
}

int entradaValida(const char entrada[]) {
    return (toupper(entrada[0]) >= 'A' && toupper(entrada[0]) <= 'C') &&
           (entrada[1] >= '1' && entrada[1] <= '3') &&
           entrada[2] == '\0';
}

int posicaoValida(char tab[DIM][DIM], int l, int c) {
    return (l >= 0 && l < DIM && c >= 0 && c < DIM && tab[l][c] == ' ');
}

int tabuleiroCheio(char tab[DIM][DIM]) {
    for (int l = 0; l < DIM; l++)
        for (int c = 0; c < DIM; c++)
            if (tab[l][c] == ' ')
                return 0;
    return 1;
}

int verificarVitoria(char tab[DIM][DIM], char simbolo) {
    for (int i = 0; i < DIM; i++) {
        if (tab[i][0] == simbolo && tab[i][1] == simbolo && tab[i][2] == simbolo) return 1;
        if (tab[0][i] == simbolo && tab[1][i] == simbolo && tab[2][i] == simbolo) return 1;
    }
    if (tab[0][0] == simbolo && tab[1][1] == simbolo && tab[2][2] == simbolo) return 1;
    if (tab[0][2] == simbolo && tab[1][1] == simbolo && tab[2][0] == simbolo) return 1;
    return 0;
}

// --------------------- CPU (fácil e difícil) --------------------

int jogadaEstrategica(char tab[DIM][DIM], char simbolo, int *l_ptr, int *c_ptr) {
    char oponente = (simbolo == JOGADOR1) ? JOGADOR2 : JOGADOR1;

    // Tenta vencer
    for (int l = 0; l < DIM; l++)
        for (int c = 0; c < DIM; c++)
            if (tab[l][c] == ' ') {
                tab[l][c] = simbolo;
                if (verificarVitoria(tab, simbolo)) {
                    *l_ptr = l;
                    *c_ptr = c;
                    tab[l][c] = ' ';
                    return 1;
                }
                tab[l][c] = ' ';
            }

    // Tenta bloquear oponente
    for (int l = 0; l < DIM; l++)
        for (int c = 0; c < DIM; c++)
            if (tab[l][c] == ' ') {
                tab[l][c] = oponente;
                if (verificarVitoria(tab, oponente)) {
                    *l_ptr = l;
                    *c_ptr = c;
                    tab[l][c] = ' ';
                    return 1;
                }
                tab[l][c] = ' ';
            }

    return 0;
}

void jogadaCPU(char tab[DIM][DIM], char simbolo, int nivel) {
    int l, c;
    if (nivel == 2 && jogadaEstrategica(tab, simbolo, &l, &c)) {
        tab[l][c] = simbolo;
    } else {
        do {
            l = rand() % DIM;
            c = rand() % DIM;
        } while (!posicaoValida(tab, l, c));
        tab[l][c] = simbolo;
    }
}

// ------------------------- main --------------------------

int main() {
    char tab[DIM][DIM], entrada[4];
    int modo, nivel, turno, placar1 = 0, placar2 = 0;
    char simbolo, jogar_novamente;

    srand(time(NULL));
    printf("== Jogo da Velha ==\n");
    printf("1 - Jogador vs Jogador\n");
    printf("2 - Jogador vs CPU\nEscolha: ");
    scanf("%d", &modo);

    if (modo == 2) {
        printf("Nível da CPU:\n1 - Fácil\n2 - Difícil\nEscolha: ");
        scanf("%d", &nivel);
    }

    do {
        limparTabuleiro(tab);
        turno = 1;

        while (1) {
            exibirTabuleiro(tab);
            simbolo = (turno == 1) ? JOGADOR1 : JOGADOR2;

            if (modo == 2 && turno == 2) {
                printf("Computador (%c) jogando...\n", simbolo);
                jogadaCPU(tab, simbolo, nivel);
            } else {
                printf("Jogador %d (%c), informe a posição (ex: A1): ", turno, simbolo);
                int ok = 0;
                while (!ok) {
                    scanf("%3s", entrada);
                    entrada[2] = '\0';

                    if (!entradaValida(entrada)) {
                        printf("Entrada inválida. Use A1, B2, etc.: ");
                        continue;
                    }

                    int l = toupper(entrada[0]) - 'A';
                    int c = entrada[1] - '1';

                    if (!posicaoValida(tab, l, c)) {
                        printf("Posição ocupada. Tente outra: ");
                        continue;
                    }

                    tab[l][c] = simbolo;
                    ok = 1;
                }
            }

            if (verificarVitoria(tab, simbolo)) {
                exibirTabuleiro(tab);
                if (modo == 2 && turno == 2) {
                    printf("O Computador venceu!\n");
                    placar2++;
                } else {
                    printf("Jogador %d venceu!\n", turno);
                    (turno == 1) ? placar1++ : placar2++;
                }
                break;
            }

            if (tabuleiroCheio(tab)) {
                exibirTabuleiro(tab);
                printf("Empate!\n");
                break;
            }

            turno = 3 - turno; // Alterna entre 1 e 2
        }

        printf("\n== Placar ==\nJogador 1 (X): %d\n%s (O): %d\n",
               placar1, (modo == 2) ? "CPU" : "Jogador 2", placar2);

        printf("Deseja jogar novamente? (S/N): ");
        scanf(" %c", &jogar_novamente);

    } while (toupper(jogar_novamente) == 'S');

    printf("\nFim de jogo. Obrigado!\n");
    return 0;
}
