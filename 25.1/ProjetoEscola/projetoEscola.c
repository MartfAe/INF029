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


//Limpar o buffer pós SCANF
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

//Função para transformar tudo em maiusculo
void ToUpperStr(char *destino, const char *origem) {
    while (*origem != '\0') {
        *destino = toupper(*origem);
        origem++;
        destino++;
    }
    *destino = '\0';
}


//Cadastro de alunos
void cadastrarAluno(Aluno alunos[], int quantidade){
    if(quantidade >=maxAlunos){
        printf("Quantidade máxima de alunos atingida.\n");
        return;
    }
    printf("Cadastro de aluno.\n");
    
    printf("Nome:");
    fgets(alunos[quantidade].nome, maxNome, stdin);
    size_t len =strlen(alunos[quantidade].nome);
    if(len >0 && alunos[quantidade].nome[len-1]=='\n'){
        alunos[quantidade].nome[len - 1]='\0';
    }
    printf("Data de nascimento (formato: DD MM AAAA): ");
    scanf("%d %d %d", &alunos[quantidade].nascimento.dia, &alunos[quantidade].nascimento.mes, &alunos[quantidade].nascimento.ano);
    limparBuffer();

    printf("Sexo (M/F): ");
    scanf(" %c", &alunos[quantidade].sexo);
    limparBuffer();

    alunos[quantidade].sexo= toupper(alunos[quantidade].sexo);
    while((alunos[quantidade].sexo != 'F') && (alunos[quantidade].sexo != 'M')) {
        printf("Entrada inválida! Digite 'M' para masculino ou 'F' para feminino: ");
        scanf(" %c", &alunos[quantidade].sexo);
        limparBuffer();
        alunos[quantidade].sexo = toupper(alunos[quantidade].sexo);
    }

    printf("Aluno cadastrado com sucesso!\n");
    return quantidade + 1;

}

//Cadastro de professores. 

void cadastrarProfessor(Professor professores[], int quantidade){
    if (quantidade >= maxProfessores)
    {
        printf("Número máximo de professores cadastrados atingido.\n");
        return;
    }
    printf("Cadastro de professor.\n");

    printf("Digite o nome:\n");
    fgets(professores[quantidade].nome, maxNome, stdin);
    size_t len =strlen(professores[quantidade].nome);
    if(len >0 && professores[quantidade].nome[len-1]=='\n'){
        professores[quantidade].nome[len - 1]='\0';
    }

    printf("Data de nascimento (formato DD MM AAAA):\n");
    scanf("%d%d%d", &professores[quantidade].nascimento.dia, &professores[quantidade].nascimento.mes, &professores[quantidade].nascimento.ano );
    limparBuffer();

    printf("Digite o sexo (M ou F):\n");
    scanf(" %c", &professores[quantidade].sexo);
    limparBuffer();
    professores[quantidade].sexo = toupper(professores[quantidade].sexo);
    while((professores[quantidade].sexo != 'F') && (professores[quantidade].sexo != 'M')){
        printf("Sexo inválido. Digite M para masculino e F para feminino.\n");
        scanf(" %c", &professores[quantidade].sexo);
        limparBuffer();
        professores[quantidade].sexo = toupper(professores[quantidade].sexo);
    }

    printf("Professor cadastrado com sucesso!\n");
    return quantidade + 1;

}

//Função de remoção de aluno

int removerAluno(Aluno alunos[], int quantidade){
    char nomeBusca[maxNome];
    char termoUpper[maxNome];
    char nomeAlunoUpper[maxNome];
    int indicesEncontrados[maxAlunos];
    int countEcontrados = 0;

    printf("Digite o nome ou parte do nome, do aluno que deseja remover:");
    fgets(nomeBusca, maxNome, stdin);
    size_t len = strlen(nomeBusca);
    if(len >0 && nomeBusca[len-1] == '\n'){
        nomeBusca[len-1] = '\0';
    }

    strcpy(termoUpper, nomeBusca);
    toUpperStr(termoUpper);

    //Busca de alunos com nome parcialmente igual. 

    for(int i =0; i <quantidade; i++){
        strcpy(nomeAlunoUpper, alunos[i].nome);
        toUpperStr(nomeAlunoUpper);

        if(strstr(nomeAlunoUpper, termoUpper) != NULL){
            printf("[%d]-Nome: %s\n Sexo: %c\n Nascimento: %02d/%02d/%04d\n",countEcontrados, alunos[i].nome, alunos[i].sexo, alunos[i].nascimento.dia,
            alunos[i].nascimento.mes, alunos[i].nascimento.ano);
            indicesEncontrados[countEcontrados]=i;
            countEcontrados++;
        }
    }

    if(countEcontrados == 0){
        printf("Nenhum aluno foi encontrado.\n");
        return quantidade;
    }

    int escolha;
    printf("Digite o número correspondente ao aluno que deseja remover:");
    scanf("%d", &escolha);
    limparBuffer();

    if(escolha <0 || escolha>=countEcontrados){
        printf("Escolha inválida.\n");
        return quantidade;
    }

    int indiceReal=indicesEncontrados[escolha];

    char confirmacao;
    printf("Tem certeza que deseja remover o aluno '%s'? (S/N): ", alunos[indiceReal].nome);
    scanf("%c", &confirmacao);
    limparBuffer();
    confirmacao = toupper(confirmacao);

    if(confirmacao != 'S'){
        printf("Remoção cancelada.\n");
        return quantidade;
    }

    //Remove o aluno mudando a posição dos demais

    for(int i = indiceReal; i <quantidade -1; i++){
        alunos[i]=alunos[i+1];
    }

    printf("Aluno removido com sucesso.\n");
    return quantidade -1 ; 
}

int removerProessor(Professor professores[], int quantidade){
    char nomeBusca[maxNome];
    char termoUpper[maxNome];
    char nomeProfessorUpper[maxNome];
    int indicesEncontrados[maxProfessores];
    int countEncontrados =0;

    printf("Digite parte do nome, ou o Nome, do professor que deseja remover: ");
    fgets(nomeBusca, maxNome, stdin);
    size_t len = strlen(nomeBusca);
    if(len >0 && termoBusca[len -1]== '\n'){
        termoBusca[len -1] ='\0';
    }


}