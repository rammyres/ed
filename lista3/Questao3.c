#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>

typedef enum {false = 0, true=!false} bool;

struct no {
    int info;
    struct no* esq;
    struct no* dir;
};
typedef struct no NoArv;

NoArv* criaArvore (void)
{
    return NULL;
}

int arvoreVazia(NoArv *arvore){
    return arvore == NULL;
}

//exibir Em Ordem
void mostraArvore (NoArv* a) {
    if (a != NULL) {
        mostraArvore(a->esq);
        printf("%d\n",a->info);
        mostraArvore(a->dir);
    }
}

NoArv* buscaElemento (NoArv* r, int v)
{
    if (r == NULL)
        return NULL;
    else
        if (r->info > v)
            return buscaElemento (r->esq, v);
        else
            if (r->info < v)
                return buscaElemento (r->dir, v);
            else
                return r;
}

NoArv* insereElemento (NoArv* a, int v)
{
    if (a == NULL) {
        a = (NoArv*)malloc(sizeof(NoArv));
        a->info = v;
        a->esq = NULL;
        a->dir = NULL;
    }
    else
        if (v < a->info)
            a->esq = insereElemento(a->esq,v);
    else
        if (v > a->info)
        a->dir = insereElemento(a->dir,v);
    return a;
}

int buscaElemento2(NoArv *arvore, int valor){

    if (arvoreVazia(arvore))
        return 0;

    return arvore->info == valor || buscaElemento2(arvore->esq,valor) || buscaElemento2(arvore->dir, valor);
}

NoArv* removeElemento (NoArv* r, int v) {
    if (r == NULL){
        printf("elemento nao existe\n");
        return NULL;
        }
    else
        if (r->info > v)
        r->esq = removeElemento(r->esq, v);
    else
        if (r->info < v)
        r->dir = removeElemento(r->dir, v);
    else {          /* achou o no� a remover */
        /* no� sem filhos */
        if (r->esq == NULL && r->dir == NULL) {
            free (r);
            r = NULL; }
        /* no� so� tem filho a` direita */
        else
            if (r->esq == NULL) {
                NoArv* t = r;
                r = r->dir;
                free (t);
            }
        /* so� tem filho a` esquerda */
        else if (r->dir == NULL) {
            NoArv* t = r;
            r = r->esq;
            free (t);
        }
        /* no� tem os dois filhos */
        else {
            NoArv* f = r->esq;
            while (f->dir != NULL)
            {
                f = f->dir;
            }
            r->info = f->info; /* troca as informac�o~es */
            f->info = v;
            r->esq = removeElemento(r->esq,v);
        }
    }
    return r;
}

void raizArvore(NoArv *arvore){
    printf("Raiz-> %d\n",arvore->info);

}

/*
 * Quest�o 3
 * O percurso In Order percore as sub-�rvores, oos n�s as "raizes", da esquerda para a direita
 */
void inOrderTraversal(NoArv* a){
    if(a==NULL)
        return;

    inOrderTraversal(a->esq);

    printf("%d\n", a->info);

    inOrderTraversal(a->dir);
}

/* Quest�o 3
 * A travessia p�s ordem percorre a �vore dos n�s mais externos (folhas), para os mais internos (raiz)
 * da esquerda para a direita
 */
void postOrderTraversal(NoArv* a){
    if(a==NULL)
        return;

    postOrderTraversal(a->esq);
    postOrderTraversal(a->dir);
    printf("%d\n", a->info);
}

/*
 * Quest�o 3
 * N�o Localizei a fun��o "preOrderHelper, nem a classe tree (classe em C...)
 * Mas implementei a ordem preOrderTraversal, de forma bem simples ele imprime a raiz e vai seguindo
 * pelos, recursivamente, pelos n�s, da esquerda para a direita
 */
void preOrderTraversal(NoArv* a){
    if(a==NULL)
        return;

    printf("%d\n", a->info);

    preOrderTraversal(a->dir);
    preOrderTraversal(a->esq);
}

void mostrarTraversals(NoArv* a){
    if(a==NULL){
        printf("�rvore vazia\n");
        return;
    }

    int e;

    printf("Qual tipo de travessia?\n");
    printf("Digite 1 para travessia inOrder\nDigite 2 para travessia postOrder\nDigite 3 para travessia preOrder\n");
    printf("Op��o: ");
    scanf("%d", &e);

    if(e==1)
        inOrderTraversal(a);
    if(e==2)
        postOrderTraversal(a);
    if(e==3)
        preOrderTraversal(a);
}

/*
 * Quest�o 4
 * A fun��o verifica os n�s a partir da raiz, caso
 */
int contarFolhas(NoArv* a){
    if(a==NULL)
        return 0;
    if(a->esq==NULL && a->dir==NULL)
        return 1;
    else
        return contarFolhas(a->esq)+contarFolhas(a->dir);
}

/*
 * Quest�o 5
 * Para esta quest�o foi preciso criar um tipo bool, ja que o C padr�o nem possui
 * O conteudista insiste em usar a sintaxe e tipos C++ para os arquivos exemplos e isso cria v�rios problemas
 * enfim...
 * Considerando que j� existe uma fun��o buscaElemento, que retorna o ponteiro do elemento, caso existente,
 * a conclus�o mais simples � testar o retorno da saida, false se for nula, true se for n�o nula.
 *
 */
