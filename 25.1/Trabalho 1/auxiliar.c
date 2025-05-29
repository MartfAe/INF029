
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "AnaMutim20241160001.h"


//Função para verificar se o ano é bissexto
int bissexto(int ano){
    //Checa se o aaaa tem 2 caracteres e insere +2000 anos, como sugerido
    if (ano < 100){
        ano += 2000;
    }
    
	if ((ano % 4 == 0 && ano % 100 != 0) || ano % 400 == 0){
		return 1;
	}

	return 0;
}

//Usada na Q1 e Q2, cria um array para dizer quais os dias em cada mês
int diasNoMes(int mes, int ano) {
    int diasPorMes[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    
    // if fevereiro, checa bissexto
    if (mes == 2) {
        if (bissexto(ano)) {
             // Fevereiro = 29 no bissexto
            return 29;
        }
    }
    return diasPorMes[mes - 1];
}

//Função usada na Q3 para converter maiúsculos para minúsculos
int paraMinusculo(char ch) {
    if (ch >= 'A' && ch <= 'Z') {
        return ch + ('a' - 'A');
    }
    return ch;
}

int calcularTamanho(char palavra[]) {
    int tamanho = 0;
    while (palavra[tamanho] != '\0') {
        tamanho++;
    }
    return tamanho;
}

int procurarDirecao(char matriz[8][10], int linha, int coluna, char palavra[], int dx, int dy) {
    int tamanho = calcularTamanho(palavra);

    for (int i = 0; i < tamanho; i++) {
        int novaLinha = linha + i * dx;
        int novaColuna = coluna + i * dy;

        // Verifica limites da matriz
        if (novaLinha < 0 || novaLinha >= 8 || novaColuna < 0 || novaColuna >= 10)
            return 0;

        // Verifica caractere da matriz com a letra da palavra
        if (matriz[novaLinha][novaColuna] != palavra[i])
            return 0;
    }

    return 1; // Palavra encontrada nessa direção
}

void naoEspeciais(char *text){
  int i, j=0;

  const char *comAcentos[] = {"Ä", "Å", "Á", "Â", "À", "Ã", "ä", "á", "â", "à", "ã",
                                "É", "Ê", "Ë", "È", "é", "ê", "ë", "è",
                                "Í", "Î", "Ï", "Ì", "í", "î", "ï", "ì",
                                "Ö", "Ó", "Ô", "Ò", "Õ", "ö", "ó", "ô", "ò", "õ",
                                "Ü", "Ú", "Û", "ü", "ú", "û", "ù",
                                "Ç", "ç"};
                                
  const char *semAcentos[] = {"A", "A", "A", "A", "A", "A", "a", "a", "a", "a", "a",
                              "E", "E", "E", "E", "e", "e", "e", "e",
                              "I", "I", "I", "I", "i", "i", "i", "i",
                              "O", "O", "O", "O", "O", "o", "o", "o", "o", "o",
                              "U", "U", "U", "u", "u", "u", "u",
                              "C", "c"};

  char buffer[256];
  buffer[0] = '\0';

  for (int i = 0; i < strlen(text);) {
    int found = 0;
    for (int j = 0; j < sizeof(comAcentos) / sizeof(comAcentos[0]); j++) {
      int len = strlen(comAcentos[j]);

      if (strncmp(&text[i], comAcentos[j], len) == 0) {
        strcat(buffer, semAcentos[j]);
        i += len;
        found = 1;
        break;
      }
    }
    if (!found) {
      strncat(buffer, &text[i], 1);
      i++;
    }
  }
  strcpy(text, buffer);
}