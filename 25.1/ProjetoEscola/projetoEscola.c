#include <stdio.h>
#include <stdlib.h> 

#define maxAlunos 100
#define maxProfessores 100
#define maxDisciplinas 100
#define maxAlunosPorDisciplina 100
#define maxMatricula

#define prefixoAluno '2025106'
#define prefixoProfessor '2025117'


// Definindo as Structs
typedef struct{
    int dia, mes, ano;
}data;


typedef struct{
    char nome[50];
    char sexo;
    char matricula[maxMatricula];
    data aniversario;
    int disciplinas;
}pessoas;

typedef struct{
    char nome[50];
    char codigo[9];
    char professor[50];
    float semestre;
    pessoas aluno[maxAlunosPorDisciplina];
    int numAlunos;
    int numVagas;
    int temProfessor;
}materias;


//Definindo as funções. 

void cadastrarPessoa(pessoas *cadastro, int maxPessoas, char tipoPessoa);
void cadastrarDisciplina(materias *disciplinas, int maxDisciplinas, pessoas *professores, int maxDisciplinas);
void gerarMatriculaAluno(char matricula[]);
void gerarMatriculaProfessor(char matricula[]);

//Funções de validação
void validarNome(char nome[]);
void validarSexo(char sexo);
void validarCpf(char cpf[]);
int validarData(data aniversario);
int validarCodigoDisciplina(char codigo[]);
int validarSemestre(float semestre);
void toUpperString(char *str);

int contadorAluno = 0;
int contadorProfessor = 0;

