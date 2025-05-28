#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    char nome[50];
}Aluno;

typedef struct{
    char nome[50];
    Aluno alunos[5];
    int qtdAlunos;
}Disciplina; 

int matriculaAluno(Aluno alunoNovo, Disciplina *disciplinas){
    if(disciplinas->qtdAlunos>=5){
        return 0;
    }

    for(int i =0; i <disciplinas->qtdAlunos; i++){
        if(strcmp(disciplinas->alunos[i].nome, alunoNovo.nome)==0){
            return -1;
        }
    }

    strcpy(disciplinas->alunos[disciplinas->qtdAlunos].nome, alunoNovo.nome);
    disciplinas->qtdAlunos++;
    return 1;
}

int main(){
    Disciplina labProg;
    strcpy(labProg.nome, "Laboratorio de Programacao");
    labProg.qtdAlunos = 0;

    Aluno joao; 
    strcpy(joao.nome, "Joao");

    int resultado = matriculaAluno(joao, &labProg);

    if(resultado==1){
        printf("Matriculado com sucesso.");
    }else if(resultado == 0){
        printf("Falha. Disciplina lotada.\n");
    }else{
        printf("Falha, aluno já matriculado.");
    }
}