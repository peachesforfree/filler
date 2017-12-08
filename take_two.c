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
                fil->piece_left = x;
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
    int     tmp;

    tmp = 1;
    while (get_next_line(fil->fd, &line))     //while there is something to read
    {
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
                return (1);                
            }
		}
		if (ft_isdigit(line[0]))                //for reading of the board, because of GNL the *line is null terminated
		{
		    fil->board[ft_atoi(line)] = ft_strdup(ft_strchr(line, ' ') + 1);		
		}
		ft_bzero(line, sizeof(line));
	}
    return (0);
}

int main(void)
{
    t_fil fil;

    fil_init(&fil);
    while (get_board(&fil))
    {
        dprintf(2, ">\tplayer[%c]\tboard[%i][%i]\tpiece[%i][%i]\n",fil.me, fil.board_y, fil.board_x, fil.piece_y, fil.piece_x);
        //for testing printf all the shit out to FD of 2
        //algo goes here for placement
        dprintf(1, "0 0\n");
    }
    
    return (0);
}