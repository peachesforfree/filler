/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm_etc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalcort <sbalcort@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/01 20:22:09 by sbalcort          #+#    #+#             */
/*   Updated: 2018/01/01 20:22:39 by sbalcort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void		asses_buffzone_count(t_fil *fil, t_values *current)
{
	t_values	*best_node;
	int			best_value;
	int			i;

	i = 0;
	best_value = 0;
	while (current != NULL)
	{
		if (current->high_value > best_value)
		{
			best_value = current->high_value;
			best_node = current;
		}
		current = current->next;
	}
	fil->put_piece_y = best_node->y;
	fil->put_piece_x = best_node->x;
}

int			buffer_zone_fil_count(t_fil *fil, int x_start, int y_start)
{
	int	value;
	int	x;
	int	y;

	y = -1 - fil->piece_top;
	value = 0;
	while (++y < fil->piece_y && ((y + y_start) < fil->board_y))
	{
		x = -1 - fil->piece_left;
		while (++x < fil->piece_x && ((x + x_start) < fil->board_x))
		{
			if ((fil->heat_map[y + y_start][x + x_start] == (fil->board_x *
BUFFER_ZONE) / 100) && (fil->piece[y][x] == '*'))
				value++;
		}
	}
	return (value);
}

/*
**t_list        *add_to_list(int x, int y, t_list *head, int heat_number)
**
**given x,y coord, head node, and heat_number
**t_list is made with the string of "x y\n" and heat number in content size
*/

t_values	*add_to_list(int x, int y, t_values *head, int heat_number)
{
	t_values	*temp;

	temp = (t_values*)malloc(sizeof(t_values));
	temp->x = x;
	temp->y = y;
	temp->high_value = heat_number;
	temp->next = head;
	return (temp);
}

/*
**int         highest_heat_value(t_fil *fil, int x_start, int y_start)
**
**function below is to asses the highest values on the heat map the piece will
**cover and returns that value
*/

int			highest_piece_value(t_fil *fil, int x_start, int y_start)
{
	int		value;
	int		x;
	int		y;

	y = -1;
	value = 1000000000;
	while (++y < fil->piece_y && ((y + y_start) < fil->board_y))
	{
		x = -1;
		while (++x < fil->piece_x && ((x + x_start) < fil->board_x))
		{
			if ((fil->heat_map[y + y_start][x + x_start] < value)
					&& (fil->piece[y][x] == '*'))
				value = fil->heat_map[y + y_start][x + x_start];
		}
	}
	return (value);
}

/*
**void        asses_places(t_fil *fil, t_list *current)
**
**this runs through the linked list looking for the highes content_size value.
**prints values and deletes linked list
*/

void		asses_places(t_fil *fil, t_values *current)
{
	t_values	*best_node;
	int			best_value;
	int			i;

	i = 0;
	best_value = 1000000000;
	while (current != NULL)
	{
		if (current->high_value < best_value)
		{
			best_value = current->high_value;
			best_node = current;
		}
		current = current->next;
	}
	fil->put_piece_y = best_node->y;
	fil->put_piece_x = best_node->x;
}
