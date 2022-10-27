#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <conio.h>
#include <ctype.h>
#include <windows.h>
#include <process.h>

#include "func.h"
//Cabeça da cobrinha fica no inicio da lista. Para se mover, se é inserido uma nova cabeça e remove-se o ultimo elemento.

int bDead;//chegagem b
int aDead;//checagem a
int nScore;
int nScreenWidth = 72;
int nScreenHeight = 18;

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
