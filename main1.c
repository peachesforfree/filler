#include <unistd.h>
#include "libft/libft.h"
#include <stdio.h>
#include <fcntl.h>

typedef struct       s_fil
{
    int     fd;
    int     board_x;
    int     board_y;
    char    **board;
    char    me;
    char    him;
	int		mini_x_offset;
	int		mini_y_offset;
    int		put_piece_x;
	int		put_piece_y;
}                   t_fil;

typedef struct      s_parse
{
    int     piece_x;
    int     piece_y;
    char    **piece;
    char    **mini_piece;
	int		mini_piece_x;
	int		mini_piece_y;
    int     x_left;
    int     x_right;
    int     y_top;
    int     y_bottom;
    int     count_y;
}               t_parse;

void	free_board_piece(t_fil *fil, t_parse *parse)
{
	fil->put_piece_x = 0;
	fil->put_piece_y = 0;
	parse->count_y = -1;
	parse->mini_piece = NULL;
	parse->piece = NULL;
	parse->x_left = 0;
	parse->x_right = 0;
	parse->y_top = 0;
	parse->y_bottom = 0;
}

void    init_structs(t_fil **fil, t_parse **piece)
{
    *fil = (t_fil*)ft_memalloc(sizeof(t_fil));
    *piece = (t_parse*)ft_memalloc(sizeof(t_parse));
    (*fil)->fd = 0;
    (*fil)->board_x = 0;
    (*fil)->board_y = 0;
    (*fil)->me = 0;
    (*fil)->him = 0;
	(*fil)->mini_x_offset = 0;
	(*fil)->mini_y_offset = 0;
    (*fil)->put_piece_x = 0;
	(*fil)->put_piece_y = 0;
	(*piece)->piece_x = 0;
    (*piece)->piece_y = 0;
    (*piece)->piece = NULL;
    (*piece)->mini_piece = NULL;
    (*piece)->x_left = 0;
    (*piece)->x_right = 0;
    (*piece)->y_top = 0;
    (*piece)->y_bottom = 0;
    (*piece)->count_y = -1;

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
	while (ft_isdigit(line[i]))             //skip past numeric char
		i++;
	while (ft_isspace(&line[i]))			// this is to skip past the space between the numbers
		i++;
	fil->board_x = ft_atoi(&line[i]);       
	fil->board = (char**)ft_memalloc((fil->board_y + 1) * sizeof(char*));       //allocates pointers for each line on the board
    fil->board[fil->board_y] = NULL;
}

char		**make_mini_map(t_parse *piece)
{
	int x;
	int y;
	char **mini_piece;

	y = -1;
	mini_piece = (char**)ft_memalloc(sizeof(char*) * (piece->y_bottom - piece->y_top));
dprintf(2, ">\t\tminimap y=%i\tx=%i\n", ((piece->y_bottom - piece->y_top) + 1), ((piece->x_right - piece->x_left) + 2));
	piece->mini_piece_x = (piece->x_right - piece->x_left);
	piece->mini_piece_y = (piece->y_bottom - piece->y_top);
	while ((++y + piece->y_top) <= piece->y_bottom)
	{
		x = -1;
		mini_piece[y] = (char*)ft_memalloc(sizeof(char) * (piece->x_right - piece->x_left) + 2);
		while ((++x + piece->x_left) <= piece->x_right)
		{
			mini_piece[y][x] = piece->piece[y + piece->y_top][x + piece->x_left];
		}
		mini_piece[y][x] = '\0';
		dprintf(2, ">\t\tprinted piece mini_piece[%i] = %s\n", y, mini_piece[y]); 
	}
	return (mini_piece);
}

void	piece_size(t_parse *piece, char *line)
{
	int i;

	i = 0;
	while (!ft_isdigit(line[i]))
		i++;
	piece->piece_y = ft_atoi(&line[i]);
	while (ft_isdigit(line[i]))
		i++;
	while (!ft_isdigit(line[i]))
		i++;
	piece->piece_x = ft_atoi(&line[i]);
	piece->piece = (char**)ft_memalloc(sizeof(char*) * piece->piece_y);
    piece->piece[piece->piece_y] = NULL;
}

/*
**	This iterates through the map from top to bottom from left to right looking for a '*'
**	returns the left mot bound of the 
*/

int			from_left(t_parse *fil)
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

int			from_right(t_parse *parse)
{
	int x;
	int y;
	
	x = parse->piece_x;
	while (--x >= 0)
	{
		y = -1;
		while (++y < parse->piece_y)
		{
			if (parse->piece[y][x] == '*')
				return (x);
		}
	}
	return (0);
}

/*
**	This searches the map from top to bottom, left to right for a '*'
**	returns the upper elevation end of the '*'
*/

int			from_top(t_parse *fil)
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

int			from_bottom(t_parse *fil)
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

