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


typedef struct {
    peca pecas[MAX];
    int topo;
} pilha;


void gerarPeca(fila *f);
int filaVazia(fila *f);
int filaCheia(fila *f);
void inicializarFila(fila *f);
void remover(fila *f, peca *removido);
void adicionarFila(fila *f, peca *adicionado);
void mostrarFila(fila *f);
void inicializarPilha(pilha *p);
int pilhaCheia(pilha *p);
int pilhaVazia(pilha *p);
void adicionarPilha(pilha *p, peca *nova);
void pop(pilha *p, peca *removida);
void mostrarPilha(pilha *p);
void flush_in();


int main(){
    pilha *reserva = malloc(sizeof(pilha));
    inicializarPilha(reserva);

    fila *filaPecas = malloc(sizeof(fila));
    inicializarFila(filaPecas);

    peca *pecaRemovida = malloc(sizeof(peca));

    while(1){
        mostrarFila(filaPecas);
        mostrarPilha(reserva);
        printf("1 - Jogar Peça (dequeue)\n");
        printf("2 - Reservar Peça\n");
        printf("3 - Usar Peça Reservada\n");
        printf("0 - Sair\n");
        int resposta;
        printf("Escolha uma opçao: ");
        scanf("%d", &resposta);
        flush_in();

        switch(resposta){
            case 1:
                remover(filaPecas, pecaRemovida);
                printf("Você jogou a peça %c", pecaRemovida->tipo);

                gerarPeca(filaPecas);
                break;
            case 2:
                if(pilhaCheia(reserva)){
                    printf("Reserva Cheia.\n");
                    break;
                }
                remover(filaPecas, pecaRemovida);
                gerarPeca(filaPecas);
                adicionarPilha(reserva, pecaRemovida);
                break;
            case 3:
                if(pilhaVazia(reserva)){
                    printf("Reserva Vazia. Não há o que remover.\n");
                    break;
                }
                pop(reserva, pecaRemovida);
                printf("Você jogou a peça %c", pecaRemovida->tipo);
                break;
            case 0:
                printf("Volte Sempre!!!\n\n");
                return 0;
        }
        printf("\n\n\n");
    }
    free(pecaRemovida);
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
    for(int i = 0; i < MAX; i++){
        gerarPeca(f);
    }
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


void adicionarFila(fila *f, peca *adicionado){
    if(!filaCheia(f)){
        f->pecas[f->fim] = *adicionado;
        f->fim = (f->fim + 1) % MAX;
        f->tamanho++;
    }
}


void gerarPeca(fila *f){
    static int id0 = 0;
    srand(time(NULL));
    char tipos[4] = {'I', 'O', 'T', 'L'};
    peca *p = malloc(sizeof(peca));
    p->tipo = tipos[rand() % 4];
    p->id = id0;
    adicionarFila(f, p);
    free(p);
    id0++;

}


void mostrarFila(fila *f){
    printf("Fila de pecas: ");
    for(int i = 0, idx = f->inicio; i < f->tamanho; i++, idx = (idx + 1) % MAX){
        printf("[%c %d] ", f->pecas[idx].tipo, f->pecas[idx].id);
    }
    printf("\n");
}


void inicializarPilha(pilha *p){
    p->topo = -1;
}


int pilhaCheia(pilha *p){
    return p->topo == MAX - 1;
}


int pilhaVazia(pilha *p){
    return p->topo == -1;
}


void adicionarPilha(pilha *p, peca *nova){
    if(pilhaCheia(p)){
        printf("Pilha Cheia. Não é possível adicionar.\n");
        return;
    }
    p->topo++;
    p->pecas[p->topo] = *nova;
}


void pop(pilha *p, peca *removida){
    if(pilhaVazia(p)){
        printf("Pilha Vazia. Não é possível Remover.\n");
        return;
    }
    *removida = p->pecas[p->topo];
    p->topo--;
}


void mostrarPilha(pilha *p){
    printf("Reserva de Peças: ");
    for(int i = p->topo; i >= 0; i--){
        printf("[%c %d]", p->pecas[i].tipo, p->pecas[i].id);
    }
    printf("\n");
}
