#ifndef FUNC_H_INCLUDED
#define FUNC_H_INCLUDED

typedef struct sSnakeSegment
{
    int x;
    int y;
    struct sSnakeSegment* prox;
} Snake;


Snake* inicializa (void);

Snake* insere (Snake* l, int x1, int y1);

void GotoXY(int x, int y);

void Boarder(Snake* snake);

void pop_back(Snake* l);

int ultimo_x(Snake* l);

int ultimo_y(Snake* l);

Snake* push_back(Snake* l, int ultimo_x, int ultimo_y);

int ourobouros(Snake* snake);

int colisao_parede(Snake* snake);

void reset();

int dentro(Snake* snake, int food_x, int food_y);

void menu();

void desenha_snake(Snake* snake);


#endif // FUNC_H_INCLUDED
