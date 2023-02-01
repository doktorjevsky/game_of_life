

#include "game_of_life.h"
#include <stdio.h>
#include <stdlib.h>

#define PASS "PASS"
#define FAIL "FAIL"

int test1();
int test2();
int test3();
int test4();
int test5();
int test6();
int test7();
int test8();
int test9();
int test10();
int test11();
int arr_eq(int * a1, int * a2, int nn);
char * result(int x);

int main()
{
    printf("*** UNIT TESTS ***\n");
    printf("Test 1 :: Expected: %d  Actual: %d Result: %s\n", 1, test1(), result(test1()));
    printf("Test 2 :: Expected: %d  Actual: %d Result: %s\n", 1, test2(), result(test2()));
    printf("Test 3 :: Expected: %d  Actual: %d Result: %s\n", 1, test3(), result(test3()));
    printf("Test 4 :: Expected: %d  Actual: %d Result: %s\n", 1, test4(), result(test4()));
    printf("Test 5 :: Expected: %d  Actual: %d Result: %s\n", 1, test5(), result(test5()));
    printf("Test 6 :: Expected: %d  Actual: %d Result: %s\n", 1, test6(), result(test6()));
    printf("Test 7 :: Expected: %d  Actual: %d Result: %s\n", 1, test7(), result(test7()));
    printf("Test 8 :: Expected: %d  Actual: %d Result: %s\n", 1, test8(), result(test8()));
    printf("Test 9 :: Expected: %d  Actual: %d Result: %s\n", 1, test9(), result(test9()));
    printf("Test 10 :: Expected: %d  Actual: %d Result: %s\n", 1, test10(), result(test10()));
    printf("Test 11 :: Expected: %d  Actual: %d Result: %s\n", 1, test11(), result(test11()));

    

    return 0;
}

char * result(int x)
{
    if (x)
    {
        return PASS;
    }
    return FAIL;
}

int arr_eq(int * a1, int * a2, int nn)
{
    for (int i = 0; i < nn; i++)
    {
        if (a1[i] != a2[i])
        {
            return 0;
        }
    }
    return 1;
}

// initial array is null array
int test1()
{
    struct gol *g = new_world(2,2);
    int * w = g->world;
    int * exp = calloc(4, sizeof(int));
    int res = arr_eq(w, exp, 4);
    free(exp);
    destroy(g);

    return res;
}

// initial array is null array
int test2()
{
    struct gol *g = new_world(10, 10);
    int * w = g->world;
    int * exp = calloc(100, sizeof(int));
    int res = arr_eq(w, exp, 100);
    free(exp);
    destroy(g);
    return res;
}

// tests equality after copy
int test3()
{
    struct gol *g = new_world(2,2);
    struct gol *g_cop = get_copy(g);
    int * original = g->world;
    int * copy = g_cop->world;
    int res = arr_eq(original, copy, 4);
    res &= (g_cop->cols == g->cols && g_cop->rows == g->rows);
    destroy(g);
    destroy(g_cop);
    return res;
}

// mutation of copy doesn't mutate original object
int test4()
{
    struct gol *g = new_world(2, 2);
    struct gol *g_cop = get_copy(g);
    // equal before
    int res = arr_eq(g->world, g_cop->world, 4);
    g_cop->world[0] = 1;
    // not equal after
    res &= !arr_eq(g_cop->world, g->world, 4);
    destroy(g);
    destroy(g_cop);
    return res;
}

// mutation testing 2
int test5()
{
    struct gol *g = new_world(2,2);
    struct gol *g_cop = get_copy(g);
    int res = g->cols == g_cop->cols;
    g_cop->cols = 5;
    res &= (g->cols != g_cop->cols);
    destroy(g);
    destroy(g_cop);
    return res;
}


// alive nbors test: doesn't count itself
int test6()
{
    struct gol *g = new_world(2,2);
    g->world[0] = 1;
    g->world[1] = 1;
    int res = alive_nbors(0,0,g);
    destroy(g);
    return res == 1;
}

// alive nbors test2: all dead
int test7()
{
    struct gol *g = new_world(2,2);
    int res = 1;
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            res &= (alive_nbors(i, j, g) == 0);
        }
    }
    destroy(g);
    return res;
}


// nbor count
int test8()
{
    struct gol *g = new_world(3,3);
    int * w = g->world;
    w[2] = 1;
    w[8] = 1;
    w[4] = 1;
    int res = alive_nbors(1, 1, g);
    destroy(g);
    return res == 2;
}


// next state for a living cell
int test9()
{
    struct gol *g = new_world(3,3);
    int *w = g->world;
    w[2] = 1;
    w[8] = 1;
    w[4] = 1;
    int res = next_cell_state(1, 1, g);
    return res == 1;
}

// next state for a dead cell
int test10()
{
    struct gol *g = new_world(3,3);
    int *w = g->world;
    w[2] = 1;
    w[3*2 + 2] = 1;
    w[3*1 + 1] = 1;
    int res = next_cell_state(2,1,g);
    return res == 1;
}

// next state for a grid

/*
 0 1 1
 0 1 0
 1 0 0

 0 1 1
 1 1 1
 0 1 0
*/
int test11()
{
    struct gol *g = new_world(3,3);
    struct gol *ptr_g = g;
    int *w = g->world;
    w[2] = 1;
    w[1] = 1;
    w[6] = 1;
    w[4] = 1;

    g = next_state(g);
    destroy(ptr_g);

    int *exp = calloc(9, sizeof(int));
    exp[1] = 1;
    exp[2] = 1;
    exp[3] = 1;
    exp[4] = 1;
    exp[5] = 1;
    exp[7] = 1;

    int res = arr_eq(w, exp, 9);
    destroy(g);
    free(exp);
    return res;
}



 