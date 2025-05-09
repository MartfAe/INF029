#include <stdio.h>
#include <stdlib.h>


typedef struct 
{
    int dia, mes, ano;
}Data;

typedef struct 
{
    char nome[50];
    char sexo;
    char cpf[15];
    Data nascimento;
}Pessoa;
