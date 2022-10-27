#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <windows.h>

#include "func.h"

int bDead;//chegagem b
int aDead;//checagem a
int nScore;
int nScreenWidth;
int nScreenHeight;

Snake* inicializa (void)
{
    return NULL;
}

Snake* insere (Snake* l, int x1, int y1)
{
    Snake* novo = (Snake*) malloc(sizeof(Snake));
    novo->x = x1;
    novo->y = y1;
    novo->prox = l;
    return novo;
}

void GotoXY(int x, int y)// coordenadas
{
    HANDLE a;
    COORD b;
    fflush(stdout);
    b.X = x;
    b.Y = y;
    a = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(a,b);
}

void Boarder(Snake* snake)// imprime o quadro
{
    system("cls");
    int i;
    GotoXY(0,0);
    printf("\t\tScore: %d\t\tX: %d Y: %d",nScore, snake->x, snake->y);// informações do jogo
    for(i=1; i<nScreenWidth; i++)
    {
        GotoXY(i,1);
        printf("!");
        GotoXY(i,nScreenHeight);
        printf("!");
    }
    for(i=1; i<nScreenHeight; i++)
    {
        GotoXY(0,i);
        printf("!");
        GotoXY(nScreenWidth,i);
        printf("!");
    }
    printf("\n\n");
}

void pop_back(Snake* l)// remove ultimo elemento
{
    Snake* p;
    for (p=l; p->prox->prox!=NULL; p=p->prox);
    p->prox=NULL;
}
int ultimo_x(Snake* l)// func. aux. retorna ultima coordenada X
{
    Snake* p=l;
    for (; p!=NULL; p=p->prox)
        if(p->prox == NULL)
            return p->x;
}
int ultimo_y(Snake* l)// func. aux. retorna ultima coordenada Y
{
    Snake* p=l;
    for (; p!=NULL; p=p->prox)
        if(p->prox == NULL)
            return p->y;
}
Snake* push_back(Snake* l, int ultimo_x, int ultimo_y)// faz a cobrinha crescer ao comer a Food
{
    Snake* p;
    Snake* novo = (Snake*) malloc(sizeof(Snake));
    for (p=l; p->prox!=NULL; p=p->prox);
    novo->x = ultimo_x;
    novo->y = ultimo_y;
    novo->prox = NULL;
    p->prox = novo;
    return l;
}
int ourobouros(Snake* snake)// caso a cobra morda ela mesma
{
    Snake* p;
    for(p=snake->prox; p!=NULL; p=p->prox)
        if(snake->x == p->x && snake->y == p->y)
            return 1;//bDead = true
    return 0;
}

int colisao_parede(Snake* snake)// colisao com o limite do tabuleiro
{
    if (snake->x == 0 || snake->x == nScreenWidth)
        return 2;
    else if (snake->y == 1 || snake->y == nScreenHeight)
        return 2;
    else
        return 0;
}
void reset()
{
    printf("Jogo sera (re)iniciado em 3 segundos.");
    Sleep(3000);
}
int dentro(Snake* snake, int food_x, int food_y)// func. aux para impedir que Food seja gerada dentro do corpo da cobra
{
    Snake* p;
    for(p=snake; p!=NULL; p=p->prox)
        if(food_x==p->x && food_y==p->y)
            return 1;
    return 0;
}
void menu()
{
    printf("Controle a direcao da snake @ utilizando as setas <- e ->\n\n");
    system("pause");
    system("cls");
}
void desenha_snake(Snake* snake)
{
    Snake* p = snake;
    GotoXY(p->x, p->y);
    printf("@");
    p=p->prox;
    for(; p->prox!=NULL; p=p->prox)
    {
        GotoXY(p->x, p->y);
        printf("O");
    }
}
