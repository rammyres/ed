#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

struct tree{
    int info, fb;

    struct tree *sae;
    struct tree *sad;
};

typedef struct tree arvore;

arvore *raiz = NULL;

int altura( arvore *aux){
    if(!aux){
        return 0;
    }
    int ae = altura(aux->sae);
    int ad = altura(aux->sad);

    return (ae > ad) ? ae + 1: ad + 1;
}


arvore* buscar(int n){
    arvore *aux;
    aux = raiz;
    while(aux && aux->info != n){
        if(n < aux->info){
            aux = aux->sae;
        }
        else{
            aux = aux->sad;
        }
    }
    return aux;
}

void limpar_arvore( arvore *aux){
    if(aux->sae){
        limpar_arvore(aux->sae);
    }
    if(aux->sad){
        limpar_arvore(aux->sad);
    }

    free(aux);
    raiz = NULL;
}

//rotacao simples a esquerda
arvore * rotacionar_dir_dir (  arvore *  no )
{
    arvore *  temp = no;
    arvore * dir = temp->sad;

    temp->sad = dir->sae;
    dir->sae = temp;

    return dir;
}
//rotacao simples a direita
arvore * rotacionar_esq_esq (  arvore *  no )
{
    arvore *  temp = no;
    arvore * esq = temp->sae;

    temp->sae = esq->sad;
    esq->sad = temp;

    return esq;
}

//rotacao dupla a direitra
arvore * rotationar_esq_dir ( arvore *  no )
{
    arvore *  temp = no;
    arvore * esq = temp->sae;
    arvore * dir = esq->sad;

    temp->sae = dir->sad;
    esq->sad = dir->sae;
    dir->sae = esq;
    dir->sad = temp;

    return dir;
}
//rotacao dupla a esquerda

arvore * rotacionar_dir_esq (  arvore *  no )
{
    arvore *  temp = no;
    arvore * dir = temp->sad;
    arvore * esq = dir->sae;

    temp->sad = esq->sae;
    dir->sae = esq->sad;
    esq->sad = dir;
    esq->sae = temp;

    return esq;
}


arvore * novoNo ( int valor )
{
    arvore * no;

    no = (arvore*) malloc ( sizeof ( arvore ) );
    if ( no == NULL )
    {
        puts ( "o programa ficou sem memória\n" );
        system ( "pause" );
    }

    no->sae = NULL;
    no->sad = NULL;
    no->info = valor;

    return no;
}

int fator_bal (  arvore *  no )
{
    int fator = 0;

    if ( no->sae )
        fator -= altura ( no->sae );

    if ( no->sad )
        fator += altura ( no->sad );

    return fator;
}


arvore * balancear_node ( arvore *  no )
{
    arvore * node_balanceado = NULL;

    if ( no->sae )
        no->sae = balancear_node ( no->sae );

    if ( no->sad )
        no->sad = balancear_node ( no->sad );

    int fator = fator_bal ( no );
    no->fb = fator;

    if ( fator <= -2 )
    {
        /* pesando pra esquerda */

        if ( fator_bal ( no->sae ) <= -1 )
            node_balanceado = rotacionar_esq_esq ( no );
        else
            node_balanceado = rotationar_esq_dir ( no );

    }
    else if ( fator >= 2 )
    {
        /* pesando pra direita */

        if ( fator_bal ( no->sad ) >= 1 )
            node_balanceado = rotacionar_dir_dir ( no );
        else
            node_balanceado = rotacionar_dir_esq ( no );

    }
    else
    {
        node_balanceado = no;
    }

    return node_balanceado;
}

void ajustaFB( arvore *aux){
    if(!raiz){
        printf("Arvore vazia!");
        return;
    }

    if(aux){
        ajustaFB(aux->sae);
        aux->fb = fator_bal(aux);
        ajustaFB(aux->sad);
        aux->fb = fator_bal(aux);
    }
}


arvore* balancear_tree ( arvore *  tree )
{
    arvore * nova_raiz = NULL;

    nova_raiz = balancear_node ( tree );

    if ( nova_raiz != tree )
    {
        tree = nova_raiz;
    }
    ajustaFB(tree);
    return tree;
}

void inserir (int valor)
{
    arvore * novo_no = NULL;
    arvore * proximo = NULL;
    arvore * ultimo = NULL;

    if ( raiz == NULL )
    {
        novo_no = novoNo ( valor );
        raiz = novo_no;
    }
    else
    {
        proximo = raiz;

        while ( proximo != NULL )
        {
            ultimo = proximo;

            if ( valor < proximo->info )
            {
                proximo = proximo->sae;

            }
            else if ( valor > proximo->info )
            {
                proximo = proximo->sad;
            }
            else if ( valor == proximo->info )
            {
                return;
            }
        }

        novo_no = novoNo ( valor );

        if ( valor < ultimo->info )
            ultimo->sae = novo_no;

        if ( valor > ultimo->info )
            ultimo->sad = novo_no;

    }
    raiz = balancear_tree(raiz);

}

