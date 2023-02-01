

#include "game_of_life.h"
#include <stdlib.h>

#define DEAD 0
#define ALIVE 1



// returns a blank slate
struct gol * new_world(int rows, int cols)
{
    struct gol *g;
    int * world = calloc(rows * cols, sizeof(int));
    g = malloc(sizeof(struct gol));
    g->cols = cols;
    g->rows = rows;
    g->world = world;
    return g;
}

/*
  Precondition: gol object has a n*n dimensioned world
  Postcondition: Changes in copy doesn't mutate the original object
*/
struct gol * get_copy(struct gol * game)
{
    struct gol * g_copy = new_world(game->rows, game->cols);
    int * w_copy = g_copy->world;
    for (int i = 0; i < game->rows * game->cols; i++)
    {
        w_copy[i] = game->world[i];
    }
    return g_copy;
}


/*
  Returns the next state in a new adress
*/
struct gol * next_state(struct gol * game)
{
    struct gol * g_new = new_world(game->rows, game->cols);
    int x = game->cols;
    int y = game->rows;
    for (int i = 0; i < y; i++)
    {
        for (int j = 0; j < x; j++)
        {
            g_new->world[i * y + j] = next_cell_state(j, i, game);
        }
    }
    return g_new;

}

/*
If the cell is alive, then it stays alive if it has either 2 or 3 live neighbors

If the cell is dead, then it springs to life only in the case that it has 3 live neighbors
*/

int next_cell_state(int x, int y, struct gol * game)
{
    int alive_nb = alive_nbors(x, y, game);
    if (game->world[y*game->rows + x] == ALIVE)
    {
        return alive_nb == 2 || alive_nb == 3;
    } 
    else 
    {
        return alive_nb == 3;
    }
}

// for counting alive nbors around a given cell
int alive_nbors(int x, int y, struct gol * game)
{
    int alive_nb = 0;
    for (int i = -1; i <= 1; i++)
    {
        for (int j = -1; j <= 1; j++)
        {
            if (in_bounds(x + j, y + i, game) && !(i == 0 && j == 0))
            {
                alive_nb += game->world[game->rows * (y + i) + x + j];
            }
        }
    }
    return alive_nb;
}

// returns 1 if (x, y) is within bounds
int in_bounds(int x, int y, struct gol * game)
{
    return 0 <= x && x < game->cols && 0 <= y && y < game->rows;
}

void destroy(struct gol *g)
{
    free(g->world);
    free(g);
    g = NULL;
}