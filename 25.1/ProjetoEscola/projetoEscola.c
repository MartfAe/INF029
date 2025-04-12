#include <stdio.h>
#include <stdlib.h> 

#define maxAlunos 100
#define maxProfessores 100
#define maxDisciplinas 100
#define maxAlunosPorDisciplina 100
#define maxMatricula
#define maxNome 60

typedef struct{
    int dia, mes, ano;
}Data;
typedef struct {
    char nome[maxNome];
    char sexo;
    Data nascimento;
    int cpf; 
}Aluno;

typedef struct {
    char nome[maxNome];
    char sexo;
    Data nascimento;
    int cpf; 
}Professor;

typedef struct {
    char nome[maxNome];
    char codigo[8];
    float semestre;
    Aluno alunos[maxAlunosPorDisciplina]; // Verificar se essa definição pode ser utilizada. 
    int numVagas; 
    int numAlunos;
}Disciplina;

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void cadastrarAluno(Aluno alunos[], int *quantidade){
    if(*quantidade >=maxAlunos){
        printf("Quantidade máxima de alunos atingida.\n");
        return;
    }
    printf("Cadastro de aluno.\n");
    
    printf("Nome:");
    fgets(alunos[*quantidade].nome, maxNome, stdin);
    size_t len =strlen(alunos[*quantidade].nome);
    if(len >0 && alunos[*quantidade].nome[len-1]=='\n'){
        alunos[*quantidade].nome[len - 1]='\0';
    }
    printf("Data de nascimento (formato: DD MM AAAA): ");
    scanf("%d %d %d", &alunos[*quantidade].nascimento.dia, &alunos[*quantidade].nascimento.mes, &alunos[*quantidade].nascimento.ano);
    limparBuffer();

    printf("Sexo (M/F): ");
    scanf(" %c", &alunos[*quantidade].sexo);
    limparBuffer();

    alunos[*quantidade].sexo= toupper(alunos[*quantidade].sexo);
    while((alunos[*quantidade].sexo != 'F') && (alunos[*quantidade].sexo != 'M')) {
        printf("Entrada inválida! Digite 'M' para masculino ou 'F' para feminino: ");
        scanf(" %c", &alunos[*quantidade].sexo);
        limparBuffer();
        alunos[*quantidade].sexo = toupper(alunos[*quantidade].sexo);
    }

    (*quantidade)++;
    printf("Aluno cadastrado com sucesso!\n");

}


void cadastrarProfessor(Professor professores[], int *quantidade){
    if(*quantidade >=maxProfessores){
        printf("Número máximo de professores cadastrados atingido.\n");
        return;
    }
    printf("Cadastro de professor.\n");

    printf("Digite o nome:\n");
    fgets(professores[*quantidade].nome, maxNome, stdin);
    size_t len =strlen(professores[*quantidade].nome);
    if(len >0 && professores[*quantidade].nome[len-1]=='\n'){
        professores[*quantidade].nome[len - 1]='\0';
    }

    printf("Data de nascimento (formato DD MM AAAA):\n");
    scanf("%d%d%d", &professores[*quantidade].nascimento.dia, &professores[*quantidade].nascimento.mes, &professores[*quantidade].nascimento.ano );
    limparBuffer();

    printf("Digite o sexo (M ou F):\n");
    scanf(" %c", &professores[*quantidade].sexo);
    limparBuffer();
    professores[*quantidade].sexo = toupper(professores[*quantidade].sexo);
    while((professores[*quantidade].sexo != 'F') && (professores[*quantidade].sexo != 'M')){
        printf("Sexo inválido. Digite M para masculino e F para feminino.\n");
        scanf(" %c", &professores[*quantidade].sexo);
        limparBuffer();
        professores[*quantidade].sexo = toupper(professores[*quantidade].sexo);
    }
    (*quantidade)++;

    printf("Professor cadastrado com sucesso!\n");

}

