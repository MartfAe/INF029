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
//  Nome: Ana Emília Lobo E Martfeld Mutim
//  email: anaemilia@mutim.com.br   
//  Matrícula: 20241160001  
//  Semestre: 2024.2

//  Copyright © 2016 Renato Novais. All rights reserved.
// Última atualização: 07/05/2021 - 19/08/2016

// #################################################

#include <stdio.h>
#include "AnaMutim20241160001.h" // Substitua pelo seu arquivo de header renomeado
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

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
  int datavalida = 0;

  //quebrar a string data em strings sDia, sMes, sAno
  DataQuebrada dataq;  // Variavel para armazenar os dados quebrados
  if(strlen(data)<=10){ //Verifica o tamanho máximo
    dataq = quebraData(data);
    
    if(dataq.valido == 1 && (dataq.iMes>=1 && dataq.iMes<=12)){ //Verifica se a data é válida
      dataq.iAno += (dataq.iAno<100)*2000; //Converte o ano para o formato de 4 digitos
      int bissexto = (dataq.iAno%4 ==0 &&(dataq.iAno %100 !=0 || dataq.iAno %400 ==0));
      
      if(dataq.iDia>=1 && dataq.iDia<=31){
        
        if(dataq.iMes ==4 || dataq.iMes ==6 || dataq.iMes ==9 || dataq.iMes ==11){
          if(dataq.iDia<=30){
            datavalida = 1;
          }
      }
      else if((dataq.iMes == 1 || dataq.iMes == 3 || dataq.iMes ==5 || dataq.iMes ==7 || dataq.iMes ==8 || dataq.iMes == 10 || dataq.iMes ==12)){
          datavalida = 1;
      }
      else if(dataq.iMes == 2){
        if(bissexto && dataq.iDia<=29){
          datavalida = 1;
        }
        else if(dataq.iDia<=28){
          datavalida = 1;
        }
      }
    
     }
   }
  }

  //printf("%s\n", data);

  if (datavalida)
      return 1;
  else
      return 0;
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
DiasMesesAnos q2(char datainicial[], char datafinal[]) {
    // Variável de retorno
    DiasMesesAnos dma;

    // Validando datas iniciais e finais
    if (q1(datainicial) == 0) {
        dma.retorno = 2;  // Data inicial inválida
        return dma;
    } else if (q1(datafinal) == 0) {
        dma.retorno = 3;  // Data final inválida
        return dma;
    } else {
        // Quebrando as datas em dia, mês e ano
        DataQuebrada DataFinalQuebrada, DataInicialQuebrada;
        DataInicialQuebrada = quebraData(datainicial);
        DataFinalQuebrada = quebraData(datafinal);

        // Verificando se a data final é menor que a inicial
        if (DataFinalQuebrada.iAno < DataInicialQuebrada.iAno ||
            (DataFinalQuebrada.iAno == DataInicialQuebrada.iAno && DataFinalQuebrada.iMes < DataInicialQuebrada.iMes) ||
            (DataFinalQuebrada.iAno == DataInicialQuebrada.iAno && DataFinalQuebrada.iMes == DataInicialQuebrada.iMes && DataFinalQuebrada.iDia < DataInicialQuebrada.iDia)) {
            dma.retorno = 4;  // Data final menor que a inicial
            return dma;
        }

        // Ajustando dias
        dma.qtdDias = DataFinalQuebrada.iDia - DataInicialQuebrada.iDia;
        if (dma.qtdDias < 0) {
            // Substitui a lógica para calcular o número de dias no mês
            if (DataInicialQuebrada.iMes == 2) {
                // Verifica se é ano bissexto
                // if ((DataInicialQuebrada.iAno % 400 == 0) || (DataInicialQuebrada.iAno % 4 == 0 && DataInicialQuebrada.iAno % 100 != 0)) {
                //     dma.qtdDias += 29;  // Fevereiro com 29 dias
                // } else {
                //     dma.qtdDias += 28;  // Fevereiro com 28 dias
                // }
                dma.qtdDias += 28; // Assume fevereiro com 28 dias (sem considerar bissexto)
            } else if (DataInicialQuebrada.iMes == 4 || DataInicialQuebrada.iMes == 6 || 
                       DataInicialQuebrada.iMes == 9 || DataInicialQuebrada.iMes == 11) {
                dma.qtdDias += 30;  // Meses com 30 dias
            } else {
                dma.qtdDias += 31;  // Meses com 31 dias
            }
            DataFinalQuebrada.iMes--;  // Ajusta o mês
        }

        // Ajustando meses
        dma.qtdMeses = DataFinalQuebrada.iMes - DataInicialQuebrada.iMes;
        if (dma.qtdMeses < 0) {
            dma.qtdMeses += 12;  // Empresta meses do ano anterior
            DataFinalQuebrada.iAno--;  // Ajusta o ano
        }

        // Ajustando anos
        dma.qtdAnos = DataFinalQuebrada.iAno - DataInicialQuebrada.iAno;

        // Imprimindo as diferenças de dias, meses e anos para depuração
        printf("data inicial: %d/%d/%d\n", DataInicialQuebrada.iDia, DataInicialQuebrada.iMes, DataInicialQuebrada.iAno);
        printf("data final: %d/%d/%d\n", DataFinalQuebrada.iDia, DataFinalQuebrada.iMes, DataFinalQuebrada.iAno);
        printf("QtdDias após ajuste: %d\n", dma.qtdDias);
        printf("QtdMeses após ajuste: %d\n", dma.qtdMeses);
        printf("QtdAnos após ajuste: %d\n", dma.qtdAnos);

        // Definindo o retorno
        dma.retorno = 1;  // Sucesso
        return dma;
    }
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
int q3(char *texto, char c, int isCaseSensitive) {
    int qtdOcorrencias = 0;
    int tamanhoTexto = strlen(texto);
    char textoTemporario[tamanhoTexto +1];
    

    //Cópia do texto na variável temporária
    for(int i =0 ; i < tamanhoTexto; i++){
        textoTemporario[i] = texto[i];
    }
    textoTemporario[tamanhoTexto] = '\0';

    // Caso insensível ao caso
    if (isCaseSensitive != 1) {
        // Converte o caractere c para minúsculo, se necessário
        if (c >= 'A' && c <= 'Z') {
            c = c + 32;  // Converte para minúsculo
        }
        
        // Converte toda a string para minúsculo
        for (int i = 0; i < tamanhoTexto; i++) {
            if (textoTemporario[i] >= 'A' && textoTemporario[i] <= 'Z') {
                textoTemporario[i] = texto[i] + 32;  // Converte para minúsculo
            }
        }
    }
    
    // Contagem das ocorrências de c
        for (int i = 0; i < strlen(texto); i++) {
          if (textoTemporario[i] == c) {
              qtdOcorrencias++;
          }
      }

    return qtdOcorrencias;
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
int q4(char *strTexto, char *strBusca, int posicoes[30])
{
   int qtdOcorrencias = 0;  // Contador de ocorrências
    int posicao = 0;         // Índice para o vetor de posições
    
    int textoTamanho = strlen(strTexto);
    int buscaTamanho = strlen(strBusca);

    // Laço principal que percorre o texto
    for (int i = 0; i <= textoTamanho - buscaTamanho; i++) {  
        int j = 0;

        // Verifica correspondência da palavra com o texto
        while (j < buscaTamanho && (i + j) < textoTamanho && strTexto[i + j] == strBusca[j]) {
            j++;
        }

        // Se encontrou a palavra
        if (j == buscaTamanho) {
            if (posicao + 1 < 30) { 
                posicoes[posicao] = i + 1;     
                posicoes[posicao + 1] = i + j;
                posicao += 2;                  
            }

            qtdOcorrencias++;
            i += j - 1;  
        }
    }

    // Retorna a quantidade de ocorrências encontradas
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

int q5(int num)
{

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
    int qtdOcorrencias;
    return qtdOcorrencias;
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

