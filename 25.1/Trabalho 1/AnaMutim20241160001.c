// #################################################
//  Instituto Federal da Bahia
//  Salvador - BA
//  Curso de Análise e Desenvolvimento de Sistemas http://ads.ifba.edu.br
//  Disciplina: INF029 - Laboratório de Programação
//  Professor: Renato Novais - renato@ifba.edu.br

//  ----- Orientações gerais -----
//  Descrição: esse arquivo deve conter as questões do trabalho do aluno.
//  Cada aluno deve renomear esse arquivo para Aluno<MATRICULA>.c
//  O aluno deve preencher seus dados abaixo, e implementar as questões do trabalho

//  ----- Dados do Aluno -----
//  Nome: Ana Emília Lobo e Martfeld Mutim  
//  email: anaemilia@mutim.com.br
//  Matrícula: 20241160001
//  Semestre: 25.1

//  Copyright © 2016 Renato Novais. All rights reserved.
// Última atualização: 07/05/2021 - 19/08/2016

// #################################################

#include <stdio.h>
#include "AnaMutim20241160001.h" // Substitua pelo seu arquivo de header renomeado
#include <stdlib.h>
#include <string.h>

DataQuebrada quebraData(char data[]);

/*
## função utilizada para testes  ##

 somar = somar dois valores
@objetivo
    Somar dois valores x e y e retonar o resultado da soma
@entrada
    dois inteiros x e y
@saida
    resultado da soma (x + y)
 */
int somar(int x, int y)
{
    int soma;
    soma = x + y;
    return soma;
}

/*
## função utilizada para testes  ##

 fatorial = fatorial de um número
@objetivo
    calcular o fatorial de um número
@entrada
    um inteiro x
@saida
    fatorial de x -> x!
 */
int fatorial(int x)
{ //função utilizada para testes
  int i, fat = 1;
    
  for (i = x; i > 1; i--)
    fat = fat * i;
    
  return fat;
}

int teste(int a)
{
    int val;
    if (a == 2)
        val = 3;
    else
        val = 4;

    return val;
}

/*
 Q1 = validar data
@objetivo
    Validar uma data
@entrada
    uma string data. Formatos que devem ser aceitos: dd/mm/aaaa, onde dd = dia, mm = mês, e aaaa, igual ao ano. dd em mm podem ter apenas um digito, e aaaa podem ter apenas dois digitos.
@saida
    0 -> se data inválida
    1 -> se data válida
 @restrições
    Não utilizar funções próprias de string (ex: strtok)   
    pode utilizar strlen para pegar o tamanho da string
 */
int q1(char data[])
{
   DataQuebrada dq = quebraData(data);

    // Se quebraData já invalidou, retorna 0
    if (dq.valido == 0) {
        return 0;
    }
    
    // Checa o tamanho (deve estar entre 6 e 10, como no original)
    int tam = strlen(data); // Usando strlen como permitido na Q1 original
    if (tam < 6 || tam > 10) {
        return 0;
    }

    // Valida Mês (1 a 12)
    if (dq.iMes < 1 || dq.iMes > 12) {
        return 0;
    }

    // Valida Dia (1 a N, onde N é o total de dias no mês)
    int maxDias = diasNoMes(dq.iMes, dq.iAno);
    if (dq.iDia < 1 || dq.iDia > maxDias) {
        return 0;
    }

    return 1; // Data válida
}




/*
 Q2 = diferença entre duas datas
 @objetivo
    Calcular a diferença em anos, meses e dias entre duas datas
 @entrada
    uma string datainicial, uma string datafinal. 
 @saida
    Retorna um tipo DiasMesesAnos. No atributo retorno, deve ter os possíveis valores abaixo
    1 -> cálculo de diferença realizado com sucesso
    2 -> datainicial inválida
    3 -> datafinal inválida
    4 -> datainicial > datafinal
    Caso o cálculo esteja correto, os atributos qtdDias, qtdMeses e qtdAnos devem ser preenchidos com os valores correspondentes.
 */
