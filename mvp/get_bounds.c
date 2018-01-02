/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_bounds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalcort <sbalcort@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/01 20:40:27 by sbalcort          #+#    #+#             */
/*   Updated: 2018/01/01 21:02:08 by sbalcort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

/*
**void    piece_size(t_fil * fil, char *str)
**
**this assumes "Piece 2 1:" within str
**first number is the piece_y and second is piece_x
**also allocates char* pointers for saving the piece
*/

void	piece_size(t_fil *fil, char *str)
{
	char	*chr;

	chr = ft_strchr(str, ' ');
	chr++;
	fil->piece_y = ft_atoi(&chr[0]);
	while (ft_isdigit(chr[0]))
		chr++;
	while (!ft_isdigit(chr[0]))
		chr++;
	fil->piece_x = ft_atoi(&chr[0]);
	fil->piece = (char**)malloc(sizeof(char*) * fil->piece_y);
}

/*
**void    get_left_bound(t_fil *fil)
**
**gets left most bound of the piece
*/

void	get_left_bound(t_fil *fil)
{
	int	x;
	int	y;

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

void	get_right_bound(t_fil *fil)
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
				fil->piece_right = x;
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

void	get_top_bound(t_fil *fil)
{
	int	x;
	int	y;

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

void	get_bottom_bound(t_fil *fil)
{
	int	x;
	int	y;

	y = (fil->piece_y - 1);
	x = 0;
	while (y >= 0)
	{
		while (x <= fil->piece_x)
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
