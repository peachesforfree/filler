#include "./libft/libft.h"
#include <stdio.h>


void    printf_heat_map(int **heat)
{
    int x;
    int y;
    y = -1;
    while(++y < 10)
    {
        x = -1;
        while (++x < 10)
        {
            printf(" %i ", heat[y][x]);
        }
        printf("\n");
    }
    printf("\n");
}

/*
**int     sweep_check(int **heat_map, int number)
**
**this checks the heat_map for the special number given, if not found, returns one
**if number is not found, returns zero
*/

int     sweep_check(int **heat_map, int number, int x_bound, int y_bound)
{
    int x;
    int y;

    y = -1;
    while (++y < y_bound)
    {
        x = -1;
        while (++x < x_bound)
        {
            if (heat_map[y][x] == number)
                return (1);
        }
    }
    return (0);
}

/*
**void    fill_heat_map(char **board, int  **heat_map, int x_board, int y_board)
**
**runs thru map while laying down one number at a time
*/

void    fill_heat_map(char **board, int  **heat_map, int x_board, int y_board)
{
    int y;
    int x;
    int number;

    number = 1;
    while (++number && sweep_check(heat_map, 0, x_board, y_board))
    {
        printf_heat_map((int**)heat_map);
        
        y = -1;
        while (++y < y_board)
        {
            x = -1;
            while (++x < x_board)
            {
                    if ((x - 1) > 0 && heat_map[y][x - 1] == (number - 1) && heat_map[y][x] == 0) //checks left
                        heat_map[y][x] = number;
                    if ((x + 1) < (x_board - 1) && heat_map[y][x + 1] == (number - 1) && heat_map[y][x] == 0) //checks right
                        heat_map[y][x] = number;
                    if ((y - 1) > 0 && heat_map[y - 1][x] == (number - 1) && heat_map[y][x] == 0) //checks below
                        heat_map[y][x] = number;
                    if ((y + 1) < (y_board - 1) && heat_map[y + 1][x] == (number - 1) && heat_map[y][x] == 0) //checks above
                        heat_map[y][x] = number;
            }
        }
    }
} 

/*
**int     **heat_map(char **board, int x_board, int y_board, char him)
**
**this inits the 2d int array and places in the values for the opponent.
*/

int     **heat_map_init(char **board, int x_board, int y_board, char him)
{
    int **heat_map;
    int  x;
    int y;

    heat_map = (int**)ft_calloc(y_board, x_board * sizeof(int));
    y = -1;
    x = -1;
    while (++y < y_board)
    {
        while (++x < x_board)
        {
            if (board[y][x] == him)
                heat_map[y][x] = 1;
        }
        x = -1;
    }
    fill_heat_map(board, heat_map, x_board, y_board);
    return (heat_map);
}


int main(void)
{
    const char *board[10] = {"..........", "..........", "..X.......", "..........", "..........", "..........", "......OO..", ".......O..", ".......O..", ".........."};

    int **heat;
    char **map;

    heat = heat_map_init((char **)board, 10, 10, 'O');
    //print heat map
    printf_heat_map(heat);
    return (0);
}