arvore* removeElemento (arvore* r, int v) {
    if (r == NULL){
        printf("elemento nao existe\n");
        return NULL;
    }
    else
        if (r->info > v)
            r->sae = removeElemento(r->sae, v);
        else
            if (r->info < v)
                r->sad = removeElemento(r->sad, v);
            else {          /* achou o no´ a remover */
                /* no´ sem filhos */
                if (r->sae == NULL && r->sad == NULL) {
                    free (r);
                    r = NULL;
                    //balancear_tree(r);
                }
                /* no´ so´ tem filho a` direita */
                else
                    if (r->sae == NULL) {
                        arvore* t = r;
                        r = r->sad;
                        free (t);
                    }
                /* so´ tem filho a` esquerda */
                    else if (r->sad == NULL) {
                        arvore* t = r;
                        r = r->sae;
                        free (t);
                    }
                /* no´ tem os dois filhos */
                    else {
                        arvore* f = r->sae;
                        while (f->sad != NULL)
                        {
                            f = f->sad;
                        }
                        r->info = f->info; /* troca as informac¸o~es */
                        f->info = v;
                        r->sae = removeElemento(r->sae,v);
                    }
            }
    return r;
}


void exibir_ordenado( arvore *aux){
    if(!raiz){
        printf("Arvore vazia!");
        return;
    }

    if(aux){
        exibir_ordenado(aux->sae);
        //aux->fb = fator_bal(aux);
        printf("%d(%d) ", aux->info, aux->fb);
        exibir_ordenado(aux->sad);
    }
}

void inOrderTraversal(arvore* a){
    if(a==NULL)
        return;

    inOrderTraversal(a->sae);

    printf("%d ", a->info);

    inOrderTraversal(a->sad);
}

void postOrderTraversal(arvore* a){
    if(a==NULL)
        return;

    postOrderTraversal(a->sae);
    postOrderTraversal(a->sad);
    printf("%d ", a->info);
}

void preOrderTraversal(arvore* a){
    if(a==NULL)
        return;

    printf("%d ", a->info);

    preOrderTraversal(a->sad);
    preOrderTraversal(a->sae);
}

void menu(void){

    printf("1.	Inserir elemento\n");
    printf("2.	Mostrar arvore em pre-ordem\n");
    printf("3.	Mostrar arvore em pos-ordem\n");
    printf("4.	Mostrar arvore em em-ordem\n");
    printf("5.	Altura da arvore\n");
    printf("6.	Buscar nó\n");
    printf("7.	Excluir nó\n");
    printf("8.	Sair\n");
    printf("Digite a opção: ");

}

int main(){
    setlocale(LC_ALL, "portuguese");

    //int vet[3] = {3,2,1}; // provoca rotacao a simples a direita
    //int vet[3] = {1,2,3}; // provoca rotacao a simples a esquerda
    //int vet[3] = {3,1,2}; // provoca rotacao a dupla a direita
    //int vet[3] = {1,3,2}; // provoca rotacao a dupla a esquerda

    //for (int i = 0; i<10; i++){
    //    inserir(rand() % 50);
    //}

    int op=0;

    printf("Bem vindo a lista 4\n");

    do{
        menu();

        scanf("%d", &op);

        if(op==1){
            int e;

            printf("Digite um número inteiro positivo, ele será inserido na árvore\n");
            printf("Digite -1 para interromper a inserção\n");
            do{
                printf("Entrada: ");
                scanf("%d", &e);
                if(e>=0)
                    inserir(e);

            }while(e>=0);
        }
        if(op==2){
            preOrderTraversal(raiz);
            printf("\n");
        }
        if(op==3){
            postOrderTraversal(raiz);
            printf("\n");
        }

        if(op==4){
            inOrderTraversal(raiz);
            printf("\n");
        }

        if(op==5)
            printf("A altura da árvore é %d\n", altura(raiz));

        if(op==6){
            printf("Digite o número a ser buscado: ");
            int b;
            scanf("%d", &b);

            if(buscar(b))
                printf("O elemento está na árvore\n");
            else
                printf("O elemento não está na árvore\n");
        }

        if(op==7){
            printf("Digite o número a ser removido da árvore: ");
            int r;
            scanf("%d", &r);

            raiz=removeElemento(raiz, r);
            exibir_ordenado(raiz);
            printf("\n");
        }
        if(op==8)
            break;

    }while(op<8);
    exibir_ordenado(raiz);

    //primeiro remove o elemento, caso ele exista
    raiz = removeElemento(raiz, 8);
    //apos a remocao balancear a arvore
    raiz = balancear_tree(raiz);
    printf("\n Depois da remocao");
    exibir_ordenado(raiz);

    limpar_arvore(raiz);

    return 0;
}
