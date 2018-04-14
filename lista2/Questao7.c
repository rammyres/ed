#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

typedef enum { false = 0, true =!false } bool;

struct no{
    char* nome;
    float salario;
    struct no *prox;
};

typedef struct no No;

struct f{
    No* inicio;
    No* fim;
};

typedef struct f Fila;

Fila *criaFila(){
    Fila *fi = (Fila*) malloc(sizeof(Fila));
    fi->inicio = NULL;
    fi->fim = NULL;
    return fi;
}

void insereElemento(Fila* fila, char* n, float s){
    No* novo;
    novo = (No*) malloc(sizeof(No));

    novo->nome = n;
    novo->salario = s;
    novo->prox = NULL;

    if (fila->fim != NULL)//se a fila jÃ¡ possui elementos
        fila->fim->prox = novo;
     else
         fila->inicio = novo;

    fila->fim = novo;
}

bool filaVazia(Fila *fila){
    bool fv;
    if (fila->inicio == NULL)
        fv = true;
    else
        fv = false;

    return fv;
}

char* removeElemento(Fila *fila){
    char* valor;
    No *aux;

    if (filaVazia(fila)){
        printf("Fila esta vazia! \n");
        exit(-1);
    }

    aux = fila->inicio;
    valor = aux->nome;
    fila->inicio = aux->prox;

    if( fila->inicio == NULL)
        fila->fim = NULL;

    free(aux);
    return valor;
}

void imprimeLinha(char c){
    for(int i = 0; i < 80 ; i++)
        printf("%c", c);
    printf("\n");
}
void imprimeNo(No* aux){
    printf("Nome: %s\n", aux->nome);
    printf("Salário: %.2f\n", aux->salario);
}
//mostra elementos da fila
void mostraFila(Fila *fila){

    No *aux;
    if (filaVazia(fila)==true)
        printf("Fila esta vazia!\n");
    else{

        aux=fila->inicio;

        imprimeLinha('=');
        //        for (aux = aux->prox; aux->prox != NULL; aux = aux->prox) {
        while(aux){

            imprimeNo(aux);
            aux = aux->prox;
            imprimeLinha('-');

        }
        imprimeLinha('=');
    }
}

//libera a memoria alocada
void liberaFila(Fila *fila){
    No *aux;
    aux = fila->inicio;
    while (aux->prox != NULL) {
        No* t;
        t = aux->prox;
        free(aux);
        aux = t;
    }
    free(fila);
}

char* maior(Fila *fila){
    No *aux;
    char* nome = (char*)malloc(sizeof(char)*255);
    float maior = 0;

    aux = fila->inicio;

    while(aux->prox){
        if(maior<aux->salario){
            maior=aux->salario;
            printf("%f %f\n", maior, aux->salario);
            strcpy(nome,aux->nome);
        }
        aux = aux->prox;
    }
    if(maior == 0){
        strcpy(nome, fila->inicio->nome);
    }

    return nome;
}

char* menor(Fila *fila){
    No *aux;
    char* nome = (char*)malloc(sizeof(char)*255);
    float menor = fila->fim->salario;

    aux = fila->inicio;

    while(aux->prox){
        if(menor>aux->salario){
            menor=aux->salario;
            strcpy(nome,aux->nome);
        }
        aux = aux->prox;
    }
    if(menor == fila->fim->salario){
        strcpy(nome, fila->fim->nome);
    }

    return nome;
}

float media(Fila *fila){
    No *aux;
    int i;
    float soma = 0;
    aux=fila->inicio;
    while(aux){
        soma+=aux->salario;
        i++;
        aux=aux->prox;
    }
    return soma/i;
}

Fila* encherFila(void){
    Fila* fila =(Fila*)malloc(sizeof(Fila));
    insereElemento(fila, "Teste 1", 1000);
    insereElemento(fila, "Teste 2", 500);
    insereElemento(fila, "Teste 3", 800);
    insereElemento(fila, "Teste 4", 2000);
    insereElemento(fila, "Teste 5", 1100);
    insereElemento(fila, "Teste 6", 2000);
    insereElemento(fila, "Teste 7", 19000);
    insereElemento(fila, "Teste 8", 1111);
    return fila;
}

void menu(void){
    printf("Digite 1 para incluir 1 funcionário\n");
    printf("Digite 2 para mostrar todos os funcionários\n");
    printf("Digite 3 para mostrar o funcionário com o maior salário\n");
    printf("Digite 4 para mostrar o funcionário com o menor saláraio\n");
    printf("Digite 5 para obter a média dos salários dos funcionários\n");
    printf("Digite 8 para preencher a fila\n");
    printf("Digite 9 para encerrar\n");
    printf("Opção: ");
}

int main(){
    setlocale(LC_ALL, "portuguese");

    Fila *fila;

    fila = criaFila();

    int opcao = 0;

    printf("Bem vindo a Lista 2 - questão 7\n");
    while(opcao<9){
        menu();
        scanf("%d", &opcao);

        if(opcao==1){
                float salario;
                char* nome = (char*)malloc(sizeof(char)*255);
                printf("Digite o nome do funcionário: ")/
                fflush(stdin);
                scanf("%s", nome);
                nome[strcspn(nome, "\n")]=0;
                printf("Digite o salário do usuário (ex.: 1000,00): ");
                scanf("%f", &salario);
                insereElemento(fila, nome, salario);
        } else
        if(opcao==2)
            if(filaVazia(fila)==true)
                printf("Fila vazia\n");
            else
                mostraFila(fila);
        else
        if(opcao==3)
            if(filaVazia(fila)==true)
                printf("Fila vazia\n");
            else
                printf("%s possui o maior salario\n", maior(fila));
        else
        if(opcao==4)
            if(filaVazia(fila)==true)
                printf("Fila vazia\n");
            else
                printf("%s possui o menor salario\n", menor(fila));
        else
        if(opcao==5)
            if(filaVazia(fila)==true)
                printf("Fila vazia\n");
            else
                printf("A média dos salários dos funcionários cadastrados é de R$ %.2f\n", media(fila));
        else
        if(opcao==8){
            fila = encherFila();
        }
        if(opcao == 9)
            break;
    }

    if(filaVazia(fila)==false)
        liberaFila(fila);

    return 0;
}

