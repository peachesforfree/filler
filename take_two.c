#include <unistd.h>
#include <stdio.h>
#include "./libft/libft.h"

typedef struct  s_fil
{
    char        me;
    char        him;
    int         fd;
    
    char        **board;
    int         board_x;
    int         board_y;
    
    char         **piece;
    int         piece_y;
    int         piece_x;
    int         piece_left;
    int         piece_right;
    int         piece_top;
    int         piece_bottom;
    int         count_y;

    int         x_place;
    int         y_place;

    int		put_piece_x;
	int		put_piece_y;

    int     **heat_map;
	int		current_x;
	int		current_y;

}               t_fil;

void    fil_init(t_fil *fil)
{
    fil->board_x = 0;
    fil->board_y = 0;
    fil->me = 0;
    fil->him = 0;
    fil->fd = 0;
    fil->board = NULL;
    fil->piece_x = 0;
    fil->piece_y = 0;
    fil->count_y = 0;
    fil->piece_left = 0;
    fil->piece_right = 0;
    fil->piece_top = 0;
    fil->piece_bottom = 0;
    fil->x_place = 0;
    fil->y_place = 0;
    fil->put_piece_x = 0;
    fil->put_piece_y = 0;
}

void        print_coordinates(t_fil *fil)
{
    ft_putnbr(fil->put_piece_x);
    ft_putchar(' ');
    ft_putnbr(fil->put_piece_y);
    ft_putchar('\n');
}

/*
**void  player_info(t_fil *fil, char *str)
**
**assuming string is "$$$ exec p1 : [./filler]"
**where the number after 'p' can be 1 or two
*/

void    player_info(t_fil *fil, char *str)
{
    char *chr;

    chr = ft_strchr(str, 'p');
    fil->me = (chr[1] == '1') ? 'O' : 'X';
	fil->him = (chr[1] == '1') ? 'X' : 'O';
}

/*
**void    board_size(t_fil *fil, char *str)
**
**assuming str is "Plateau 24 40:
**first number is board_Y and second is board_X
**also allocated memory pointers for the board to be filled in
*/

void    board_size(t_fil *fil, char *str)
{
    char    *chr;

    chr = ft_strchr(str, ' ');
    chr++;
    fil->board_y = ft_atoi(&chr[0]);
    while(ft_isdigit(chr[0]))
        chr++;
    while(!ft_isdigit(chr[0]))
        chr++;
    fil->board_x = ft_atoi(&chr[0]);
    fil->board = (char**)malloc(sizeof(char*) * fil->board_y);
}

/*
**void    piece_size(t_fil * fil, char *str)
**
**this assumes "Piece 2 1:" within str
**first number is the piece_y and second is piece_x
**also allocates char* pointers for saving the piece
*/

void    piece_size(t_fil * fil, char *str)
{
    char *chr;

    chr = ft_strchr(str, ' ');
    chr++;
    fil->piece_y = ft_atoi(&chr[0]);
    while(ft_isdigit(chr[0]))
        chr++;
    while(!ft_isdigit(chr[0]))
        chr++;
    fil->piece_x = ft_atoi(&chr[0]);
    fil->piece = (char**)malloc(sizeof(char*) * fil->piece_y);
}

/*
**int     get_piece(t_fil *fil, char *line)
**
**has its own counter counting down the
**number of lines untill @ end of reading
**the piece line by line
*/

int     get_piece(t_fil * fil, char *line)
{
    if (fil->count_y < fil->piece_y)
    {
        fil->piece[fil->count_y] = ft_strdup(line);
        fil->count_y++;
        if (fil->count_y == fil->piece_y)
            return (1);
        return (0);
    }
    return (0);
}

/*
**void    get_left_bound(t_fil *fil)
**
**gets left most bound of the piece
*/

void    get_left_bound(t_fil *fil)
{
    int x;
    int y;

    x = 0;
    y = 0;
    while (x < fil->piece_x)
    {
        while (y < fil->piece_y)
        {
            if (fil->piece[y][x] == '*')        
            {
                fil->piece_left = x;
                return ;
            }
            y++;
        }
        y = 0;
        x++;
    }
}

/*
**void    get_right_bound(t_dil *fil)
**starts rights from right, top to bottom
**if '*' is found, return x location
*/

void    get_right_bound(t_fil *fil)
{
    int x;
    int y;

    y = 0;
    x = fil->piece_x;
    while (x >= 0)
    {
        while (y < fil->piece_y)
        {
            if (fil->piece[y][x] == '*')
            {
                fil->piece_right = x;
                return ;
            }
            y++;
        }
        x--;
        y = 0;
    }
}


/*
**void    get_top_bound(t_fil *fil)
**
**scans piece from left to right
**from top to bottom looking for '*'
**setting fil->piece_top as top most bound
*/

void    get_top_bound(t_fil *fil)
{
    int x;
    int y;

    x = 0;
    y = 0;
    while (y < fil->piece_y)
    {
        while (x < fil->piece_x)
        {
            if (fil->piece[y][x] == '*')
            {
                fil->piece_top = y;
                return ;
            }
            x++;
        }
        y++;
        x = 0;
    }
}

/*
**void    get_bottom_bound(t_fil *fil)
**
**from left to right starting from bottom to top
**scans the piece for '*'
*/

void    get_bottom_bound(t_fil *fil)
{
    int x;
    int y;

    y = (fil->piece_y - 1);
    x = 0;
    while (y >= 0)
    {
        while(x <= fil->piece_x)
        {
            if (fil->piece[y][x] == '*')
            {
                fil->piece_bottom = y;
                return ;
            }
            x++;
        }
        y--;
        x = 0;
    }
}

