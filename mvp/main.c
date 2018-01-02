/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalcort <sbalcort@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/01 23:25:57 by sbalcort          #+#    #+#             */
/*   Updated: 2018/01/01 23:27:01 by sbalcort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void	fil_init(t_fil *fil)
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
**void        print_coordinates(t_fil *fil)
**
**prints the coordinates on the map and sets
**those values back to zero
*/

void	print_coordinates(t_fil *fil)
{
	ft_putnbr(fil->put_piece_y);
	ft_putchar(' ');
	ft_putnbr(fil->put_piece_x);
	ft_putchar('\n');
	fil->put_piece_y = 0;
	fil->put_piece_x = 0;
}

/*
**void        not_near_buffer(t_fil *fil)
**
**checks heat map for DMZ zone and IF fil->me
**if on the same place on the board. if true, return 1
*/

int		not_near_buffer(t_fil *fil)
{
	int		number;
	int		x;
	int		y;
	bool	place;

	y = -1;
	place = false;
	number = ((fil->board_x * BUFFER_ZONE) / 100);
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

int		main(void)
{
	t_fil fil;

	fil_init(&fil);
	while (get_board(&fil))
	{
		fil.heat_map = heat_map_init(fil.board,
				fil.board_x, fil.board_y, fil.him);
		placement_start(&fil);
		print_coordinates(&fil);
	}
	return (0);
}
