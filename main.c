#include <unistd.h>
#include "libft/libft.h"
#include <stdio.h>

#define FILEDESCRIPTOR 0

typedef struct	s_fil
{
	char		me;
	int			me_location_x;		//on map, no zero
	int			me_location_y;		//on map. no zero
	char		him;
	int			him_location_x;		//on map, no zero
	int			him_location_y;		//on map, no zero
	int			board_x;	//not including zero index
	int			board_y;	//not including zero index
	int			board_buffer;
	char		**board;	// board is saved here every iteration
	int			piece_x;	//piece dimentions to be read
	int			piece_y;
	char		**piece;	// where the piece is saved
	int			fd;			//reading from this file descriptor
	int			**heat_map;
	int			place_piece_x;	//the destination where to place the piece
	int			palce_piece_y;
	int			me_direction_x;
	int			me_direction_y;
	char		**mini_piece;
	int			mini_piece_x;
	int			mini_piece_y;
	int			mini_x_offset;
	int			mini_y_offset;
	int			put_piece_x;
	int			put_piece_y;

}				t_fil;

typedef struct	s_parse
{
	int			x_left;
	int 		x_right;
	int 		y_top;
	int 		y_bottom;
	char		**mini_piece;
}				t_parse;

t_fil	*initialize_values(void)
{
	t_fil *tmp;

	tmp = (t_fil*)malloc(sizeof(t_fil));
	tmp->me = 0;
	tmp->me_location_x = 0;
	tmp->me_location_y = 0;
	tmp->him = 0;
	tmp->him_location_x = 0;
	tmp->him_location_y = 0;
	tmp->board_x = 0;
	tmp->board_y = 0;
	tmp->board_buffer = 0;
	tmp->board = NULL;
	tmp->piece_x = 0;
	tmp->piece_y = 0;
	tmp->piece = NULL;
	tmp->fd = FILEDESCRIPTOR;
	tmp->me_direction_x = 0;
	tmp->me_direction_y = 0;
	tmp->mini_x_offset = 0;
	tmp->mini_y_offset = 0;
	return (tmp);
}

/*
**	This initializes which player is represented by which char
**		O = p1		X = p2
*/

void		get_player_stats(t_fil *fil, char *line)
{
	char	*chr;

	chr = ft_strchr(line, 'p');
	fil->me = (chr[1] == '1') ? 'O' : 'X';
	fil->him = (chr[1] == '1') ? 'X' : 'O';
}

/*
**	This iterates through the map from top to bottom from left to right looking for a '*'
**	returns the left mot bound of the 
*/

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

/*
**	This iterates thru the map bottom to top from right to left looking for a '*'
**	returns right most x bound for the '*'s
*/

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

/*
**	This searches the map from top to bottom, left to right for a '*'
**	returns the upper elevation end of the '*'
*/

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

/*
** This runs thru the piece map from bottom left to right looking for a '*'
** returns the lowest elevation for the piece.
*/

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

char		**make_mini_map(t_parse *piece, t_fil *fil)
{
	int x;
	int y;
	char **mini_piece;

	y = -1;
	mini_piece = (char**)malloc(sizeof(char*) * (piece->y_bottom - piece->y_top));
	dprintf(2, "\n\t\tminimap y=%i\tx=%i\n", ((piece->y_bottom - piece->y_top) + 1), ((piece->x_right - piece->x_left) + 2));
	fil->mini_piece_x = (piece->x_right - piece->x_left);
	fil->mini_piece_y = (piece->y_bottom - piece->y_top);
	while ((++y + piece->y_top) <= piece->y_bottom)
	{
		x = -1;
		mini_piece[y] = (char*)malloc(sizeof(char) * (piece->x_right - piece->x_left) + 2);
		while ((++x + piece->x_left) <= piece->x_right)
		{
			mini_piece[y][x] = fil->piece[y + piece->y_top][x + piece->x_left];
		}
		mini_piece[y][x] = '\0';
		dprintf(2, "\n\t\tprinted piece mini_piece[%i] = %s\n", y, mini_piece[y]); 
	}
	return (mini_piece);
}

void		make_mini_piece(t_fil *fil)
{
	t_parse piece;

	piece.x_left = from_left(fil);
	piece.x_right = from_right(fil);
	piece.y_top = from_top(fil);
	piece.y_bottom = from_bottom(fil);
	fil->mini_piece = make_mini_map(&piece, fil);
	fil->mini_x_offset = piece.x_left;
	dprintf(2,">\t\tx_offset <%i>\n", fil->mini_x_offset);
	fil->mini_y_offset = piece.y_top;
	dprintf(2,">\t\ty_offset <%i>\n", fil->mini_y_offset);
}

