#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

typedef struct      s_fil
{
	int				fd;
	char			me;
	char			him;
	int				board_y;
	int				board_x;
	int				piece_x;
	int				piece_y;
	char			**board;
	int				count_y;
	char			**piece;
	int				x_left;
	int				x_len;
	int				y_top;
	int				y_len;

}                   t_fil;

int		left(t_fil *fil)
{
	int x;
	int y;
	int	count;

	y = 0;
	count = fil->piece_x;
	while ((y < fil->piece_y) && (fil->piece != NULL))
	{
		x = 0;
		while (x < fil->piece_x)
		{
			if (fil->piece[y][x] == '*' && x < count)
				count = x;
			x++;
		}
		y++;
	}
	return (count);
}

int		top(t_fil *fil)
{
	int x;
	int y;
	int count;

	y = 0;
	count = fil->piece_y;
	while (fil->piece[y] != NULL)
	{
		x = 0;
		while (fil->piece[y][x])
		{
			if (fil->pice[y][x] == '*' && (y < count))
				count = y;
			x++;
		}
		y++;
	}
	return (count);
}

/*
**Starts at the left bound on x and starts counting outwards
*/
int		x_len(t_fil *fil)
{
	int x;
	int y;
	int count;

	y = 0;
	count = 0;
	while (fil->piece[y] != NULL)
	{
		x = fil->x_left;
		while (fil->piece[y][x])
		{
			if ((fil->pice[y][x] == '*') && (x > count))
				count = x;
			x++;
		}
		y++;
	}
	return (count);
}

/*
**Starting from Y top border, count the *'s going south
*/

int		y_len(t_fil *fil)
{
	int	x;
	int y;
	int	count;

	y = fil->y_top;
	while (fil->piece[y] != NULL)
	{
		x = 0;
		while (fil->piece[y][x])
		{
			if ((fil->piece[y][x] == '*') && (y > count))
				count = y;
			x++;
		}
		y++;
	}
	return (count);
}

/*
**
*/

void    get_mini_stats(t_fil *fil)
{
    fil->x_left = left(fil);
	fil->y_top = top(fil);
	fil->x_len = x_len(fil);		//total count to far right from 0
	fil->y_len = y_len(fil);		//total count to far botom from 0
}

void    init_struct(t_fil *fil)
{
	fil->fd = 0;
	fil->me = '\0';
	fil->him = '\0';
	fil->board_y = 0;
	fil->board_x = 0;
	fil->piece_x = 0;
	fil->piece_y = 0;
	fil->board = NULL;
	fil->count_y = 0;
	fil->piece = 0;
	fil->x_left = 0;
	fil->x_len = 0;
	fil->y_top = 0;
	fil->y_len = 0;
}

void    player_info(t_fil *fil, char *line)
{
    char	*chr;

	chr = ft_strchr(line, 'p');
	fil->me = (chr[1] == '1') ? 'O' : 'X';
	fil->him = (chr[1] == '1') ? 'X' : 'O';
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

int     get_piece(t_fil *fil, char *line)
{
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

int		read_board(t_fil *fil)
{
	char *line;

	while (get_next_line(fil->fd, &line))
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

int main(void)
{
	t_fil fil;

	init_struct(&fil);
	while (read_board(&fil) == 1)
   	{
		if(all_good(&fil))
			printf("%i %i\n", fil.put_piece_y, fil.put_piece_x);
		else
			printf("0 0\n");
	}

	return(0);
}