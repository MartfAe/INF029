#include <stdio.h>
#include <stdlib.h>
#include <ctype.h> // Para toupper

// --- Constantes Globais ---
#define LADO_GRADE 10
#define MAX_FROTA 10
#define QTD_EMBARCACOES 6

// Define os comprimentos da frota padrão
const int COMPRIMENTOS_EMBARCACOES[QTD_EMBARCACOES] = {4, 3, 3, 2, 2, 1};

// --- Tipos e Estruturas de Dados ---

// Enum para tornar o código mais legível, substituindo 'caracteres mágicos'
typedef enum {
    AGUA = '~',
    ACERTO = 'A',
    ERRO = 'X'
} EstadoCelula;

// Enum para os resultados possíveis de um disparo
typedef enum {
    DISPARO_INVALIDO = -1,
    DISPARO_NA_AGUA = 0,
    DISPARO_COM_SUCESSO = 1
} ResultadoDisparo;

typedef struct {
    int comprimento;
    int resistencia; // Quantas partes ainda não foram atingidas
} Embarcacao;

typedef struct {
    char grade[LADO_GRADE][LADO_GRADE];
    Embarcacao frota[MAX_FROTA];
    int num_embarcacoes;
    int navios_afundados; // Contador para verificar a condição de vitória de forma eficiente
} Participante;

// --- Protótipos das Funções ---
void preparar_participante(Participante *p);
void exibir_grade(const Participante *p, int revelar_navios);
int alocar_embarcacao(Participante *p, int indice_frota, int linha, int coluna, char orientacao);
void alocar_frota_completa(Participante *p, int id_jogador);
ResultadoDisparo disparar(Participante *adversario, int linha, int coluna);
int todos_navios_afundados(const Participante *p);
void executar_turno(Participante *jogador_vez, Participante *jogador_alvo, int id_jogador);
void iniciar_jogo(Participante *p1, Participante *p2);

// --- Função Principal ---
int main() {
    Participante jogador1, jogador2;

    printf("Batalha Naval - Preparacao\n");

    preparar_participante(&jogador1);
    preparar_participante(&jogador2);

    alocar_frota_completa(&jogador1, 1);
    alocar_frota_completa(&jogador2, 2);

    iniciar_jogo(&jogador1, &jogador2);

    return 0;
}

void preparar_participante(Participante *p) {
    p->num_embarcacoes = QTD_EMBARCACOES;
    p->navios_afundados = 0;

    for (int i = 0; i < LADO_GRADE; i++) {
        for (int j = 0; j < LADO_GRADE; j++) {
            p->grade[i][j] = AGUA;
        }
    }

    for (int i = 0; i < p->num_embarcacoes; i++) {
        p->frota[i].comprimento = COMPRIMENTOS_EMBARCACOES[i];
        p->frota[i].resistencia = COMPRIMENTOS_EMBARCACOES[i];
    }
}

void exibir_grade(const Participante *p, int revelar_navios) {
    printf("\n    ");
    for (int i = 0; i < LADO_GRADE; i++) printf("%2d ", i);
    printf("\n  +------------------------------+\n");

    for (int i = 0; i < LADO_GRADE; i++) {
        printf("%2d|", i);
        for (int j = 0; j < LADO_GRADE; j++) {
            char simbolo = p->grade[i][j];
            // Se não for para revelar e a célula contém um navio (indicado por um dígito)
            if (!revelar_navios && isdigit(simbolo)) {
                simbolo = AGUA;
            }
            printf(" %c ", simbolo);
        }
        printf("|\n");
    }
    printf("  +------------------------------+\n");
}

int alocar_embarcacao(Participante *p, int indice_frota, int linha, int coluna, char orientacao) {
    int comp = p->frota[indice_frota].comprimento;
    orientacao = toupper(orientacao);

    if (orientacao != 'H' && orientacao != 'V') return 0; // Orientação inválida

    // 1. Verifica se a embarcação cabe na grade e não sobrepõe outra
    for (int i = 0; i < comp; i++) {
        int l = linha + (orientacao == 'V' ? i : 0);
        int c = coluna + (orientacao == 'H' ? i : 0);

        if (l >= LADO_GRADE || c >= LADO_GRADE || p->grade[l][c] != AGUA) {
            printf(">> Erro: Posicao invalida ou sobreposta!\n");
            return 0; // Fora da grade ou já ocupado
        }
    }

    // 2. Se a verificação passou, aloca a embarcação
    for (int i = 0; i < comp; i++) {
        int l = linha + (orientacao == 'V' ? i : 0);
        int c = coluna + (orientacao == 'H' ? i : 0);
        p->grade[l][c] = '0' + indice_frota; // Armazena o índice do navio como char
    }
    return 1;
}