void		read_piece(t_fil *fil, char *line)
{
	int i;

	i = -1;
	while (++i < fil->piece_y)
	{
		fil->piece[i] = line;
		if ((i + 1) < fil->piece_y)
		{
			get_next_line(fil->fd, &line);
			dprintf(2, ">\tpiece read %s\n", line);
		}
	}
	make_mini_piece(fil);
}

/*
**gets dmensions of the piece x y starting at index of 1 and not zero.
*/

void	get_piece_info(t_fil *fil, char *line)
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
	fil->piece = (char**)malloc(sizeof(char*) * fil->piece_y);
}

/*
**	This gets the map dimensions 
**	then calls to func. malloc memory for map
*/

void		get_board_info(t_fil *fil, char *line)
{
	int		i;

	i = 0;
	while (!ft_isdigit(line[i]))
		i++;
	fil->board_y = ft_atoi(&line[i]);
	while (ft_isdigit(line[i]))
		i++;
	while (ft_isspace(&line[i]))			// this is to skip past the space between the numbers
		i++;
	fil->board_x = ft_atoi(&line[i]);
	fil->board = (char**)malloc(fil->board_y * sizeof(char*));
}

/*
**given x and y coord on the map, we can check the mini map against it.
*/

int		check_place_validity(int board_x, int board_y, t_fil *fil)
{
	int x;
	int y;

	//if ((fil->mini_piece_x + board_x) >= fil->board_x || (fil->mini_piece_y + board_y) >= fil->board_y)
	//	return (0);
	y = -1;
	while (++y <= fil->mini_piece_y )
	{
		x = -1;
		while (++x < fil->mini_piece_x )
		{
			if ((fil->board[y + board_y][x + board_x] == fil->me) && (fil->mini_piece[y][x] == '*'))
			{
				return (1);
			}			
		}
	}
	return (0);
}


void	place_to_right(t_fil *fil)
{
	int x;
	int y;

	y = -1;
	fil->put_piece_y = 0;
	fil->put_piece_x = 0;
	while (++y < fil->board_y)
	{
		x = fil->board_x;
		while(--x >= 0)
		{
			if(check_place_validity(x, y, fil))
			{
				fil->put_piece_x = (x - fil->mini_x_offset);
				dprintf(2, ">fil->put_piece_x = (%i - %i)\n", x, fil->mini_x_offset);
				fil->put_piece_y = (y - fil->mini_y_offset);
				dprintf(2, ">fil->put_piece_y = (%i - %i)\n", y, fil->mini_y_offset);
				x = -1;
				y = fil->board_x;
			}	
		}
	}
}

void	print_location(t_fil *fil)
{
	ft_putnbr(fil->put_piece_x);
	ft_putchar(' ');
	ft_putnbr(fil->put_piece_y);
	ft_putchar('\n');
	dprintf(2, ">\t\t\tCo-ord:%i %i\n", fil->put_piece_x, fil->put_piece_y);
}

int		read_parse_maps(t_fil *fil, char *line)
{
	while (get_next_line(fil->fd, &line))
	{
		dprintf(2,">\t%s\n", line);
		if (ft_strstr(line, "$$$"))
		{
			get_player_stats(fil, line);
			continue;
		}
		if (ft_strstr(line, "Plateau"))
		{
			get_board_info(fil, line);
			continue;
		}
		if (ft_isdigit(line[0]))
		{
			fil->board[ft_atoi(line)] = ft_strdup(ft_strchr(line, '.'));
			continue;
		}
		if (ft_strstr(line, "Piece"))
		{
			get_piece_info(fil, line);
			continue;
		}
		if (ft_strchr(&line[0],' '))		//might get problems here when at end of reading map and piece
			continue;
		if (line[0] == '*' || line[0] == '.')
		{
			read_piece(fil, line);
			//if (fil->piece[fil->piece_y] != NULL)
				break;
		}

	}
	return (1);
}

/*
**	Here we start by reading the first two lines
**		who is player one and player two
**		then the dimentions of the board
**	Then we stick in the while loop for the durration of the program
**		reading the map again,
**		reading each new piece 
**		compute next move
**		return the plcement value of the next piece 
*/
int		main(void)
{
	t_fil	*fil;
	char	*line;

	fil = initialize_values();
	//fil->fd = open("test.txt", O_RDONLY);
	while (read_parse_maps(fil, line))
	{
		place_to_right(fil);
		print_location(fil);
		sleep(1);
	}
	printf("0 0");
	return(0);
}