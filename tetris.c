#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 5


typedef struct {
    char tipo;
    int id;
} peca;


typedef struct {
    peca pecas[MAX];
    int inicio;
    int fim;
    int tamanho;
} fila;


void gerarPeca(peca *p);
int filaVazia(fila *f);
int filaCheia(fila *f);
void inicializarFila(fila *f);
void remover(fila *f, peca *removido);
void adicionar(fila *f, peca *adicionado);
void mostrarFila(fila *f);
void flush_in();

int id0 = 0;

int main(){
    fila *filaPecas = malloc(sizeof(fila));
    inicializarFila(filaPecas);
    while(1){
        mostrarFila(filaPecas);
        printf("1 - Jogar Peça (dequeue)\n");
        printf("2 - Inserir Nova Peça (enqueue)\n");
        printf("0 - Sair\n");
        int resposta;
        printf("Escolha uma opçao: ");
        scanf("%d", &resposta);
        flush_in();

        switch(resposta){
            case 1:
                if(filaVazia(filaPecas)){
                    printf("\nA fila está vazia. Não há peças para se jogar.\n\n");
                    break;
                }
                peca *pecaRemovida = malloc(sizeof(peca));
                remover(filaPecas, pecaRemovida);
                free(pecaRemovida);
                break;
            case 2:
                if(filaCheia(filaPecas)){
                    printf("\nA fila está cheia. Não é possível adicionar peças.\n\n");
                    break;
                }
                peca *pecaAdicionada = malloc(sizeof(peca));
                printf("Que peça você deseja adicionar à fila: ");
                scanf("%c", &pecaAdicionada->tipo);
                flush_in();
                pecaAdicionada->id = id0;
                id0++;
                adicionar(filaPecas, pecaAdicionada);
                free(pecaAdicionada);
                break;
            case 0:
                printf("Volte Sempre!!!\n\n");
                return 0;
        }
        printf("\n\n\n");
    }
    return 0;
}


int filaVazia(fila *f){
    return f->tamanho == 0;
}


int filaCheia(fila *f){
    return f->tamanho == MAX;
}


void inicializarFila(fila *f){
    f->inicio = 0;
    f->fim = 0;
    f->tamanho = 0;
    peca *p = malloc(sizeof(peca));
    for(int i = 0; i < MAX; i++){
        gerarPeca(p);
        adicionar(f, p);
    }
    free(p);
}


void flush_in(){
    int ch;
    while( (ch = fgetc(stdin)) != EOF && ch != '\n' ){}
}


void remover(fila *f, peca *removido){
    if(!filaVazia(f)){
        *removido = f->pecas[f->inicio];
        f->inicio = (f->inicio + 1) % MAX;
        f->tamanho--;
    }
}


void adicionar(fila *f, peca *adicionado){
    if(!filaCheia(f)){
        f->pecas[f->fim] = *adicionado;
        f->fim = (f->fim + 1) % MAX;
        f->tamanho++;
    }
}


void gerarPeca(peca *p){
    srand(time(NULL));
    char tipos[4] = {'I', 'O', 'T', 'L'};
    p->tipo = tipos[rand() % 4];
    p->id = id0;
    id0++;
}


void mostrarFila(fila *f){
    printf("Fila de pecas: ");
    for(int i = 0, idx = f->inicio; i < f->tamanho; i++, idx = (idx + 1) % MAX){
        printf("[%c %d] ", f->pecas[idx].tipo, f->pecas[idx].id);
    }
    printf("\n");
}