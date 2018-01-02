/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heat_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalcort <sbalcort@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/01 21:02:30 by sbalcort          #+#    #+#             */
/*   Updated: 2018/01/01 21:20:53 by sbalcort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

/*
**void    fill_heat_map(int  **heat_map, int x_board, int y_board)
**
**runs thru map while laying down one number at a time
*/

void		fill_heat_map(int **m, int x_b, int y_b)
{
	int y;
	int x;
	int n;

	n = 1;
	while (++n && sweep_check(m, 0, x_b, y_b))
	{
		y = -1;
		while (++y < y_b)
		{
			x = -1;
			while (++x < x_b)
			{
				if ((x - 1) > 0 && m[y][x - 1] == (n - 1) && m[y][x] == 0)
					m[y][x] = n;
				if (x + 1 < (x_b - 1) && m[y][x + 1] == (n - 1) && m[y][x] == 0)
					m[y][x] = n;
				if (y - 1 > 0 && m[y - 1][x] == (n - 1) && m[y][x] == 0)
					m[y][x] = n;
				if (y + 1 < (y_b - 1) && m[y + 1][x] == (n - 1) && m[y][x] == 0)
					m[y][x] = n;
			}
		}
	}
}

/*
**int     **heat_map(char **board, int x_board, int y_board, char him)
**
**this inits the 2d int array and places in the values for the opponent.
*/

int			**heat_map_init(char **board, int x_board, int y_board, char him)
{
	int	**heat_map;
	int	x;
	int	y;

	heat_map = (int**)ft_calloc(y_board, (x_board * sizeof(int)));
	y = -1;
	while (++y < y_board)
	{
		x = -1;
		while (++x < x_board)
		{
			if (board[y][x] == him)
				heat_map[y][x] = 1;
		}
	}
	fill_heat_map(heat_map, x_board, y_board);
	return (heat_map);
}

/*
**void    printf_heat_map(int **heat, int x_bound, int y_bound)
**
**this is only for debugging to show how the heat map is populating
*/

void		printf_heat_map(int **heat, int x_bound, int y_bound)
{
	int	x;
	int	y;

	y = -1;
	while (++y < y_bound)
	{
		x = -1;
		while (++x < x_bound)
		{
			dprintf(2, " %i ", heat[y][x]);
		}
		dprintf(2, "\n");
	}
	dprintf(2, "\n");
}