void		make_mini_piece(t_fil *fil, t_parse *piece)
{
	piece->x_left = from_left(piece);
dprintf(2, ">\tx_left=%i\n", piece->x_left);
	piece->x_right = from_right(piece);
dprintf(2, ">\tx_right=%i\n", piece->x_right);
	piece->y_top = from_top(piece);
dprintf(2, ">\ty_top=%i\n", piece->y_top);
	piece->y_bottom = from_bottom(piece);
dprintf(2, ">\ty_bottom=%i\n", piece->y_bottom);
	piece->mini_piece = make_mini_map(piece);
	fil->mini_x_offset = piece->x_left;
dprintf(2,">\tx_offset=%i\n", fil->mini_x_offset);
	fil->mini_y_offset = piece->y_top;
dprintf(2,">\ty_offset=%i\n", fil->mini_y_offset);
}

int     get_piece(t_fil *fil, t_parse *piece, char *line)
{
    if(++piece->count_y < piece->piece_y)
        piece->piece[piece->count_y] = ft_strdup(line);
    if (piece->count_y == (piece->piece_y - 1))
	{
		make_mini_piece(fil, piece);
		dprintf(2, ">get_piece return one");
	    return (1);
	}
	dprintf(2, ">get_piece return zero");
	return (0);
}

int		get_board(t_fil *fil, t_parse *piece)
{
	int i;
	char	*line;
	while ((i = get_next_line(fil->fd, &line))) 
	{
		if (ft_strstr(line, "$$$")) // && ft_strstr(line, "./filler")
			player_info(fil, line);
		if (ft_strstr(line, "Plateau"))
			board_size(fil, line);
		if (ft_strstr(line, "Piece"))
			piece_size(piece, line);
		if ((line[0] == '*' || line[0] == '.'))
		{
			if (get_piece(fil, piece, line))
				return (1);
		}
		if (ft_isdigit(line[0]))
		    fil->board[ft_atoi(line)] = ft_strdup(ft_strchr(line, ' ') + 1);
		//free(line);
	}
	return (0);
}

/*
**given x and y coord on the map, we can check the mini map against it.
*/

int		check_place_validity(int location_x, int location_y, t_fil *fil, t_parse *piece)
{
	int x;
	int y;
	//if ((fil->mini_piece_x + board_x) >= fil->board_x || (fil->mini_piece_y + board_y) >= fil->board_y)
	//	return (0);
	y = -1;
//dprintf(2, ">\tChecking place validity x=%i y=%i", piece->mini_piece_y, piece->mini_piece_x);
	while (piece->mini_piece[++y] != NULL )
	{
dprintf(2, ">\tchecking y=%i", y);
		x = -1;
		while (++x < ft_strlen(piece->mini_piece[0]))
		{
dprintf(2, " x =%i",x);
			if ((fil->board[y + location_y][x + location_x]) == (fil->me)) // && (piece->mini_piece[y][x] == '*'))
			{
				return (1);
			}		
		}

	}
	return (0);
}

int		place_to_right(t_fil *fil, t_parse *piece)
{
	int x;
	int y;

	y = -1;
dprintf(2, ">\tplacing to right\n");
dprintf(2, "place_to_right piece->mini_piece_y =%i", piece->mini_piece_y);
	while ((++y + piece->mini_piece_y) < fil->board_y)
	{
		x = fil->board_x - piece->mini_piece_x;

		while(--x >= 0)
		{
dprintf(2, "\n>>Checking place[%i][%i]\n", y, x);
			if(check_place_validity(x, y, fil, piece))
			{
				fil->put_piece_x = (x - fil->mini_x_offset);
				dprintf(2, ">\tfil->put_piece_x = (%i - %i)\n", x, fil->mini_x_offset);
				fil->put_piece_y = (y - fil->mini_y_offset);
				dprintf(2, ">fil->put_piece_y = (%i - %i)\n", y, fil->mini_y_offset);
				x = -1;
				y = fil->board_x;
dprintf(2, "sucessful placement\n");
				return (1);
			}
		}
	}
	return (0);
}


int     main(void)
{
    t_fil *fil;
    t_parse *piece;

    fil = NULL;
    piece = NULL;
    init_structs(&fil, &piece);

	//fil->fd = open("test.txt", O_RDWR);
    while (get_board(fil, piece))
   	{
   		if (place_to_right(fil, piece)) //analyze(fil, piece))  // for now make this the place to the right
   		{
			ft_putnbr(fil->put_piece_y);
dprintf(2, ">\t%d\n", fil->put_piece_y);
			ft_putchar(' ');
			ft_putnbr(fil->put_piece_x);
dprintf(2, ">\t%d\n", fil->put_piece_x);
			ft_putchar('\n');
			free_board_piece(fil, piece);   //Still need to write
		}
		else
			ft_putstr("0 0\n");
	dprintf(2, "~~~~~~MARKER END\n");
	}
	return (0);
}

/*
Its starting to look like when validating the piece at its given location on the map. It shits the bead when we get 
to the edge of the right side of the map. Looks like it just reaturns ZERO at check place validity. 

maybe redo this section so I keep in mind of the far edge of the minipiece staying on the main board?
or maybe redo the variables in the fil struct so things are clearly defined in the name.*/