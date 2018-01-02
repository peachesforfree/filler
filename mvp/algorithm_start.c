/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm_start.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalcort <sbalcort@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/01 20:23:24 by sbalcort          #+#    #+#             */
/*   Updated: 2018/01/01 20:31:54 by sbalcort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void		placement_start(t_fil *fil)
{
	if (!buffer_zone_check(fil))
		wall_off_buffer_zone(fil);
	if (not_near_buffer(fil))
		work_towards_buffer_zone(fil);
}

void		wall_off_buffer_zone(t_fil *fil)
{
	t_values	*head_node;
	int			x;
	int			y;

	head_node = NULL;
	y = -1 - fil->piece_top;
	while (++y < fil->board_y)
	{
		x = -1 - fil->piece_left;
		while (++x < fil->board_x)
		{
			if (bounds_check(fil, x, y) && check_mine(fil, x, y)
					&& check_his(fil, x, y))
				head_node = add_to_list(x, y, head_node,
						buffer_zone_fil_count(fil, x, y));
		}
	}
	asses_buffzone_count(fil, head_node);
}

void		norme(int lst_count, t_fil *fil, t_values *head_node)
{
	if (lst_count > 0)
		asses_places(fil, head_node);
	else
		take_anything(fil);
}

void		work_towards_buffer_zone(t_fil *fil)
{
	t_values	*head_node;
	int			x;
	int			y;
	int			lst_count;

	head_node = NULL;
	y = -1 - fil->piece_top;
	lst_count = 0;
	while (++y < fil->board_y)
	{
		x = -1 - fil->piece_left;
		while (++x < fil->board_x)
		{
			if (bounds_check(fil, x, y) && check_mine(fil, x, y)
					&& check_his(fil, x, y))
			{
				head_node = add_to_list(x, y, head_node,
						highest_piece_value(fil, x, y));
				lst_count++;
			}
		}
	}
	norme(lst_count, fil, head_node);
}

void		take_anything(t_fil *fil)
{
	t_values	*head_node;
	int			x;
	int			y;

	head_node = NULL;
	y = -1 - fil->piece_top;
	while (++y < fil->board_y)
	{
		x = -1 - fil->piece_left;
		while (++x < fil->board_x)
		{
			if (bounds_check(fil, x, y) && check_mine(fil, x, y)
					&& check_his(fil, x, y))
			{
				fil->put_piece_x = x;
				fil->put_piece_y = y;
				return ;
			}
		}
	}
}
