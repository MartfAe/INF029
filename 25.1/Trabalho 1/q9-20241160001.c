#include <stdio.h>
#include <stdlib.h> 
#include <time.h>   
#include <ctype.h> // Adicionado para toupper

#define LADO_GRADE 10 
#define MAX_FROTA 10  

typedef struct {
    int comprimento; 
    int resistencia; 
} Embarcacao;

typedef struct {
    char grade[LADO_GRADE][LADO_GRADE]; 
    Embarcacao frota[MAX_FROTA];        
    int num_embarcacoes;               
} Participante;

const int QTD_EMBARCACOES = 6;
const int COMPRIMENTOS_EMBARCACOES[MAX_FROTA] = {4, 3, 1, 1, 1, 2};

void preparar_participante(Participante *p);
void exibir_grade(Participante *p, int revelar_frota);
int alocar_embarcacao(Participante *p, int indice, int l, int c, char orientacao);
int disparar(Participante *adversario, int l, int c);
int frota_restante(Participante *p);
void alocar_frota_completa(Participante *p, int id_jogador);
void iniciar_jogo(Participante *p1, Participante *p2);


void preparar_participante(Participante *p) {
    p->num_embarcacoes = QTD_EMBARCACOES;
    for (int i = 0; i < LADO_GRADE; i++) {
        for (int j = 0; j < LADO_GRADE; j++) {
            p->grade[i][j] = '~'; 
        }
    }
    for (int i = 0; i < QTD_EMBARCACOES; i++) {
        p->frota[i].comprimento = COMPRIMENTOS_EMBARCACOES[i];
        p->frota[i].resistencia = COMPRIMENTOS_EMBARCACOES[i];
    }
}


void exibir_grade(Participante *p, int revelar_frota) {
    printf("\n    ");
    for (int i = 0; i < LADO_GRADE; i++) printf("%2d ", i);
    printf("\n  +-------------------------------+\n");
    for (int i = 0; i < LADO_GRADE; i++) {
        printf("%2d|", i);
        for (int j = 0; j < LADO_GRADE; j++) {
            char simbolo = p->grade[i][j];
            if (!revelar_frota && simbolo == 'E') {
                simbolo = '~';
            }
            printf(" %c ", simbolo);
        }
        printf("|\n");
    }
    printf("  +-------------------------------+\n");
}


int alocar_embarcacao(Participante *p, int indice, int l, int c, char orientacao) {
    int comp = p->frota[indice].comprimento;
    orientacao = toupper(orientacao); 

    for (int i = 0; i < comp; i++) {
        int nl = l + (orientacao == 'V' ? i : 0);
        int nc = c + (orientacao == 'H' ? i : 0);
        if (nl >= LADO_GRADE || nc >= LADO_GRADE || p->grade[nl][nc] != '~') {
            printf(">> Erro: Posicao invalida ou sobreposta!\n");
            return 0; 
        }
    }
    for (int i = 0; i < comp; i++) {
        int nl = l + (orientacao == 'V' ? i : 0);
        int nc = c + (orientacao == 'H' ? i : 0);
        p->grade[nl][nc] = 'E'; 
    }
    return 1; 
}


int disparar(Participante *adversario, int l, int c) {
    if (l < 0 || l >= LADO_GRADE || c < 0 || c >= LADO_GRADE) return -1; 

    char *local_alvo = &adversario->grade[l][c];

    if (*local_alvo == 'E') { 
        *local_alvo = 'A'; 
        for (int i = 0; i < adversario->num_embarcacoes; i++) {
            if (adversario->frota[i].resistencia > 0) {
                adversario->frota[i].resistencia--;
                break;
            }
        }
        return 1; 
    } else if (*local_alvo == '~') { 
        *local_alvo = 'X'; 
        return 0; 
    }
    
    return -1; 
}


int frota_restante(Participante *p) {
    int ativas = 0;
    for (int i = 0; i < p->num_embarcacoes; i++) {
        if (p->frota[i].resistencia > 0) {
            ativas++;
        }
    }
    return ativas;
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
            scanf("%d %d %c", &l_in, &c_in, &o_in);
            // Limpa o buffer de entrada para evitar problemas com leituras futuras
            while(getchar() != '\n'); 
        } while (!alocar_embarcacao(p, i, l_in, c_in, o_in));
    }
    printf("\n--- Frota do Jogador %d alocada! ---\n", id_jogador);
}


void iniciar_jogo(Participante *p1, Participante *p2) {
    int rodada = 0;
    while (frota_restante(p1) > 0 && frota_restante(p2) > 0) {
        Participante *jogador_vez = (rodada % 2 == 0) ? p1 : p2;
        Participante *jogador_alvo = (rodada % 2 == 0) ? p2 : p1;
        int id_vez = (rodada % 2 == 0) ? 1 : 2;
        int escolha_menu;
        int efetuou_disparo = 0;

        printf("\n<<<<< TURNO DO JOGADOR %d >>>>>\n", id_vez);
        
        while (!efetuou_disparo) {
            printf("\nOpcoes:\n");
            printf("  1. Ver Minha Grade\n");
            printf("  2. Ver Grade do Oponente (Tiros)\n");
            printf("  3. Atirar!\n");
            printf("  4. Desistir\n");
            printf("Escolha uma acao: ");
            scanf("%d", &escolha_menu);
            while(getchar() != '\n'); // Limpa o buffer

            switch (escolha_menu) {
                case 1:
                    printf("\n--- Sua Grade ---\n");
                    exibir_grade(jogador_vez, 1);
                    break;
                case 2:
                    printf("\n--- Grade do Oponente ---\n");
                    exibir_grade(jogador_alvo, 0); 
                    break;
                case 3: {
                    int l_tiro, c_tiro, resultado_tiro;
                    printf("Informe a Linha e a Coluna para o disparo: ");
                    scanf("%d %d", &l_tiro, &c_tiro);
                    while(getchar() != '\n'); // Limpa o buffer
                    resultado_tiro = disparar(jogador_alvo, l_tiro, c_tiro);
                    
                    if (resultado_tiro == 1) printf(">> FOGO! Voce acertou uma embarcacao!\n");
                    else if (resultado_tiro == 0) printf(">> SPLASH! Tiro na agua.\n");
                    else printf(">> ERRO! Coordenada invalida ou ja atingida.\n");
                    
                    if (resultado_tiro != -1) efetuou_disparo = 1; 
                    break;
                }
                case 4:
                    printf("Jogo encerrado por desistencia.\n");
                    for(int i = 0; i < jogador_vez->num_embarcacoes; i++) jogador_vez->frota[i].resistencia = 0;
                    efetuou_disparo = 1; 
                    break;
                default:
                    printf("Opcao nao reconhecida!\n");
                    break;
            }
        } 

        if (frota_restante(jogador_vez) == 0 && escolha_menu == 4) break;

        rodada++; 
    } 

    if (frota_restante(p1) == 0)
        printf("\n*** VITORIA DO JOGADOR 2! Frota inimiga destruida! ***\n");
    else
        printf("\n*** VITORIA DO JOGADOR 1! Frota inimiga destruida! ***\n");
}

int main() {
    Participante jogador1, jogador2; 

    preparar_participante(&jogador1);
    preparar_participante(&jogador2);

    alocar_frota_completa(&jogador1, 1);
    alocar_frota_completa(&jogador2, 2);

    iniciar_jogo(&jogador1, &jogador2);

    return 0;
}