#include <stdio.h>
#include <stdlib.h>
#include <locale.h>


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

void mostrarTopo(int *pilha, int topo){
    if (topo == -1) {
        printf("Pilha vazia\n");
        exit(0);
    }
    printf("Topo da pilha: %d\n",pilha[topo]);
}

int maior(int *pilha, int topo){
    int maior=0;
    if (topo == -1) {
        printf("Pilha vazia\n");
        exit(0);
    }
    else
        for(int i = topo; i > -1 ; i--){
            if(maior<pilha[i])
                maior=pilha[i];
        }
    return maior;
}
int menor(int *pilha, int topo){
    int menor=pilha[topo];
    if (topo == -1) {
        printf("Pilha vazia\n");
        exit(0);
    }
    else
        for(int i = 0; i<=(topo) ; i++){
            if(menor>pilha[i])
                menor=pilha[i];
        }
    return menor;
}

float media(int *pilha, int topo){
    float media=0;
    int i;
    if (topo == -1) {
        printf("Pilha vazia\n");
        exit(0);
    }
    else
        for(i = 0; i<=topo; i++){
            media = media + (float)pilha[i];
        }
    return media/i;
}

int main(){
    setlocale(LC_ALL, "portuguese");

    int *pilha, topo = -1, aux, entrada;

    pilha = criaPilha();

    printf("Bem vindo a lista 2\n");
    printf("Digite numeros inteiros positivos, eles serão adicionados a pilha\n");
    printf("Para parar digite -1\n");
    while(entrada>=0){
        printf("Entrada: ");
        scanf("%d", &entrada);
        if(entrada>=0)
            insereElemento(pilha, entrada, &topo);
        else
            break;

        mostrarTopo(pilha, topo);
        printf("\n");
    }
    mostrarPilha(pilha, topo);
    printf("\n");
    printf("Maior número da pilha: %d\n", maior(pilha, topo));
    printf("Menor número da pilha: %d\n", menor(pilha, topo));
    printf("A média aritmética da pilha é %.2f\n", media(pilha, topo));

    /* insereElemento(pilha, 12, &topo);
    insereElemento(pilha, 11, &topo);
    insereElemento(pilha, 98, &topo);
    insereElemento(pilha, 34, &topo);
    insereElemento(pilha, 66, &topo);
    insereElemento(pilha, 65, &topo);
    insereElemento(pilha, 76, &topo);
    insereElemento(pilha, 87, &topo);

    mostrarPilha(pilha, topo);

    aux = removeElemento(pilha, &topo);
   // aux = removeElemento(pilha, &topo);
   // aux = removeElemento(pilha, &topo);
   // aux = removeElemento(pilha, &topo);

    if (aux>-1)
        printf("\nElemento a ser removido %d\n", pilha[aux]);

    mostrarPilha(pilha, topo); */

    return 0;

}