void alocar_frota_completa(Participante *p, int id_jogador) {
    printf("\n========= ALOCACAO: JOGADOR %d =========\n", id_jogador);
    for (int i = 0; i < p->num_embarcacoes; i++) {
        int l_in, c_in;
        char o_in;

        exibir_grade(p, 1);
        printf("Alocar Embarcacao %d (Comprimento %d):\n", i + 1, p->frota[i].comprimento);

        do {
            printf("Digite Linha, Coluna e Orientacao (H/V): ");
            // Valida o formato da entrada para evitar loops infinitos
            if (scanf("%d %d %c", &l_in, &c_in, &o_in) != 3) {
                 printf(">> Entrada invalida. Tente novamente.\n");
                 while(getchar() != '\n'); // Limpa buffer de entrada
                 continue;
            }
            while(getchar() != '\n'); // Limpa o restante do buffer

        } while (!alocar_embarcacao(p, i, l_in, c_in, o_in));
    }
    printf("\n--- Frota do Jogador %d alocada! ---\n", id_jogador);
    // system("clear || cls"); // Opcional: limpa a tela entre as alocações
}

ResultadoDisparo disparar(Participante *adversario, int linha, int coluna) {
    if (linha < 0 || linha >= LADO_GRADE || coluna < 0 || coluna >= LADO_GRADE) {
        return DISPARO_INVALIDO;
    }

    char *celula_alvo = &adversario->grade[linha][coluna];

    if (isdigit(*celula_alvo)) { // Acertou uma embarcação que não tinha sido atingida antes
        int indice_navio = *celula_alvo - '0'; // Converte char '0'..'9' para int 0..9
        *celula_alvo = ACERTO;
        adversario->frota[indice_navio].resistencia--;

        if (adversario->frota[indice_navio].resistencia == 0) {
            printf(">> NAVIO AFUNDADO!!!\n");
            adversario->navios_afundados++;
        }
        return DISPARO_COM_SUCESSO;

    } else if (*celula_alvo == AGUA) { // Acertou a água
        *celula_alvo = ERRO;
        return DISPARO_NA_AGUA;
    }

    // A célula já foi atingida antes (ACERTO ou ERRO)
    return DISPARO_INVALIDO;
}

int todos_navios_afundados(const Participante *p) {
    return p->navios_afundados == p->num_embarcacoes;
}

void iniciar_jogo(Participante *p1, Participante *p2) {
    int rodada = 0;
    Participante *jogador_vez, *jogador_alvo;

    while (!todos_navios_afundados(p1) && !todos_navios_afundados(p2)) {
        if (rodada % 2 == 0) {
            jogador_vez = p1;
            jogador_alvo = p2;
            executar_turno(jogador_vez, jogador_alvo, 1);
        } else {
            jogador_vez = p2;
            jogador_alvo = p1;
            executar_turno(jogador_vez, jogador_alvo, 2);
        }
        rodada++;
    }

    // Anuncia o vencedor
    printf("\n======= FIM DE JOGO =======\n");
    if (todos_navios_afundados(p2)) {
        printf("*** VITORIA DO JOGADOR 1! Frota inimiga destruida! ***\n");
        printf("Sua grade final:\n");
        exibir_grade(p1, 1);
    } else {
        printf("*** VITORIA DO JOGADOR 2! Frota inimiga destruida! ***\n");
        printf("Sua grade final:\n");
        exibir_grade(p2, 1);
    }
}

void executar_turno(Participante *jogador_vez, Participante *jogador_alvo, int id_jogador) {
    int escolha_menu;
    int disparo_efetuado = 0;

    printf("\n<<<<< TURNO DO JOGADOR %d >>>>>\n", id_jogador);

    while (!disparo_efetuado) {
        printf("\nOpcoes:\n");
        printf("  1. Ver Minha Grade\n");
        printf("  2. Ver Grade do Oponente (Tiros)\n");
        printf("  3. Atirar!\n");
        printf("  4. Desistir\n");
        printf("Escolha uma acao: ");

        if (scanf("%d", &escolha_menu) != 1) {
            escolha_menu = -1; // Força erro no switch
        }
        while (getchar() != '\n'); // Limpa buffer

        switch (escolha_menu) {
            case 1:
                printf("\n--- Sua Grade ---\n");
                exibir_grade(jogador_vez, 1);
                break;
            case 2:
                printf("\n--- Grade do Oponente ---\n");
                exibir_grade(jogador_alvo, 0); // 0 para esconder navios
                break;
            case 3: {
                int l_tiro, c_tiro;
                printf("Informe a Linha e a Coluna para o disparo: ");
                scanf("%d %d", &l_tiro, &c_tiro);
                while (getchar() != '\n');

                ResultadoDisparo resultado = disparar(jogador_alvo, l_tiro, c_tiro);

                if (resultado == DISPARO_COM_SUCESSO) printf(">> FOGO! Voce acertou uma embarcacao!\n");
                else if (resultado == DISPARO_NA_AGUA) printf(">> SPLASH! Tiro na agua.\n");
                else printf(">> ERRO! Coordenada invalida ou ja atingida.\n");

                if (resultado != DISPARO_INVALIDO) {
                    disparo_efetuado = 1;
                }
                break;
            }
            case 4:
                printf("Jogador %d desistiu. Fim de jogo.\n", id_jogador);
                // Define a vida de todas as embarcações como 0 para forçar a derrota
                for(int i=0; i < jogador_vez->num_embarcacoes; i++) jogador_vez->frota[i].resistencia = 0;
                jogador_vez->navios_afundados = jogador_vez->num_embarcacoes;
                disparo_efetuado = 1;
                break;
            default:
                printf("Opcao nao reconhecida!\n");
                break;
        }
    }
}