DiasMesesAnos q2(char datainicial[], char datafinal[])
{
    DiasMesesAnos dma;
    dma.qtdAnos = 0;
    dma.qtdMeses = 0;
    dma.qtdDias = 0;

    // Valida as datas
    if (q1(datainicial) == 0) {
        dma.retorno = 2; // datainicial inválida
        return dma;
    }
    if (q1(datafinal) == 0) {
        dma.retorno = 3; // datafinal inválida
        return dma;
    }

    DataQuebrada inicio = quebraData(datainicial);
    DataQuebrada fim = quebraData(datafinal);

    // Garante que anos com 2 dígitos sejam tratados
    if (inicio.iAno < 100) inicio.iAno += 2000;
    if (fim.iAno < 100) fim.iAno += 2000;

    // Verifica se datainicial > datafinal
    if (fim.iAno < inicio.iAno ||
        (fim.iAno == inicio.iAno && fim.iMes < inicio.iMes) ||
        (fim.iAno == inicio.iAno && fim.iMes == inicio.iMes && fim.iDia < inicio.iDia)) {
        dma.retorno = 4; // datainicial > datafinal
        return dma;
    }

    // Cálculo da diferença (lógica similar à primeira versão)
    int anos = fim.iAno - inicio.iAno;
    int meses = fim.iMes - inicio.iMes;
    int dias = fim.iDia - inicio.iDia;

    if (dias < 0) {
        meses--;
        dias += diasNoMes(inicio.iMes, inicio.iAno); // Usa o mês inicial para o empréstimo
    }

    if (meses < 0) {
        anos--;
        meses += 12;
    }
    
    // O ajuste complexo de bissexto da Q2 original foi simplificado aqui.
    // A lógica anterior era um pouco confusa e talvez incorreta.
    // Esta lógica é a mais comum para cálculo de diferença D/M/A.
    // Se a lógica exata da Q2 original for crucial, ela pode ser reimplementada.

    dma.qtdAnos = anos;
    dma.qtdMeses = meses;
    dma.qtdDias = dias;
    dma.retorno = 1; // Sucesso

    return dma;
}

/*
 Q3 = encontrar caracter em texto
 @objetivo
    Pesquisar quantas vezes um determinado caracter ocorre em um texto
 @entrada
    uma string texto, um caracter c e um inteiro que informa se é uma pesquisa Case Sensitive ou não. Se isCaseSensitive = 1, a pesquisa deve considerar diferenças entre maiúsculos e minúsculos.
        Se isCaseSensitive != 1, a pesquisa não deve  considerar diferenças entre maiúsculos e minúsculos.
 @saida
    Um número n >= 0.
 */
int q3(char *texto, char c, int isCaseSensitive)
{
    int contador = 0;
    char charTexto, charBusca;

    for (int i = 0; texto[i] != '\0'; i++) {
        charTexto = texto[i];
        charBusca = c;

        // Se não for Case Sensitive, converte tudo para minúsculo
        if (isCaseSensitive != 1) {
            charTexto = paraMinusculo(charTexto);
            charBusca = paraMinusculo(charBusca);
        }

        if (charTexto == charBusca) {
            contador++;
        }
    }

    return contador;
}


/*
 Q4 = encontrar palavra em texto
 @objetivo
    Pesquisar todas as ocorrências de uma palavra em um texto
 @entrada
    uma string texto base (strTexto), uma string strBusca e um vetor de inteiros (posicoes) que irá guardar as posições de início e fim de cada ocorrência da palavra (strBusca) no texto base (texto).
 @saida
    Um número n >= 0 correspondente a quantidade de ocorrências encontradas.
    O vetor posicoes deve ser preenchido com cada entrada e saída correspondente. Por exemplo, se tiver uma única ocorrência, a posição 0 do vetor deve ser preenchido com o índice de início do texto, e na posição 1, deve ser preenchido com o índice de fim da ocorrencias. Se tiver duas ocorrências, a segunda ocorrência será amazenado nas posições 2 e 3, e assim consecutivamente. Suponha a string "Instituto Federal da Bahia", e palavra de busca "dera". Como há uma ocorrência da palavra de busca no texto, deve-se armazenar no vetor, da seguinte forma:
        posicoes[0] = 13;
        posicoes[1] = 16;
        Observe que o índice da posição no texto deve começar ser contado a partir de 1.
        O retorno da função, n, nesse caso seria 1;

 */


