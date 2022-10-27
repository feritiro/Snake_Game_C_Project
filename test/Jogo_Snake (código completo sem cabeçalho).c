#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <conio.h>
#include <ctype.h>
#include <windows.h>
#include <process.h>
//Cabeça da cobrinha fica no inicio da lista. Para se mover, se é inserido uma nova cabeça e remove-se o ultimo elemento.
int bDead;//chegagem b
int aDead;//checagem a
int nScore;
int nScreenWidth = 72;
int nScreenHeight = 18;

typedef struct sSnakeSegment
{
    int x;
    int y;
    struct sSnakeSegment* prox;
} Snake;

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
int main()
{
    menu();
    while(1)
    {
        // Reset
        reset();
        fflush(stdin);
        Snake* snake = inicializa();
        snake = insere(snake, 20, 15);
        snake = insere(snake, 21, 15);
        snake = insere(snake, 22, 15);
        snake = insere(snake, 23, 15);
        snake = insere(snake, 24, 15);
        snake = insere(snake, 25, 15);
        snake = insere(snake, 26, 15);
        snake = insere(snake, 27, 15);
        snake = insere(snake, 28, 15);
        snake = insere(snake, 29, 15);
        int nFoodX = 10;
        int nFoodY = 15;
        nScore = 0;
        int nSnakeDirection = 1;
        bDead = 0;
        aDead = 0;
        int bKeyLeft = 0, bKeyRight = 0, bKeyLeftOld = 0, bKeyRightOld = 0;

        while(aDead!=2 && bDead!=1)
        {
            fflush(stdin);
            bKeyRight = (0x8000 & GetAsyncKeyState((unsigned char)('\x27'))) != 0;
            bKeyLeft = (0x8000 & GetAsyncKeyState((unsigned char)('\x25'))) != 0;

            if (bKeyRight && !bKeyRightOld)
            {
                nSnakeDirection++;
                if (nSnakeDirection == 4)
                    nSnakeDirection = 0;
            }

            if (bKeyLeft && !bKeyLeftOld)
            {
                nSnakeDirection--;
                if (nSnakeDirection == -1)
                    nSnakeDirection = 3;
            }

            bKeyRightOld = bKeyRight;
            bKeyLeftOld = bKeyLeft;

            //Lógica do jogo | movimento
            switch (nSnakeDirection)
            {
            case 0: // UP
                snake = insere(snake, snake->x, snake->y-1);
                break;
            case 1: // RIGHT
                snake = insere(snake, snake->x+1, snake->y);
                break;
            case 2: // DOWN
                snake = insere(snake, snake->x, snake->y+1);
                break;
            case 3: // LEFT
                snake = insere(snake, snake->x-1, snake->y);
                break;
            }
            // Deslocamento ao cortar o rabo da cobra
            pop_back(snake);

            // Colisão Cobra X Food | Gerar novo Food
            if (snake->x == nFoodX && snake->y == nFoodY)
            {
                nScore++;
                srand(time(NULL));
                while(dentro(snake,nFoodX,nFoodY)==1)
                {
                    nFoodX = (rand() % nScreenWidth);
                    if(nFoodX==0)
                        nFoodX=1;
                    nFoodY = (rand() % nScreenHeight);
                    if(nFoodY==0 || nFoodY==1)
                        nFoodY = 2;
                }
                for (int i = 0; i < 3; i++)
                    snake = push_back(snake, ultimo_x(snake), ultimo_y(snake));
            }
            //Colisão Cobra x Parede
            aDead = colisao_parede(snake);

            // Ourobouros
            bDead = ourobouros(snake);

            // Desenhar Snake na tela
            desenha_snake(snake);

            // Desenha Food
            GotoXY(nFoodX, nFoodY);
            printf("F");

            // Frame Timing
            Sleep(33);

            // Screen Buffer
            Boarder(snake);
        }
    }
    return 0;
}
