#include <stdio.h>
#include "./libft/libft.h"
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

typedef struct       s_fil
{
    char    me;
    char    him;
    int     fd;
    
    char    **board;
    int     board_x;
    int     board_y;
   
    char    **piece;
    int     count_y;
    int     piece_x;
    int     piece_y;
    int     x_left;
    int     x_len;
    int     y_top;
    int     y_len;   
    char    **mini_piece;
    int		put_piece_x;
	int		put_piece_y;
	int		**heat_map;
	int		current_x;
	int		current_y;
}                   t_fil;

void    init_struct(t_fil *fil)
{
    fil->me = 0;
    fil->him = 0;
    fil->fd = 0;
    fil->board = NULL;
    fil->board_x = 0;
    fil->board_y = 0;
    fil->piece = NULL;
    fil->piece_x = 0;
    fil->piece_y = 0;
    fil->x_left = 0;
    fil->x_len = 0;
    fil->y_top = 0;
    fil->y_len = 0;
    fil->put_piece_x = 0;
    fil->put_piece_y = 0;
    fil->count_y = 0;
	fil->current_x = 0;
	fil->current_y = 0;
}

void    player_info(t_fil *fil, char *line)
{
    char	*chr;

	chr = ft_strchr(line, 'p');
	fil->me = (chr[1] == '1') ? 'O' : 'X';
	fil->him = (chr[1] == '1') ? 'X' : 'O';
}

void	piece_size(t_fil *fil, char *line)
{
	int i;

	i = 0;
	while (!ft_isdigit(line[i]))
		i++;
	fil->piece_y = ft_atoi(&line[i]);
	while (ft_isdigit(line[i]))
		i++;
	while (!ft_isdigit(line[i]))
		i++;
	fil->piece_x = ft_atoi(&line[i]);
	fil->piece = (char**)ft_memalloc(sizeof(char*) * (fil->piece_y + 1));
    fil->piece[fil->piece_y] = NULL;
}

void		board_size(t_fil *fil, char *line)
{
	int		i;

	i = 0;
	while (!ft_isdigit(line[i]))
		i++;
	fil->board_y = ft_atoi(&line[i]);
	while (ft_isdigit(line[i]))
		i++;
	while (ft_isspace(&line[i]))
        i++;
	fil->board_x = ft_atoi(&line[i]);       
	fil->board = (char**)ft_memalloc((fil->board_y + 1) * sizeof(char*));
    fil->board[fil->board_y] = NULL;
}

int     get_piece(t_fil *fil, char *line)
{
	dprintf(2, ">\t%s\t# = %i\n", line, fil->count_y);
    if(fil->count_y < fil->piece_y)
		fil->piece[fil->count_y] = ft_strdup(line);
	fil->count_y++;
	if (fil->count_y == (fil->piece_y))
	{
		fil->count_y = 0;
	    return (1);
	}
	return (0);
}

int			from_left(t_fil *fil)
{
	int x;
	int y;
	
	x = 0;
	while (x < fil->piece_x)
	{
		y = 0;
		while (y < fil->piece_y)
		{
//		dprintf(2, ">fil->piece[%i][%i] = %c \n", y, x, fil->piece[y][x]);
			if (fil->piece[y][x] == '*')
				return (x);
			y++;
		}
		x++;
	}
	return (0);
}

int			from_right(t_fil *fil)
{
	int x;
	int y;
	int	counter;

	counter = 1;
	x = fil->x_left;
	while (x < fil->piece_x)
	{
		y = fil->y_top;
		while (y < fil->piece_y)
		{
			if ((fil->piece[y][x] == '*') && (x >= counter))
				counter = x;
			y++;
		}
		x++;
	}
	return (counter);
}

int			from_top(t_fil *fil)
{
	int x;
	int y;
	
	y = -1;
	while (++y < fil->piece_y)
	{
		x = -1;
		while (++x < fil->piece_x)
		{
			if (fil->piece[y][x] == '*')
				return (y);
		}
	}
	return (0);
}

