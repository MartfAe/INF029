int contaDigito(int N, int x){
    if( N ==0){
        return 0;
    }
    if (N%10 == x){
        return contaDigito(N/10, x) + 1;
    }
    else
    return contaDigito(N/10, x);
}

int main(){
    int N, x;

    printf("Digite um número inteiro:");
    scanf("%d", &N);

    printf("Digite um dígito:");
    scanf("%d", &x);

    printf("O dígito %d aparece %d vezes em %d\n", x, contaDigito(N, x), N);

    return 0;
}

