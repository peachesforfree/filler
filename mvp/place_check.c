/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   place_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalcort <sbalcort@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/01 23:37:51 by sbalcort          #+#    #+#             */
/*   Updated: 2018/01/01 23:41:11 by sbalcort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

/*
**int     sweep_check(int **heat_map, int number)
**
**this checks the heat_map for the special number given,
**if not found, returns one
**if number is not found, returns zero
*/

int			sweep_check(int **heat_map, int number, int x_bound, int y_bound)
{
	int	x;
	int	y;

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

int			check_mine(t_fil *fil, int x, int y)
{
	int	xx;
	int	yy;
	int	count;

	count = 0;
	yy = -1;
	xx = -1;
	while (++yy < fil->piece_y)
	{
		while (++xx < fil->piece_x)
		{
			if ((fil->piece[yy][xx] == '*') &&
					(fil->board[y + yy][x + xx] == fil->me))
				count++;
		}
		xx = -1;
	}
	if (count == 1)
		return (1);
	return (0);
}

int			check_his(t_fil *fil, int x, int y)
{
	int	xx;
	int	yy;

	xx = -1;
	yy = -1;
	while (++yy < fil->piece_y)
	{
		while (++xx < fil->piece_x)
		{
			if ((y + yy >= 0) && (x + xx >= 0) && (x + xx < fil->board_x)
					&& (y + yy < fil->board_y))
			{
				if ((fil->board[y + yy][x + xx] == fil->him) &&
						(fil->piece[yy][xx] == '*'))
				{
					return (0);
				}
			}
		}
		xx = -1;
	}
	return (1);
}

int			bounds_check(t_fil *fil, int x, int y)
{
	if ((y + fil->piece_bottom + 1) > fil->board_y)
		return (0);
	if ((x + fil->piece_right + 1) > fil->board_x)
		return (0);
	if (x < (0 - fil->piece_left))
		return (0);
	if (y < 0)
		return (0);
	return (1);
}

/*
**void        buffer_zone_filled(t_fil *fil)
**
**given the current map, if the DMZ zone is filled, the function returns 1
**if the DMZ zone is not filled in, function reurns 0
**DMZ zone is determined by 10% of the board width or fil->board_x value
*/

int			buffer_zone_check(t_fil *fil)
{
	int	number;
	int	x;
	int	y;

	y = -1;
	number = ((fil->board_x * BUFFER_ZONE) / 100);
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
