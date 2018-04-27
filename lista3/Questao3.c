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
    else {          /* achou o no´ a remover */
        /* no´ sem filhos */
        if (r->esq == NULL && r->dir == NULL) {
            free (r);
            r = NULL; }
        /* no´ so´ tem filho a` direita */
        else
            if (r->esq == NULL) {
                NoArv* t = r;
                r = r->dir;
                free (t);
            }
        /* so´ tem filho a` esquerda */
        else if (r->dir == NULL) {
            NoArv* t = r;
            r = r->esq;
            free (t);
        }
        /* no´ tem os dois filhos */
        else {
            NoArv* f = r->esq;
            while (f->dir != NULL)
            {
                f = f->dir;
            }
            r->info = f->info; /* troca as informac¸o~es */
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
 * Questão 3
 * O percurso In Order percore as sub-árvores, oos nós as "raizes", da esquerda para a direita
 */
void inOrderTraversal(NoArv* a){
    if(a==NULL)
        return;

    inOrderTraversal(a->esq);

    printf("%d\n", a->info);

    inOrderTraversal(a->dir);
}

/* Questão 3
 * A travessia pós ordem percorre a ávore dos nós mais externos (folhas), para os mais internos (raiz)
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
 * Questão 3
 * Não Localizei a função "preOrderHelper, nem a classe tree (classe em C...)
 * Mas implementei a ordem preOrderTraversal, de forma bem simples ele imprime a raiz e vai seguindo
 * pelos, recursivamente, pelos nós, da esquerda para a direita
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
        printf("Árvore vazia\n");
        return;
    }

    int e;

    printf("Qual tipo de travessia?\n");
    printf("Digite 1 para travessia inOrder\nDigite 2 para travessia postOrder\nDigite 3 para travessia preOrder\n");
    printf("Opção: ");
    scanf("%d", &e);

    if(e==1)
        inOrderTraversal(a);
    if(e==2)
        postOrderTraversal(a);
    if(e==3)
        preOrderTraversal(a);
}

/*
 * Questão 4
 * A função verifica os nós a partir da raiz, caso
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
 * Questão 5
 * Para esta questão foi preciso criar um tipo bool, ja que o C padrão nem possui
 * O conteudista insiste em usar a sintaxe e tipos C++ para os arquivos exemplos e isso cria vários problemas
 * enfim...
 * Considerando que já existe uma função buscaElemento, que retorna o ponteiro do elemento, caso existente,
 * a conclusão mais simples é testar o retorno da saida, false se for nula, true se for não nula.
 *
 */
bool testaElemento(NoArv* a, int v){
    if(buscaElemento(a, v))
        return true;
    else
        return false;
}

/*
 * Questão 6
 * A função testa primeiro a raiz (caso a arvore esteja vazia, retorna 0), depois testar a subarvore da esquerda (aumentado 1 nível a
 * cada chamada recursiva da função). Depois faz o mesmo na subarvore esquerda, da mesma forma.
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
 * Questão 6
 * A implementação direta da função auxRetornaNivel tem certas dificuldades quanto aos limites dos números possíveis,
 * portanto criei uma função auxiliar para tratar a possibilidade de retorno -1 que são tratados na função princila
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
    printf("1 - Inserir dados na árvore\n");
    printf("2 - Mostrar árvore\n");
    printf("3 - Fazer travessia da árvore\n");
    printf("4 - Contar folhas\n");
    printf("5 - Verificar se um número existe na árvore\n");
    printf("6 - Verificar o nível do nó onde o número se encontra\n");
    printf("7 - Contar a quantidade de nós com valores maiores que um número\n");
    printf("8 - Verificar qual subárvore é maior\n");
 // printf("96 - Contar os nós da subárvore direita\n");
 // printf("97 - Contar os nós da subárvore esquerda\n");
 // printf("98 - Contar os nós da árvore\n");
    printf("99 - Sair\n");
    printf("Opção: ");
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
            printf("Digite um número, ele será incluido numa arvore\nDigite -1 para parar e mostrar a arvore\n");
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
            printf("A árvore possui %d folha(s)\n", contarFolhas(arvore));
        if(op==5){
            int b;
            printf("Digite o número a ser verificado: ");
            scanf("%d", &b);
            if(testaElemento(arvore, b)==true)
                printf("O número existe na árvore\n");
            else
                printf("O número não existe na árvore\n");
        }
        if(op==6){
            int b;
            printf("Digite o número a ser verificado: ");
            scanf("%d", &b);
            int c = retornaNivel(arvore, b, 1);
            if(c==-1)
                printf("O elemento não foi encontrado (retorno da função igual a -1)\n");
            else
                printf("Nó no nível %d\n", c);
        }
        if(op==7){
            int b;
            printf("Digite o número a ser verificado: ");
            scanf("%d", &b);
            printf("%d números na árvore são maiores que %d\n", contaMaiores(arvore, b), b);
        }

        if(op==8){
            if(!arvore)
            printf("Ávore vazia\n");
            else {
                if(contaNos(arvore->dir)>contaNos(arvore->esq))
                    printf("A subárvore direita possui mais nós que a esquerda\n");
                if(contaNos(arvore->dir)<contaNos(arvore->esq))
                    printf("A subárvore direita possui menos nós que a esquerda\n");
                if(contaNos(arvore->dir)==contaNos(arvore->esq))
                    printf("As subárvorees direita e esquerda possuem o mesmo número de nós\n");
            }

        }

        if(op==96)
            printf("A subárvore direita possui %d nó(s)\n", contaNos(arvore->dir));
        if(op==97)
            printf("A subárvoroe esquerda possui %d nó(s)\n", contaNos(arvore->esq));

        if(op==98)
            printf("A árvore tem %d nó(s)\n", contaNos(arvore));

        if(op==99)
            break;


    }while(op<99);


    return 0;
}