int q4(char *strTexto, char *strBusca, int posicoes[30]){
    int qtdOcorrencias = 0;
    int posicao = 0;
    int len = strlen(strBusca);
    naoEspeciais(strTexto);
    naoEspeciais(strBusca);

    for(int i = 0; i<strlen(strTexto);){
      int achou = 0;
      if(strTexto[i]==strBusca[0]){
        achou=1;
        for(int j=i, k=0; k<len; j++,k++){
          if(strBusca[k]!=strTexto[j])achou=0;
        }
        if(achou){
          qtdOcorrencias++;
          posicoes[posicao] = i+1;
          posicao++;
          posicoes[posicao] = i+len;
          posicao++;

          i += len;
        }else{
          i++;
        }
      }
      if(!achou)i++;
    }

    return qtdOcorrencias;
}

/*
 Q5 = inverte número
 @objetivo
    Inverter número inteiro
 @entrada
    uma int num.
 @saida
    Número invertido
 */

/*
 Q5 = inverte número
 @objetivo
    Inverter número inteiro
 @entrada
    uma int num.
 @saida
    Número invertido
 */

int q5(int num){

    int invert = 0;

    while (num != 0){
        invert = invert * 10 + num % 10;
        num /= 10;
    }

    num = invert;

    return num;
}
/*
 Q6 = ocorrência de um número em outro
 @objetivo
    Verificar quantidade de vezes da ocorrência de um número em outro
 @entrada
    Um número base (numerobase) e um número de busca (numerobusca).
 @saida
    Quantidade de vezes que número de busca ocorre em número base
 */


int q6(int numerobase, int numerobusca)
{
    int qtdOcorrencias = 0;
    char strBase[50];
    char strBusca[50];

    sprintf(strBase, "%d", numerobase);
    sprintf(strBusca, "%d", numerobusca);

    int tamBase = strlen(strBase);
    int tamBusca = strlen(strBusca);

    if (tamBusca == 0) return 0;

    for (int i = 0; i <= tamBase - tamBusca; i++) {
        if (strncmp(&strBase[i], strBusca, tamBusca) == 0) {
            qtdOcorrencias++;
        }
    }

    return qtdOcorrencias;
}




/*
 Q7 = jogo busca palavras
 @objetivo
    Verificar se existe uma string em uma matriz de caracteres em todas as direções e sentidos possíves
 @entrada
    Uma matriz de caracteres e uma string de busca (palavra).
 @saida
    1 se achou 0 se não achou
 */

     int q7(char matriz[8][10], char palavra[]){ 
    // Vetor com as 8 direções: H+, H-, V+, V-, D1+, D1-, D2+, D2-
    int direcoes[8][2] = {
        {0, 1}, {0, -1}, {1, 0}, {-1, 0}, 
        {1, 1}, {1, -1}, {-1, -1}, {-1, 1}
    };

    // Percorre cada célula da matriz como ponto inicial
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 10; j++) {
            // Tenta buscar a palavra em todas as 8 direções a partir desta célula
            for (int d = 0; d < 8; d++) {
                if (procurarDirecao(matriz, i, j, palavra, direcoes[d][0], direcoes[d][1])) {
                    return 1; // Achou!
                }
            }
        }
    }

    return 0; // Não achou em lugar nenhum
}




DataQuebrada quebraData(char data[]){
  DataQuebrada dq;
  char sDia[3];
	char sMes[3];
	char sAno[5];
	int i; 

	for (i = 0; data[i] != '/'; i++){
		sDia[i] = data[i];	
	}
	if(i == 1 || i == 2){ // testa se tem 1 ou dois digitos
		sDia[i] = '\0';  // coloca o barra zero no final
	}else {
		dq.valido = 0;
    return dq;
  }  
	

	int j = i + 1; //anda 1 cada para pular a barra
	i = 0;

	for (; data[j] != '/'; j++){
		sMes[i] = data[j];
		i++;
	}

	if(i == 1 || i == 2){ // testa se tem 1 ou dois digitos
		sMes[i] = '\0';  // coloca o barra zero no final
	}else {
		dq.valido = 0;
    return dq;
  }
	

	j = j + 1; //anda 1 cada para pular a barra
	i = 0;
	
	for(; data[j] != '\0'; j++){
	 	sAno[i] = data[j];
	 	i++;
	}

	if(i == 2 || i == 4){ // testa se tem 2 ou 4 digitos
		sAno[i] = '\0';  // coloca o barra zero no final
	}else {
		dq.valido = 0;
    return dq;
  }

  dq.iDia = atoi(sDia);
  dq.iMes = atoi(sMes);
  dq.iAno = atoi(sAno); 

	dq.valido = 1;
    
  return dq;
}