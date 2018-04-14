#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

typedef enum { false = 0, true =!false } bool;

struct no{
    int info;
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

void insereElemento(Fila* fila, int info){
    No* novo;
    novo = (No*) malloc(sizeof(No));

    novo->info = info;
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

int removeElemento(Fila *fila){
    int valor;
    No *aux;

    if (filaVazia(fila)){
        printf("Fila esta vazia! \n");
        exit(-1);
    }

    aux = fila->inicio;
    valor = aux->info;
    fila->inicio = aux->prox;

    if( fila->inicio == NULL)
        fila->fim = NULL;

    free(aux);
    return valor;
}

//mostra elementos da fila
void mostraFila(Fila *fila){

    No *aux;
    if (filaVazia(fila))
        printf("Fila esta vazia!\n");
    else{
        aux = fila->inicio;

        printf("Inicio: %d \n", fila->inicio->info);
        printf("Fim: %d \n", fila->fim->info);

        printf("Demais valores: ");
        for (aux = aux->prox; aux->prox != NULL; aux = aux->prox) {
            printf("%d ", aux->info);
        }
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

bool buscaElemento(Fila *fila, int item){
    No *aux = fila->inicio;

    while(aux){
        if(aux->info == item)
            return true;
        else
            aux = aux->prox;
    }
}

int main(){
    setlocale(LC_ALL, "portuguese");

    Fila *fila;

    fila = criaFila();

    insereElemento(fila,12);
    insereElemento(fila,65);
    insereElemento(fila,23);
    insereElemento(fila,43);
    insereElemento(fila,11);
    insereElemento(fila,21);
    insereElemento(fila,23);
    insereElemento(fila,98);
    insereElemento(fila,10);
    insereElemento(fila,9);

    mostraFila(fila);

    printf("\nDigite um número, verificaremos se ele está na fila: ");
    int entrada;
    scanf("%d", &entrada);
    if(buscaElemento(fila, entrada)==true)
        printf("O número procurado está na fila\n");
    else
        printf("O número procurado não está na fila\n");
    getchar();
    liberaFila(fila);

    return 0;
}

