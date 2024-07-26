#include <stdio.h>
#include <stdlib.h>


typedef struct _tnode_{
    void *data;
    struct _tnode_ *l;
    struct _tnode_ *r;
}TNode;

void printdata(void *data){
    if(data != NULL){
        //TIPO *aux = (TIPO*)data;
        int *x = (int*)data; // (int*)aux->int;
                             //       aux->string;
                             // (float*)aux->float;
        printf("%i", *x);
        printf("\n");
    }else{
        printf("-\n");
    }
}

int cmp(void* a, void* b){
    int *x = (int*)a;
    int *y = (int*)b;
    if(*x == *y){
        return 0;
    }
    else if(*x < *y){
        return -1;
    }
    return 1;
}

void apbListar(){
    //visitação simétrica
    //visitação pos-ordem
    //visitação pre-ordem
}

void abpQuery(){

}


TNode *findMin(TNode *t) {
    while (t->l != NULL) {
        t = t->l;
    }
    return t;
}

TNode *findMax(TNode *t) {
    while (t->r != NULL) {
        t = t->r;
    }
    return t;
}


TNode *abpRemove(TNode *t, void *key, int(*cmp)(void* a, void* b), void **data){
    if(t != NULL){ 
        printf("Node\n");
        int stat = cmp(key, t->data);
        if(stat < 0){
            printf("left");
            t->l = abpRemove(t->l, key, cmp, data);
            return t;
        }else if(stat > 0){
            printf("right");
            t->r = abpRemove(t->r, key, cmp, data);
            return t;
        }else{
            printf("achou o que vai ser removido\n");
            *data = t->data;
            printf("salvou data\n");
        
            if(t->l == NULL && t->r == NULL){ // Folha
                free(t);
                return NULL;
            }else if(t->l == NULL && t->r != NULL){ // Nó somente com filho direito 
                TNode *aux = t->r;
                free(t);
                return aux;
            }else if(t->l != NULL && t->r == NULL){ // Nó somente com filho esquerdo
                TNode *aux = t->l;
                free(t);
                return aux;
            }else{ //Nó com dois filhos
                //TNode *aux = findMin(t->r); // Acha o sucessor, o menor dos maiores
                TNode *aux = findMax(t->l); // Acha o sucessor, o maior dos menores
                t->data = aux->data;    // Substitui o dado do nó a ser removido pelo dado do sucessor
                void *data2 = (void*)malloc(sizeof(void));
                t->l = abpRemove(t->l, aux->data, cmp, data2); // Remove o sucessor da subárvore esquerda
                //t->r = abpRemove(t->r, aux->data, cmp, data); // Remove o sucessor da subárvore direita
                
                /*
                    pra escolher o sucessor é opcional, pode ser o maior dos menores (subárvores esquerda) ou o menor dos maiores (subárvore direita)
                    dependendo da escolha você vai precisar fazer umas modificações como descomentar as linhas

                     //TNode *aux = findMin(t->r); // Acha o sucessor, o menor dos maiores
                     //t->r = abpRemove(t->r, aux->data, cmp, data); // Remove o sucessor da subárvore direita

                     e comentar as linhas 

                      TNode *aux = findMax(t->l); // Acha o sucessor, o maior dos menores
                      t->l = abpRemove(t->l, aux->data, cmp, data); // Remove o sucessor da subárvore esquerda
                */
                
                return t;
            }
        }
    }
    
    return NULL;
}


TNode *createTree(){
    TNode *t = NULL;
    return t;
}



TNode *abpInsert(TNode *t, void* data, int(*cmp)(void*, void*)){
    if(t != NULL){
        int stat = cmp(data, t->data);
        if(stat >= 0){
            t->r = abpInsert(t->r, data, cmp);
        }else{
            t->l = abpInsert(t->l, data, cmp);
        }
        return t;
    }else{
        TNode *newnode = (TNode*)malloc(sizeof(TNode));
        if(newnode != NULL){
            newnode->l = NULL;
            newnode->r = NULL;
            newnode->data = data;
            return newnode;
        }
        return NULL;
    }
}


int main(){

    int *p = (int*)malloc(sizeof(int));
    int *h = (int*)malloc(sizeof(int));
    int *y = (int*)malloc(sizeof(int));
    int *vk = (int*)malloc(sizeof(int));
    int *ry = (int*)malloc(sizeof(int));
    *p = 14;
    *h = 21;
    *y = 11;
    *vk = 33;
    *ry = 15;

    int *data = (int*)malloc(sizeof(int));
    *data = NULL;
    
    TNode *t = createTree();
    t = abpInsert(t, p, cmp);
    t = abpInsert(t, h, cmp);
    t = abpInsert(t, y, cmp);
    t = abpInsert(t, vk, cmp);
    t = abpInsert(t, ry, cmp);
    printdata(t->l->data);
    printdata(t->data);
    printdata(t->r->data);
    printdata(t->r->l->data);
    printdata(t->r->r->data);
    
    t = abpRemove(t, h, cmp, data);
    printf("\ndepois da remocao\n");
    printdata(t->l->data);
    printdata(t->data);
    printdata(t->r->data);
    printdata(t->r->r->data);
    


    /*

    
    
    */
    



   // printdata(p); //nesse caso vai ser t->data, mas o campo inteiro

}