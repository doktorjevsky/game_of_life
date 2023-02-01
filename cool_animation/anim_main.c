
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "game_of_life.h"
#include <Windows.h>

#define TRUE 1
#define FALSE 0


void render();
char paint_cell(int c);
struct gol * init_game(int size);
double get_double_cps(clock_t t1, clock_t t0);
void update();
DWORD WINAPI run(void* data);


int RUNNING = TRUE;
struct gol GAME;

int main()
{
    system("cls");
    int size = 20;
    GAME = *init_game(size);
    
    HANDLE thread = CreateThread(NULL, 0, run, NULL, 0, NULL);
    int var;
    while(RUNNING && thread)
    {
        scanf("%d", &var);
        if (var == -1)
        {
            RUNNING = FALSE;
        }
        GAME.world[var % size*size] = 1;
    }
    
    return 0;
}


DWORD WINAPI run(void* data)
{
    DWORD last = GetTickCount();
    DWORD dt = 500;
    DWORD current;
    int cnt = 0;
    while (RUNNING)
    {
        current = GetTickCount();
        if (current - last >= dt)
        {
            cnt = (cnt + 1) % 2;
            render();
            current = last;
        }
        if (cnt == 0)
        {
            update();
        }

    }
    return 0;
}

struct gol * init_game(int size)
{
    srand(GetTickCount());
    struct gol *game = new_world(size, size);
    for (int i = 0; i < size * size; i++)
    {
        game->world[i] = 1;
        if ((rand() % 3) < 1)
        {
            game->world[i] = 0;
        }
    }
    
    return game;
    
}

void render()
{
    int *w = GAME.world;
    system("cls");
    for (int i = 0; i < GAME.rows; i++)
    {
        for (int j = 0; j < GAME.cols; j++)
        {
            printf("%c", paint_cell(w[i*GAME.rows + j]));
        }
        printf("\n");
    }
}

void update()
{
    struct gol *temp = next_state(&GAME);
    destroy(&GAME);
    GAME = *temp;

}

char paint_cell(int c)
{
    if (c)
    {
        return '#';
    } 
    else 
    {
        return ' ';
    }
}