int			from_bottom(t_fil *fil)
{
	int		x;
	int		y;
	int		count;
	
	count = 1;
	y = 0;
	while (y < fil->piece_y)
	{
		x = 0;
		while (x < fil->piece_x)
		{
			if ((fil->piece[y][x] == '*') && (y >= count))
				count++;
			x++;
		}
		y++;
	}
	return (count);
}

void    get_mini_stats(t_fil *fil)
{
    fil->x_left = from_left(fil);
	fil->y_top = from_top(fil);
	fil->x_len = from_right(fil);
	fil->y_len = from_bottom(fil);
}


int		get_board(t_fil *fil)
{
	char	*line;

	while ((get_next_line(fil->fd, &line))) 
	{
		if (ft_strstr(line, "$$$"))
			player_info(fil, line);
		if (ft_strstr(line, "Plateau"))
			board_size(fil, line);
		if (ft_strstr(line, "Piece"))
			piece_size(fil, line);
		if ((line[0] == '*' || line[0] == '.'))
		{
			if (get_piece(fil, line))
            {
                get_mini_stats(fil);
                return (1);                
            }
		}
		if (ft_isdigit(line[0]))
		{
		    fil->board[ft_atoi(line)] = ft_strdup(ft_strchr(line, ' ') + 1);		
		}
		ft_bzero(line, sizeof(line));
	}
	return (0);
}

/*
**this checks the validity of the coordinates on the map of our given piece.
*/

int     check_place_validity(int board_place_x, int board_place_y, t_fil *fil)
{
    int x;
    int y;
	int count;

	count = 0;
    y = -1;
	while(++y < fil->y_len)
    {
        x = -1;
        while (++x < fil->x_len)
        {
	dprintf(2, ">\toffset[%i][%i]\tlen[%i][%i]\tboard[%i][%i]\tpiece[%i][%i]\tcoord[%i][%i]\t\n", fil->y_top, fil->x_left, fil->y_len, fil->x_len, board_place_y, board_place_y, (y + fil->y_top), (x + fil->x_left), y, x);
            if ((fil->board[board_place_y + y][board_place_x + x] == fil->me) && (fil->piece[y + fil->y_top][x + fil->x_left] == '*'))
				count++;
			if (fil->board[board_place_y + y][board_place_x + x] == fil->him && (fil->piece[y + fil->y_top][x + fil->x_left] == '*'))
				return (0);
	    }
	}
	if (count == 1)
	{
		fil->put_piece_x = board_place_x - fil->x_left;
		fil->put_piece_y = board_place_y - fil->y_top;
		free(fil->piece);
		return (1);
	}
	else
		return (0);
}

/*
**place_to_right
**finds the nearest valid place to the right to place the minipiece.
**then sets the put_piece_x and y variables to where the piece needs to be placed
*/

int		place_to_right(t_fil *fil)
{
	int x;
	int y;

	y = (fil->board_y - fil->y_len);
	while (--y >= 0)
	{
		x = (fil->board_x - fil->x_len);
		while(--x >= 0)
		{
			if(check_place_validity(x, y, fil) == 1)
				return (1);
		}
	}
	return (0);
}


/*
**Main starts
**initiate struct and sets all values to zero
**get board reads everything
**place_to_right - figures out the next place to place the piece
**then printf out the results.
*/
int     main(void)
{
    t_fil fil;
	int i;

    init_struct(&fil);
	//fil.fd = open("test.txt", O_RDWR);
    while (get_board(&fil) == 1)
   	{
		if(place_to_right(&fil))
			dprintf(1, "%i %i\n", fil.put_piece_y, fil.put_piece_x);
		else
			printf("0 0");
		fil.put_piece_y = 0;
		fil.put_piece_x = 0;
	}
	return (0);
}
