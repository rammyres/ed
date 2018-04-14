#include <stdio.h>
#include <stdlib.h>


#define TAM 100

int *criaPilha(){
    int *pilha;
    pilha = (int*) malloc(sizeof(int)*TAM);
    return pilha;
}

void insereElemento(int *pilha, int valor, int *topo){
    if (*topo < TAM) {
        *topo = *topo + 1;
        pilha[*topo] = valor;

    }
    else{
        printf("A pilha nao suporta mais elementos, aloque mais espeaco\n");
    }
}

void mostrarPilha(int *pilha, int topo){
    if (topo == -1) {
        printf("Pilha vazia\n");
        exit(0);
    }
    printf("Topo da pilha: %d\nDemais valores: ",pilha[topo]);

    for(int i = (topo-1); i >= 0 ; i--){
        printf("%d ", pilha[i]);
    }
}

int removeElemento(int *pilha, int *topo){
    if (*topo == -1) {
        printf("Pilha vazia \n");
        return -1;
    }
    else{
        *topo = *topo - 1;//decrementando
        return *topo+1;
    }
}


int main(){

    int *pilha1, *pilha2, topo1 = -1, topo2 = -1, aux;

    pilha1 = criaPilha();

    insereElemento(pilha1, 12, &topo1);
    insereElemento(pilha1, 11, &topo1);
    insereElemento(pilha1, 98, &topo1);
    insereElemento(pilha1, 34, &topo1);
    insereElemento(pilha1, 66, &topo1);
    insereElemento(pilha1, 65, &topo1);
    insereElemento(pilha1, 76, &topo1);
    insereElemento(pilha1, 87, &topo1);

    mostrarPilha(pilha1, topo1);

   //aux = removeElemento(pilha1, &topo1);
   // aux = removeElemento(pilha, &topo);
   // aux = removeElemento(pilha, &topo);
   // aux = removeElemento(pilha, &topo);

    //if (aux>-1)
    //    printf("\nElemento a ser removido %d\n", pilha1[aux]);

    if(topo1>-1)
        printf("\nRemoveremos metade dos elementos da pilha atual e moveremos para a segunda pilha\n");

    pilha2 = criaPilha();

    for(int i=0; i<=topo1/2+1; i++)
            insereElemento(pilha2, pilha1[removeElemento(pilha1, &topo1)], &topo2);

    printf("Pilha 1\n");
    mostrarPilha(pilha1, topo1);
    printf("\n");
    printf("Pilha 2\n");
    mostrarPilha(pilha2, topo2);

    return 0;

}