/*
**void    get_mini_stats(t_fil *fil, char *str)
**
**this extracts data from the piece.
**upper, bottom, left and right bound.
*/

void    get_mini_stats(t_fil *fil)
{
    get_left_bound(fil);
    get_right_bound(fil);
    get_top_bound(fil);
    get_bottom_bound(fil);
}

/*
**int     get_board(t_fil *fil)
**
**pulls out all data and board 
**also the piece and related data
*/

int     get_board(t_fil *fil)
{
    char *line;

    while (get_next_line(fil->fd, &line))     //while there is something to read
    {
        //dprintf(2, ">\t%s\n", line);
       if (ft_strstr(line, "$$$"))      //indicator for which player I am
        	player_info(fil, line);
        if (ft_strstr(line, "Plateau")) //indicator for board dimentions
			board_size(fil, line);
		if (ft_strstr(line, "Piece"))   //for piece dimentions 
			piece_size(fil, line);
		if ((line[0] == '*' || line[0] == '.')) //knowing when reading of the piece takes place
		{
			if (get_piece(fil, line))           //reading of the whole piece
            {
                get_mini_stats(fil);
                fil->count_y = 0;
                return (1);                
            }
		}
		if (ft_isdigit(line[0]))                //for reading of the board, because of GNL the *line is null terminated
		{
		    fil->board[ft_atoi(line)] = ft_strdup(ft_strchr(line, ' ') + 1);		
		}
		ft_bzero(line, sizeof(line));
    }
    fil->count_y = 0;
    return (0);
}

/*
**void    printf_heat_map(int **heat, int x_bound, int y_bound)
**
**this is only for debugging to show how the heat map is populating
*/

void    printf_heat_map(int **heat, int x_bound, int y_bound)
{
    int x;
    int y;
    y = -1;
    while(++y < y_bound)
    {
        x = -1;
        while (++x < x_bound)
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

    heat_map = (int**)ft_calloc(y_board, (x_board * sizeof(int)));
    y = -1;
    while (++y < y_board)
    {
        x = -1;
        while (++x < x_board)
        {
            if (board[y][x] == him)
                heat_map[y][x] = 1;
        }
    }
    fill_heat_map(board, heat_map, x_board, y_board);
    printf_heat_map((int**)heat_map, x_board, y_board); //for debugging    
    return (heat_map);
}

/*
**void        buffer_zone_filled(t_fil *fil)
**
**given the current map, if the DMZ zone is filled, the function returns 1
**if the DMZ zone is not filled in, function reurns 0
**DMZ zone is determined by 10% of the board width or fil->board_x value
*/

void        buffer_zone_check(t_fil *fil)
{
    int number;
    int x;
    int y;

    y = -1;
    number = ((fil->board_x * 10) / 100);
    while (++y < fil->board_y)
    {
        x = -1;
        while (++x < fil->board_x)
        {
            if (fil->heat_map[y][x] == number && fil->board[y][x] == fil->me)
                return (0);
        }
    }
    return (1);
}

/*
**void        not_near_buffer(t_fil *fil)
**
**checks heat map for DMZ zone and IF fil->me
**if on the same place on the board. if true, return 1
*/

void        not_near_buffer(t_fil *fil)
{
    int number;
    int x;
    int y;
    bool place;

    y = -1;
    place = false;
    number = ((fil->board_x * 10) / 100);
    while (++y < fil->board_y)
    {
        x = -1;
        while (++x < fil->board_x)
        {
            if (fil->heat_map[y][x] == number && fil->board[y][x] == fil->me)
                place = true;
        }
    }
    if (place == true)
        return (0);
    return (1);
}

/*
**t_list        *add_to_list(int x, int y, t_list *head, int heat_number)
**
**given x,y coord, head node, and heat_number
**t_list is made with the string of "x y\n" and heat number in content size
*/

t_list        *add_to_list(int x, int y, t_list *head, int heat_number)
{
    t_list *temp;

    temp = ft_lstnew(printf("%i %i\n", y, x), heat_number);
    temp->next = head;
    return (temp);
}

//
//      tke off from here
//      trying to build a functiom that runns thru the nodes and chooses the one with the 
//      largest content size and take those coordinates and places them into
//      fil->put_piece_x and fil->put_piece_y

void        asses_places(t_fil *fil, t_list *head)
{
    t_list *current;
    t_list *best_value;

    while (current->next != NULL)
    {

    }
}

void        work_towards_buffer_zone(t_fil * fil)
{
    t_list *places;
    int x;
    int y;

    y = -1;
    while (++y < fil->board_y)
    {
        x = -1;
        while (++x < fil->board_x)
        {
            if(bounds_check(fil, x, y) && check_mine(fil, x, y) && check_his(fil, x, y))
            {
                places = add_to_lst(x, y, palces, fil->heat_map[y][x]);
            }
        }
    }
    asses_placement(fil, palces);
}

void        placement_start(t_fil &fil)
{
    if (buffer_zone_check(&fil))
        fil_rest_of_map(&fil);
    else if (!buffer_zone_check(&fil))
        wall_off_buffer_zone(&fil);
    else if (not_near_buffer(&fil))
        work_towards_buffer_zone(&fil);
}

int         main(void)
{
    t_fil fil;

    fil_init(&fil);
    fil.fd = open("test.txt", O_RDONLY); //for reading the test file
    while (get_board(&fil))
    {
        fil.heat_map = heat_map_init(fil.board, fil.board_x, fil.board_y, fil.him);
        placement_start(&fil);
        print_coordinates(&fil);
    }
    return (0);
}