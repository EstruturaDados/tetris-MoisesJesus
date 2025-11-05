#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAXFILA 5
#define MAXPILHA 3


typedef struct {
    char tipo;
    int id;
} peca;


typedef struct {
    peca pecas[MAXFILA];
    int inicio;
    int fim;
    int tamanho;
} fila;


typedef struct {
    peca pecas[MAXPILHA];
    int topo;
} pilha;


void gerarPeca(fila *f);
int filaVazia(fila *f);
int filaCheia(fila *f);
void inicializarFila(fila *f);
peca remover(fila *f);
void inserir(fila *f, peca *adicionado);
void mostrarFila(fila *f);
void inicializarPilha(pilha *p);
int pilhaCheia(pilha *p);
int pilhaVazia(pilha *p);
void push(pilha *p, peca nova);
peca pop(pilha *p);
void mostrarPilha(pilha *p);
peca peekFila(fila *f);
void flush_in();


int main(){
    pilha *reserva = malloc(sizeof(pilha));
    inicializarPilha(reserva);

    fila *filaPecas = malloc(sizeof(fila));
    inicializarFila(filaPecas);

    peca pecaRemovida;

    while(1){
        mostrarFila(filaPecas);
        mostrarPilha(reserva);
        printf("\n\nOpções:\n");
        printf("1 - Jogar peça da frente da fila\n");
        printf("2 - Enviar peça da fila pra reserva (pilha)\n");
        printf("3 - Usar peça da reserva (pilha)\n");
        printf("4 - Trocar peça da frente com o topo da pilha\n");
        printf("5 - Trocar 3 primeiros da filas com as 3 peças da pilha\n");
        printf("0 - Sair\n");
        int resposta;
        printf("Escolha uma opçao: ");
        scanf("%d", &resposta);
        flush_in();
        printf("\n\n");

        switch(resposta){
            case 1:
                pecaRemovida = remover(filaPecas);
                printf("Você jogou a peça %c.", pecaRemovida.tipo);

                gerarPeca(filaPecas);
                break;
            case 2:
                if(pilhaCheia(reserva)){
                    printf("Reserva Cheia.\n");
                    break;
                }
                pecaRemovida = remover(filaPecas);
                gerarPeca(filaPecas);
                push(reserva, pecaRemovida);
                break;
            case 3:
                if(pilhaVazia(reserva)){
                    printf("Reserva Vazia. Não há o que remover.\n");
                    break;
                }
                pecaRemovida = pop(reserva);
                printf("Você jogou a peça %c.", pecaRemovida.tipo);
                break;
            case 4:
                if(pilhaVazia(reserva)){
                    printf("Reserva Vazia.\n");
                    break;
                }

                peca topoDaPilha = pop(reserva);
                push(reserva, peekFila(filaPecas));
                filaPecas->pecas[filaPecas->inicio] = topoDaPilha;
                printf("Troca realizada entre o primeiro da fila e o último da pilha.");
                break;
            case 5:
                if(!pilhaCheia(reserva)){
                    printf("A reserva deve estar cheia.\n");
                    break;
                }

                for(int i = 0; i < MAXPILHA; i++){
                    peca aux = filaPecas->pecas[(filaPecas->inicio + i) % MAXFILA];
                    filaPecas->pecas[(filaPecas->inicio + i) % MAXFILA] = pop(reserva);
                    push(reserva, aux);
                }
                printf("Troca realizada entre os 3 primeiros da fila e os 3 da pilha.");
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
    return f->tamanho == MAXFILA;
}


void inicializarFila(fila *f){
    f->inicio = 0;
    f->fim = 0;
    f->tamanho = 0;
    for(int i = 0; i < MAXFILA; i++){
        gerarPeca(f);
    }
}


void flush_in(){
    int ch;
    while( (ch = fgetc(stdin)) != EOF && ch != '\n' ){}
}


peca remover(fila *f){
    peca removida = f->pecas[f->inicio];
    f->inicio = (f->inicio + 1) % MAXFILA;
    f->tamanho--;
    return removida;
}


void inserir(fila *f, peca *adicionado){
    if(!filaCheia(f)){
        f->pecas[f->fim] = *adicionado;
        f->fim = (f->fim + 1) % MAXFILA;
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
    inserir(f, p);
    free(p);
    id0++;

}


void mostrarFila(fila *f){
    printf("Fila de pecas: ");
    for(int i = 0, idx = f->inicio; i < f->tamanho; i++, idx = (idx + 1) % MAXFILA){
        printf("[%c %d] ", f->pecas[idx].tipo, f->pecas[idx].id);
    }
    printf("\n");
}


void inicializarPilha(pilha *p){
    p->topo = -1;
}


int pilhaCheia(pilha *p){
    return p->topo == MAXPILHA - 1;
}


int pilhaVazia(pilha *p){
    return p->topo == -1;
}


void push(pilha *p, peca nova){
    p->topo++;
    p->pecas[p->topo] = nova;
}


peca pop(pilha *p){
    return p->pecas[p->topo--];
}


void mostrarPilha(pilha *p){
    printf("Pilha de Reserva (Topo -> Base): ");
    for(int i = p->topo; i >= 0; i--){
        printf("[%c %d] ", p->pecas[i].tipo, p->pecas[i].id);
    }
    printf("\n");
}


peca peekFila(fila *f){
    return f->pecas[f->inicio];
}