bool testaElemento(NoArv* a, int v){
    if(buscaElemento(a, v))
        return true;
    else
        return false;
}

/*
 * Quest�o 6
 * A fun��o testa primeiro a raiz (caso a arvore esteja vazia, retorna 0), depois testar a subarvore da esquerda (aumentado 1 n�vel a
 * cada chamada recursiva da fun��o). Depois faz o mesmo na subarvore esquerda, da mesma forma.
 */

int auxRetornaNivel(NoArv* n, int k, int l){
    if(n == NULL)
        return 0;
    if(n->info == k)
        return l;
    int baixo = auxRetornaNivel(n->esq, k, l+1);
    if(baixo != 0)
        return baixo;

    baixo=auxRetornaNivel(n->dir, k, l+1);
    return baixo;
}

/*
 * Quest�o 6
 * A implementa��o direta da fun��o auxRetornaNivel tem certas dificuldades quanto aos limites dos n�meros poss�veis,
 * portanto criei uma fun��o auxiliar para tratar a possibilidade de retorno -1 que s�o tratados na fun��o princila
 */

int retornaNivel(NoArv* n, int k, int l){
    if(auxRetornaNivel(n, k, l)>0)
        return auxRetornaNivel(n, k, l);
    else
        return -1;
}

int contaNos(NoArv* a){
    if(a==NULL)
        return 0;
    return 1+contaNos(a->esq)+contaNos(a->dir);
}

int auxContaMaiores(NoArv* a, int n){
    if(a==NULL)
        return;

    auxContaMaiores(a->esq, n);
    auxContaMaiores(a->dir, n);
    if(a->info<n)
        return 1;

}

int contaMaiores(NoArv* a, int n){
    int t = auxContaMaiores(a, n);

    return t;
}

void menu(void){
    printf("1 - Inserir dados na �rvore\n");
    printf("2 - Mostrar �rvore\n");
    printf("3 - Fazer travessia da �rvore\n");
    printf("4 - Contar folhas\n");
    printf("5 - Verificar se um n�mero existe na �rvore\n");
    printf("6 - Verificar o n�vel do n� onde o n�mero se encontra\n");
    printf("7 - Contar a quantidade de n�s com valores maiores que um n�mero\n");
    printf("8 - Verificar qual sub�rvore � maior\n");
 // printf("96 - Contar os n�s da sub�rvore direita\n");
 // printf("97 - Contar os n�s da sub�rvore esquerda\n");
 // printf("98 - Contar os n�s da �rvore\n");
    printf("99 - Sair\n");
    printf("Op��o: ");
}

int main(){
    setlocale(LC_ALL, "portuguese");
    srand(time(NULL));

    NoArv *arvore;

    arvore = criaArvore();

    int op = 0;

    printf("Bem vindo a lista 3\n");

    do{
        menu();
        scanf("%d", &op);
        if(op==1){
            printf("Digite um n�mero, ele ser� incluido numa arvore\nDigite -1 para parar e mostrar a arvore\n");
            int ent = 0;
            while(ent > -1){
                printf("Entrada:");
                scanf("%d", &ent);

                if(ent>-1)
                    arvore=insereElemento(arvore, ent);
                if(ent==-1)
                    break;
            }
        }
        if(op==2)
            mostraArvore(arvore);
        if(op==3)
            mostrarTraversals(arvore);
        if(op==4)
            printf("A �rvore possui %d folha(s)\n", contarFolhas(arvore));
        if(op==5){
            int b;
            printf("Digite o n�mero a ser verificado: ");
            scanf("%d", &b);
            if(testaElemento(arvore, b)==true)
                printf("O n�mero existe na �rvore\n");
            else
                printf("O n�mero n�o existe na �rvore\n");
        }
        if(op==6){
            int b;
            printf("Digite o n�mero a ser verificado: ");
            scanf("%d", &b);
            int c = retornaNivel(arvore, b, 1);
            if(c==-1)
                printf("O elemento n�o foi encontrado (retorno da fun��o igual a -1)\n");
            else
                printf("N� no n�vel %d\n", c);
        }
        if(op==7){
            int b;
            printf("Digite o n�mero a ser verificado: ");
            scanf("%d", &b);
            printf("%d n�meros na �rvore s�o maiores que %d\n", contaMaiores(arvore, b), b);
        }

        if(op==8){
            if(!arvore)
            printf("�vore vazia\n");
            else {
                if(contaNos(arvore->dir)>contaNos(arvore->esq))
                    printf("A sub�rvore direita possui mais n�s que a esquerda\n");
                if(contaNos(arvore->dir)<contaNos(arvore->esq))
                    printf("A sub�rvore direita possui menos n�s que a esquerda\n");
                if(contaNos(arvore->dir)==contaNos(arvore->esq))
                    printf("As sub�rvorees direita e esquerda possuem o mesmo n�mero de n�s\n");
            }

        }

        if(op==96)
            printf("A sub�rvore direita possui %d n�(s)\n", contaNos(arvore->dir));
        if(op==97)
            printf("A sub�rvoroe esquerda possui %d n�(s)\n", contaNos(arvore->esq));

        if(op==98)
            printf("A �rvore tem %d n�(s)\n", contaNos(arvore));

        if(op==99)
            break;


    }while(op<99);


    return 0;
}
