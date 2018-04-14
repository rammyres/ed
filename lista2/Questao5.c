#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#define TAM 100

struct professor{
    char* nome;
    int titulacao;
    float salario;
};

typedef struct professor Professor;

Professor *criaPilha(){
    Professor *pilha;
    pilha = (Professor*) malloc(sizeof(Professor)*TAM);
    return pilha;
}

Professor criaElemento(void){
    Professor elemento;
    elemento.nome = (char*)malloc(sizeof(char)*255);
    //char* entrada = (char*)malloc(sizeof(char)*255);
    printf("Digite o nome do professor: ");
    fflush(stdin);
    //fgets(entrada, sizeof(char)*255, stdin);
    fgets(elemento.nome, sizeof(char)*255, stdin);
    //scanf("%s", &nome);
    elemento.nome[strcspn(elemento.nome, "\n")]='\0';
    //entrada[strcspn(entrada, "\n")]=0;
    //strcpy(elemento.nome, entrada);
    printf("Digite o título do professor (Digite 1 para mestre, 2 para doutor e 3 para especialista): ");
    scanf("%d", &elemento.titulacao);
    printf("Digite o salário do professor (ex: 2000,00): ");
    scanf("%f", &elemento.salario);

    return elemento;
}
void insereElemento(Professor *pilha, Professor valor, int *topo){
    if (*topo < TAM) {
        *topo = *topo + 1;
        pilha[*topo] = valor;
    }
    else{
        printf("A pilha não suporta mais elementos, aloque mais espeaco\n");
    }
}

char* titulacao(int t){
    if(t==1)
        return "Mestre";
    if(t==2)
        return "Doutor";
    if(t==3)
        return "Especialista";
}

void mostrarPilha(Professor *pilha, int topo){
    if (topo == -1) {
        printf("Pilha vazia\n");
        //exit(0);
    }

    for(int i = topo; i >= 0 ; i--){
        printf("Nome: %s\n", pilha[i].nome);
        printf("Titulação: %s\n", titulacao(pilha[i].titulacao));
        printf("Salário: %.2f\n", pilha[i].salario);
        for(int j = 0; j<80; j++)
            printf("=");
        printf("\n");
    }
}

void mostrarElemento(Professor pilha){
        printf("Nome: %s\n", pilha.nome);
        printf("Titulação: %s\n", titulacao(pilha.titulacao));
        printf("Salário: %.2f\n", pilha.salario);
}

int removeElemento(Professor *pilha, int *topo){
    if (*topo == -1) {
        printf("Pilha vazia \n");
        return -1;
    }
    else{
        *topo = *topo - 1;//decrementando
        return *topo+1;
    }
}
int buscaPorTitulo(Professor* pilha, int topo, int titulo){
    printf("Retornando todos os %ss\n", titulacao(titulo));
    for(int i = topo; i>=0; i--){
        if(pilha[i].titulacao==titulo)
            mostrarElemento(pilha[i]);
    }
}



void menu(){
    printf("Digite 1 para incluir 1 professor na pilha\nDigite 2 para remover 1 professor da pilha\nDigite 3 para mostrar a pilha\n");
    printf("Digite 4 para listar os professores por título\nDigite 5 para buscar os professores pelo nome\nDigite 9 para encerrar\n");
    printf("Opção: ");
}

int main(){
    setlocale(LC_ALL, "portuguese");

    int topo = -1, opcao=0;
    Professor aux, *pilha;

    pilha = criaPilha();

    printf("Bem vindo a lista 2 (questão 5)\n");

    while(opcao<9){
        menu();
        scanf("%d", &opcao);

        if(opcao == 1)
            insereElemento(pilha, criaElemento(), &topo);
        if(opcao == 2)
            removeElemento(pilha, &topo);
        if(opcao == 3)
            mostrarPilha(pilha, topo);
        if(opcao == 4){
            int tit;
            if(topo>0){

                printf("Digite o título para listar (1 para mestre, 2 para doutor e 3 para especialista): ");
                scanf("%d", &tit);

                if(tit<1 || tit>3)
                    printf("Titulo inválido\n");
                else
                buscaPorTitulo(pilha, topo, tit);
            } else
                printf("Pilha vazia\n");
        }


        if(opcao == 9)
            break;
    }


   //aux = removeElemento(pilha1, &topo1);
   // aux = removeElemento(pilha, &topo);
   // aux = removeElemento(pilha, &topo);
   // aux = removeElemento(pilha, &topo);

    //if (aux>-1)
    //    printf("\nElemento a ser removido %d\n", pilha1[aux]);


    return 0;

}
