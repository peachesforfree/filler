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

int         check_mine(t_fil *fil, int x, int y)
{
    //dprintf(2, "\tcheck mine start");
    int xx;
    int yy;
    int count;

    count = 0;
    yy = -1;
    xx = -1;
    while (++yy < fil->piece_y)
    {
        while (++xx < fil->piece_x)
        {
            if ((fil->piece[yy][xx] == '*') && (fil->board[y + yy][x + xx] == fil->me))
             {
                // dprintf(2, ">\tonboard[%i][%i]\tonpiece[%i][%i]", y, x, yy, xx);
                 //dprintf(2, ">\tminefound@ \t%i\t%i\tcount=%i\n", (y + yy), (x + xx), (count + 1));
                count++;
             }
        }
        xx = -1;
    }
    if (count != 1)
        return (0);
    return (1);
}

int         check_his(t_fil *fil, int x, int y)
{
    dprintf(2, "\tcheck his start");
    int xx;
    int yy;

    xx = -1;
    yy = -1;
    while (++yy < fil->piece_y && (yy + y < fil->board_y))
    {
        while (++xx < fil->piece_x && (xx + x < fil->board_x))
        {
            if ((fil->board[y + yy][x +xx] == fil->him) && (fil->piece[yy][xx] == '*'))
            {
                //dprintf(2, "hisfound@\t%i\t%i\n", (yy + y), (xx + x));
                return (0);
            }
        }
        xx = -1;
    }
    return (1);
}

int         bounds_check(t_fil *fil, int x, int y)
{
    //dprintf(2, "\tbounds check start");
    if ((y + fil->piece_bottom) >= fil->board_y)
        return (0);
    if ((x + fil->piece_right) >= fil->board_x)
        return (0);
    return (1);
}

int        up_and_left(t_fil *fil)        //scans from top left
{
    int x;
    int y;

    x = -1;
    y = -1;
   
    while (++y < fil->board_y) //takes into account the bottom bound
    {
        while (++x < fil->board_x)  //takes into account the far right bound
        {
            if(bounds_check(fil, x, y) && check_mine(fil, x, y) && check_his(fil, x, y))
            {
                fil->x_place = x;
                fil->y_place = y;
                return (1);                    
            }
        }
        x = -1;
    }
    return (0);
}

int        up_and_right(t_fil *fil)       //scans from top right
{
    int x;
    int y;

    x = fil->board_x;
    y = -1;
   
    while (++y < fil->board_y) //takes into account the bottom bound
    {
        while (--x > -1)  //takes into account the far right bound
        {
            if(bounds_check(fil, x, y) && check_mine(fil, x, y) && check_his(fil, x, y))
            {
                fil->x_place = x;
                fil->y_place = y;
                return (1);                    
            }
        }
        x = fil->board_x;
    }
    return (0);
}

int        from_bottom_left(t_fil *fil) //scans from bottom left
{
    int x;
    int y;

    x = -1;
    y = fil->board_y;
   
    while (--y > -1) //takes into account the bottom bound
    {
        while (++x > fil->board_x)  //takes into account the far right bound
        {
            if(bounds_check(fil, x, y) && check_mine(fil, x, y) && check_his(fil, x, y))
            {
                fil->x_place = x;
                fil->y_place = y;
                return (1);                    
            }
        }
        x = -1;
    }
    return (0);
}

int        from_bottom_right(t_fil *fil)    //scans from bottom right 
{
    int x;
    int y;

    x = fil->board_x;
    y = fil->board_y;
   
    while (--y > -1) //takes into account the bottom bound
    {
        while (--x > -1)  //takes into account the far right bound
        {
            if(bounds_check(fil, x, y) && check_mine(fil, x, y) && check_his(fil, x, y))
            {
                fil->x_place = x;
                fil->y_place = y;
                return (1);                    
            }
        }
        x = fil->board_x;
    }
    return (0);
}

int         up_down(t_fil *fil)
{
    int x;
    int y;
    int place;

    y = -1;
    x = -1;
    while (++y < fil->board_y)
    {
        while (++x < fil->board_x)
        {
            if (fil->board[y][x] == fil->me)
                count = y;
        }
        x = -1;
    }
    if (count < (fil->board_y / 2))
        return (1);
    return (-1);
}

int         left_right(t_fil *fil)
{
    int x;
    int y;
    int place;

    x = -1;
    y = -1;
    place = -1;
    while (++y < fil->board_y)
    {
        while (++x < fil->board_x)
        {
            if ((fil->board[y][x] == fil->me) && (place < x))
                place = x;
        }
        x = -1;
    }
    if (place < (fil->board_x / 2))
        return (1);
    return (-1);
}

int        find_place(t_fl *fil, int x_vec, int y_vec)
{
    //x_vec == -1 right if 1 left
    //y_vec == -1 down if 1 up
    if (x_vec < 0 && y_vec < 0)             //player resides in right bottom
        return (from_bottom_left(fil));
    if (x_vec < 0 && y_vec > 0)
        return (from_bottom_right(fil));    //player resides in right top 
    if (x_vec > 0 && y_vec < 0)
        return (from_top_right(fil));       //player resides in left bottom
    if (x_vec > 0 && y_vec > 0)
        return (from_top_left(fil));        //player resides in left top
}

int         bolt_for_center(t_fil *fil)
{
    int x_vector;
    int y_vector;

    y_vector = up_down(fil);       //will return +1 or -1 depending on going up or down
    x_vector = left_right(fil);   //will return +1 or -1 depending on going left or right
    if (fil->board[fil->board_y / 2][fil->board_x / 2] != fil->me ||
    fil->board[(fil->board_y / 2) + 1][fil->board_x / 2] != fil->me ||
    fil->board[(fil->board_y / 2) - 1][fil->board_x / 2] != fil->me ||
    fil->board[fil->board_y / 2][(fil->board_x / 2) + 1] != fil->me ||
    fil->board[fil->board_y / 2][(fil->board_x / 2) - 1] != fil->me)    // maybe make this into a looped function where it checks in radius from selected point
        return ((find_place(fil, x_vector, y_vector) > 0) ? 1: 0);
    return (0);
}

int     find_spot_near(t_fil *fil, int x, int y)        //here I need do devise a way to scan in a radius around the point given in arguments x,y
{
    int rad;
    int count;

    rad = -1;
    while (++rad;)
    {
        count = (rad / 2);
        while(y + count)
        {
            while(x + )
            {

            }
        }
    }
}

int        spread_from_center(t_fil fil)
{
    if (find_spot_near(fil, x, y))

}

int         fill_out_from_center(fil)
{

}

int         main(void)
{
    t_fil fil;

    fil_init(&fil);
    //fil.fd = open("test.txt", O_RDONLY); //for reading the test file
    while (get_board(&fil))
    {
        if (bolt_for_center(fil))
            dprintf(2, "%i %i\n", fil.y_place, fil.x_place);
        else if (spread_from_center(fil))
            dprintf(2, "%i %i\n", fil.y_place, fil.x_place);
        else if (fill_out_from_center(fil))
            dprintf(2, "%i %i\n", fil.y_place, fil.x_place);
        else
            dprintf(2, "0 0\n");
    }
    return (0);
}