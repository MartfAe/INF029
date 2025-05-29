#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

#define DIMENSAO 3 

void mostrarGrade(char grade[DIMENSAO][DIMENSAO]);
int checarGanhador(char grade[DIMENSAO][DIMENSAO], char simbolo);
int gradeCheia(char grade[DIMENSAO][DIMENSAO]);
int validarEntrada(char entrada[3]);
void iniciarJogo(char grade[DIMENSAO][DIMENSAO]);
int jogadaPossivel(char grade[DIMENSAO][DIMENSAO], int l, int c);
void cpuJoga(char grade[DIMENSAO][DIMENSAO], char simbolo, int nivel);
int tentarJogadaEstrategica(char grade[DIMENSAO][DIMENSAO], char simbolo, int *l_ptr, int *c_ptr);


void mostrarGrade(char grade[DIMENSAO][DIMENSAO]) {
    printf("\n    1   2   3\n");
    printf("   -----------\n");
    for (int linha = 0; linha < DIMENSAO; linha++) {
        printf("%c |", 'A' + linha);
        for (int coluna = 0; coluna < DIMENSAO; coluna++) {
            printf(" %c |", grade[linha][coluna]);
        }
        printf("\n   -----------\n");
    }
    printf("\n");
}


int checarGanhador(char grade[DIMENSAO][DIMENSAO], char simbolo) {
    // Verifica linhas
    for (int l = 0; l < DIMENSAO; l++) {
        if (grade[l][0] == simbolo && grade[l][1] == simbolo && grade[l][2] == simbolo) return 1;
    }
    // Verifica colunas
    for (int c = 0; c < DIMENSAO; c++) {
        if (grade[0][c] == simbolo && grade[1][c] == simbolo && grade[2][c] == simbolo) return 1;
    }
    // Verifica diagonais
    if (grade[0][0] == simbolo && grade[1][1] == simbolo && grade[2][2] == simbolo) return 1;
    if (grade[0][2] == simbolo && grade[1][1] == simbolo && grade[2][0] == simbolo) return 1;

    return 0; // Ninguém ganhou
}


int gradeCheia(char grade[DIMENSAO][DIMENSAO]) {
    for (int l = 0; l < DIMENSAO; l++) {
        for (int c = 0; c < DIMENSAO; c++) {
            if (grade[l][c] == ' ') return 0; // Encontrou espaço vazio
        }
    }
    return 1; // Grade está cheia
}


int validarEntrada(char entrada[3]) {
    char l = toupper(entrada[0]);
    char c = entrada[1];
    return (l >= 'A' && l <= 'C' && c >= '1' && c <= '3' && entrada[2] == '\0');
}


void iniciarJogo(char grade[DIMENSAO][DIMENSAO]) {
    for (int l = 0; l < DIMENSAO; l++) {
        for (int c = 0; c < DIMENSAO; c++) {
            grade[l][c] = ' ';
        }
    }
}


int jogadaPossivel(char grade[DIMENSAO][DIMENSAO], int l, int c) {
    return (l >= 0 && l < DIMENSAO && c >= 0 && c < DIMENSAO && grade[l][c] == ' ');
}


int tentarJogadaEstrategica(char grade[DIMENSAO][DIMENSAO], char simbolo, int *l_ptr, int *c_ptr) {
    char adversario = (simbolo == 'O') ? 'X' : 'O';

    // 1. Tentar ganhar
    for (int l = 0; l < DIMENSAO; l++) {
        for (int c = 0; c < DIMENSAO; c++) {
            if (grade[l][c] == ' ') {
                grade[l][c] = simbolo; // Testa a jogada
                if (checarGanhador(grade, simbolo)) {
                    *l_ptr = l; *c_ptr = c;
                    grade[l][c] = ' '; // Desfaz
                    return 1;
                }
                grade[l][c] = ' '; // Desfaz
            }
        }
    }

    // 2. Tentar bloquear
    for (int l = 0; l < DIMENSAO; l++) {
        for (int c = 0; c < DIMENSAO; c++) {
            if (grade[l][c] == ' ') {
                grade[l][c] = adversario; // Testa jogada do oponente
                if (checarGanhador(grade, adversario)) {
                    *l_ptr = l; *c_ptr = c;
                    grade[l][c] = ' '; // Desfaz
                    return 1;
                }
                grade[l][c] = ' '; // Desfaz
            }
        }
    }
    return 0; // Nenhuma jogada estratégica encontrada
}


