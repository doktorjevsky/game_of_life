
struct gol
{
    int rows;
    int cols;
    int * world;
};

struct gol * new_world(int rows, int cols);
struct gol * get_copy(struct gol * game);
struct gol * next_state(struct gol * game);
int next_cell_state(int x, int y, struct gol * game);
int alive_nbors(int x, int y, struct gol * game);
int in_bounds(int x, int y, struct gol * game);
void destroy(struct gol * game);
