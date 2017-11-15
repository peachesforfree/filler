#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

typedef struct       s_fil
{
    char    me;
    char    him;
    int     fd;
    
    char    **board;
    int     board_x;
    int     board_y;
	int		current_x;
	int		current_y;
    
    char    **piece;
    int     count_y;
    int     piece_x;
    int     piece_y;
    int     x_left;
    int     x_right;
    int     y_top;
    int     y_bottom;   

    int		put_piece_x;
	int		put_piece_y;
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
    fil->x_right = 0;
    fil->y_top = 0;
    fil->y_bottom = 0;
    fil->put_piece_x = 0;
    fil->put_piece_y = 0;
    fil->count_y = -1;
	fil->current_x = 0;
	fil->current_y = 0;
}
int			from_left(t_fil *fil)
{
	int x;
	int y;
	
	x = -1;
	while (++x < fil->piece_x)
	{
		y = -1;
		while (++y < fil->piece_y)
		{
			if (fil->piece[y][x] == '*')
				return (x);
		}
	}
	return (0);
}

int			from_right(t_fil *fil)
{
	int x;
	int y;
	
	x = fil->piece_x;
	while (--x >= 0)
	{
		y = -1;
		while (++y < fil->piece_y)
		{
			if (fil->piece[y][x] == '*')
				return (x);
		}
	}
	return (0);
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
	
	y = fil->piece_y;
	while (--y >= 0)
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

void    get_mini_stats(t_fil *fil)
{
    fil->x_left = from_left(fil);
	fil->x_right = from_right(fil);
	fil->y_top = from_top(fil);
	fil->y_bottom = from_bottom(fil);
}

int     get_piece(t_fil *fil, char *line)
{
    if(++fil->count_y < fil->piece_y)
	{
        fil->piece[fil->count_y] = ft_strdup(line);
	}
	if (fil->count_y == (fil->piece_y - 1))
	{
		fil->count_y = -1;
	    return (1);
	}
	return (0);
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
	}
	return (0);
}




int main(void)
{
	t_fil fil;

	init_struct(&fil);
	while (get_board(&fil) == 1)
   	{
		if(algorithm(&fil) && valid_placement(&fil))
			printf("%i %i\n", fil.put_piece_y, fil.put_piece_x);
		else
			printf("0 0");
	}

	return(0);
}