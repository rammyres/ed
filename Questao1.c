#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

typedef enum bool{false = 0, true=!false};

struct no {
    char* info;
    struct no* esq;
    struct no* dir;
};

typedef struct no NoArv;

//esses prototipos das funcoes
NoArv* criaArvoreVazia(void);
NoArv* criaComSubArvores(char* c, NoArv* e, NoArv* d);
NoArv* arv_libera(NoArv* a);
int arv_vazia(NoArv* a);
int arv_pertence(NoArv* a, char c);
void mostraArvore(NoArv* a);


NoArv* criaArvoreVazia(void)
{
    return NULL;
}


NoArv* criaComSubArvores (char* c, NoArv* sae, NoArv* sad) {

    NoArv* p = (NoArv*)malloc(sizeof(NoArv));

    if(p == NULL)
        exit(1);

    p->info = c;
    p->esq = sae;
    p->dir = sad;
    return p;
}

NoArv* arv_libera (NoArv* a){
    if (!arv_vazia(a)){
        arv_libera(a->esq);
        arv_libera(a->dir);
        free(a);
    }
    return NULL;
}

int arv_vazia (NoArv* a)
{
    return a==NULL;
}


int arv_pertence (NoArv* a, char c) {
    if (arv_vazia(a))
        return 0; /* a´rvore vazia na~o encontrou */
    else
        return a->info == c || arv_pertence(a->esq,c) || arv_pertence(a->dir,c);
}

void mostraArvore(NoArv* a) {
    printf("<");
    if (!arv_vazia(a)){
        printf(" %c ",a->info);
        mostraArvore(a->esq);
        mostraArvore(a->dir);
    }
    printf("> ");
}

NoArv* criarNo(char* d){
    NoArv* no = (NoArv*)malloc(sizeof(NoArv*));

    no->info = d;
    no->esq = NULL;
    no->dir = NULL;

    return no;

}

void menu(){
        printf("Escolha uma das opções abaixo.\n");
        printf("1 - Inserir um novo nó na arvore\n");
        printf("2 - Mostrar a arvore\n");
        printf("9 - Sair\n");
        printf("Opção: ");
}

int main(){
    setlocale(LC_ALL, "portuguese");

    //Exemplo:<a<b<><d<><>>><c<e<><>><f<><>>>>
    int op=0;
    char* a = (char*)malloc(sizeof(char)*255);

    NoArv* arvore = criaArvoreVazia();
    NoArv* no1 = criaArvoreVazia();
    NoArv* no2 = criaArvoreVazia();
    NoArv* no11 = criaArvoreVazia();
    NoArv* no12 = criaArvoreVazia();
    NoArv* no21 = criaArvoreVazia();
    NoArv* no22 = criaArvoreVazia();
    printf("Digite os dados quando solicitado, eles serão incluidos numa arvore\n");
    printf("Digite um elemento: ");
    fflush(stdin);
    scanf("%s", &a);
    no11 = criarNo(a);
    printf("Digite um elemento: ");
    fflush(stdin);
    scanf("%s", &a);
    no12 = criarNo(a);
    printf("Digite um elemento: ");
    fflush(stdin);
    scanf("%s", &a);
    no21= criarNo(a);
    printf("Digite um elemento: ");
    fflush(stdin);
    scanf("%s", &a);
    no22= criarNo(a);
    printf("Digite um elemento: ");
    fflush(stdin);
    scanf("%s", &a);
    no1= criaComSubArvores(a, no11, no12);
    printf("Digite um elemento: ");
    fflush(stdin);
    scanf("%s", &a);
    no2= criaComSubArvores(a, no21, no22);
    printf("Digite um elemento: ");
    fflush(stdin);
    scanf("%s", &a);
    arvore= criaComSubArvores(a, no1, no2);

    mostraArvore(arvore);

    return 0;
}