void cpuJoga(char grade[DIMENSAO][DIMENSAO], char simbolo, int nivel) {
    int l_jogada, c_jogada;

    // Se nível difícil e encontrou jogada estratégica, joga nela
    if (nivel == 2 && tentarJogadaEstrategica(grade, simbolo, &l_jogada, &c_jogada)) {
        grade[l_jogada][c_jogada] = simbolo;
    } else {
        // Senão, joga aleatoriamente
        do {
            l_jogada = rand() % DIMENSAO;
            c_jogada = rand() % DIMENSAO;
        } while (!jogadaPossivel(grade, l_jogada, c_jogada));
        grade[l_jogada][c_jogada] = simbolo;
    }
}

int main() {
    char grade_atual[DIMENSAO][DIMENSAO];
    char entrada_usuario[4]; // Espaço para A1 e \0
    char continuar_jogo;
    int tipo_partida, nivel_cpu = 1;
    int placar_j1 = 0, placar_j2 = 0;
    int turno_jogador;
    char simbolo_jogador;

    srand(time(NULL)); // Inicializa gerador aleatório

    printf("Bem-vindo ao Jogo da Velha!\n");
    printf("Escolha o modo:\n");
    printf("  1 - Humano vs Humano\n");
    printf("  2 - Humano vs Computador\n");
    printf("Opcao: ");
    scanf("%d", &tipo_partida);

    if (tipo_partida == 2) {
        printf("Escolha a dificuldade da CPU:\n");
        printf("  1 - Facil\n");
        printf("  2 - Dificil\n");
        printf("Opcao: ");
        scanf("%d", &nivel_cpu);
    }

    do {
        iniciarJogo(grade_atual);
        turno_jogador = 1; // Jogador 1 (X) começa
        int jogo_em_andamento = 1;

        while (jogo_em_andamento) {
            mostrarGrade(grade_atual);
            simbolo_jogador = (turno_jogador == 1) ? 'X' : 'O';

            if (tipo_partida == 2 && turno_jogador == 2) {
                printf("Vez do Computador (%c)...\n", simbolo_jogador);
                cpuJoga(grade_atual, simbolo_jogador, nivel_cpu);
            } else {
                printf("Vez do Jogador %d (%c). Digite a posicao (ex: A1): ", turno_jogador, simbolo_jogador);
                
                int jogada_ok = 0;
                while(!jogada_ok) {
                    scanf("%3s", entrada_usuario); // Lê até 3 chars para pegar A1 + ENTER
                    entrada_usuario[2] = '\0'; // Garante terminação para validar

                    if (!validarEntrada(entrada_usuario)) {
                        printf("Entrada invalida! Use A1, B2, C3, etc. Tente novamente: ");
                        continue;
                    }

                    int l = toupper(entrada_usuario[0]) - 'A';
                    int c = entrada_usuario[1] - '1';

                    if (!jogadaPossivel(grade_atual, l, c)) {
                        printf("Posicao ocupada ou invalida! Tente novamente: ");
                        continue;
                    }

                    grade_atual[l][c] = simbolo_jogador;
                    jogada_ok = 1;
                }
            }

            // Verifica estado do jogo após a jogada
            if (checarGanhador(grade_atual, simbolo_jogador)) {
                mostrarGrade(grade_atual);
                if (tipo_partida == 2 && turno_jogador == 2) {
                    printf("O Computador (%c) venceu!\n", simbolo_jogador);
                    placar_j2++;
                } else {
                    printf("O Jogador %d (%c) venceu!\n", turno_jogador, simbolo_jogador);
                    (turno_jogador == 1) ? placar_j1++ : placar_j2++;
                }
                jogo_em_andamento = 0; // Termina o loop
            } else if (gradeCheia(grade_atual)) {
                mostrarGrade(grade_atual);
                printf("Deu Velha! Empate!\n");
                jogo_em_andamento = 0; // Termina o loop
            } else {
                // Passa a vez
                turno_jogador = (turno_jogador == 1) ? 2 : 1;
            }
        } // Fim do while (jogo_em_andamento)

        printf("\n--- Placar ---\n");
        printf("Jogador 1 (X): %d\n", placar_j1);
        printf("%s (O): %d\n", (tipo_partida == 2) ? "Computador" : "Jogador 2", placar_j2);
        printf("--------------\n");

        printf("Jogar mais uma partida? (S/N): ");
        scanf(" %c", &continuar_jogo); // Espaço antes de %c para consumir newlines

    } while (toupper(continuar_jogo) == 'S'); // Fim do do-while (jogar_novamente)

    printf("\nObrigado por jogar!\n");
    return 0;
}