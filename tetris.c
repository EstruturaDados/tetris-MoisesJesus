#include <stdio.h>

#define MAX 5

typedef struct {
    char pecas[MAX];
    int inicio;
    int fim;
    int tamanho;
} fila;


void listaVazia(fila *f);
void listaCheia(fila *f);
void inicializarLista(fila *f);
void remover(fila *f, *removido);
void adicionar(fila *f, char *adicionado);
void mostrarFila(fila *f);

int main(){
    return 0;
}


void listaVazia(fila *f){
    return f->tamanho == 0;
}


void listaCheia(fila *f){
    return f->tamanho == MAX;
}


void inicializarLista(fila *f){
    f->inicio = 0;
    f->fim = 0;
    f->tamanho = 0;
}


void remover(fila *f, char *removido){
    if(!listaVazia(f)){
        *removido = f->pecas[f->inicio];
        f->inicio = (f->inicio + 1) % MAX;
        f->tamanho--;
    }
}


void adicionar(fila *f, char *adicionado){
    if(!listaCheia(f)){
        f->pecas[l->fim] = adicionado;
        f->fim = (l->fim + 1) % MAX;
        f->tamanho++;
    }
}


void mostrarFila(lista *l){
    prinf("");
}