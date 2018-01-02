/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalcort <sbalcort@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/01 23:30:27 by sbalcort          #+#    #+#             */
/*   Updated: 2018/01/01 23:34:40 by sbalcort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

/*
**void  player_info(t_fil *fil, char *str)
**
**assuming string is "$$$ exec p1 : [./filler]"
**where the number after 'p' can be 1 or two
*/

void		player_info(t_fil *fil, char *str)
{
	char	*chr;

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

void		board_size(t_fil *fil, char *str)
{
	char	*chr;

	chr = ft_strchr(str, ' ');
	chr++;
	fil->board_y = ft_atoi(&chr[0]);
	while (ft_isdigit(chr[0]))
		chr++;
	while (!ft_isdigit(chr[0]))
		chr++;
	fil->board_x = ft_atoi(&chr[0]);
	fil->board = (char**)malloc(sizeof(char*) * fil->board_y);
}

/*
**int     get_piece(t_fil *fil, char *line)
**
**has its own counter counting down the
**number of lines untill @ end of reading
**the piece line by line
*/

int			get_piece(t_fil *fil, char *line)
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
**void    get_mini_stats(t_fil *fil, char *str)
**
**this extracts data from the piece.
**upper, bottom, left and right bound.
*/

void		get_mini_stats(t_fil *fil)
{
	get_left_bound(fil);
	get_right_bound(fil);
	get_top_bound(fil);
	get_bottom_bound(fil);
}

/*
**int     get_board(t_fil *fil)
**pulls out all data and board
**also the piece and related data
*/

int			get_board(t_fil *fil)
{
	char	*line;

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
				fil->count_y = 0;
				return (1);
			}
		}
		if (ft_isdigit(line[0]))
			fil->board[ft_atoi(line)] = ft_strdup(ft_strchr(line, ' ') + 1);
		ft_bzero(line, sizeof(line));
	}
	fil->count_y = 0;
	return (0);
}
