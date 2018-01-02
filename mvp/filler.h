/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalcort <sbalcort@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/01 20:32:26 by sbalcort          #+#    #+#             */
/*   Updated: 2018/01/01 20:40:02 by sbalcort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_H
# define FILLER_H

# include <unistd.h>
# include <stdio.h>
# include "./libft/libft.h"
# include <stdbool.h>

# define BUFFER_ZONE 1

typedef struct	s_fil
{
	char		me;
	char		him;
	int			fd;
	char		**board;
	int			board_x;
	int			board_y;
	char		**piece;
	int			piece_y;
	int			piece_x;
	int			piece_left;
	int			piece_right;
	int			piece_top;
	int			piece_bottom;
	int			count_y;
	int			x_place;
	int			y_place;
	int			put_piece_x;
	int			put_piece_y;
	int			**heat_map;
	int			current_x;
	int			current_y;
}				t_fil;

typedef struct	s_values
{
	int			x;
	int			y;
	int			high_value;
	void		*next;
}				t_values;

void			placement_start(t_fil *fil);
void			wall_off_buffer_zone(t_fil *fil);
void			asses_buffzone_count(t_fil *fil, t_values *current);
int				buffer_zone_fil_count(t_fil *fil, int x_start, int y_start);
void			take_anything(t_fil *fil);
t_values		*add_to_list(int x, int y, t_values *head, int heat_number);
int				highest_piece_value(t_fil *fil, int x_start, int y_start);
void			asses_places(t_fil *fil, t_values *current);
int				not_near_buffer(t_fil *fil);
int				buffer_zone_check(t_fil *fil);
int				**heat_map_init(char **board, int x_board, int y_board,
		char him);
void			fill_heat_map(int **heat_map, int x_board, int y_board);
int				sweep_check(int **heat_map, int number, int x_bound,
		int y_bound);
void			printf_heat_map(int **heat, int x_bound, int y_bound);
int				bounds_check(t_fil *fil, int x, int y);
int				check_his(t_fil *fil, int x, int y);
int				check_mine(t_fil *fil, int x, int y);
int				get_board(t_fil *fil);
void			get_mini_stats(t_fil *fil);
void			get_bottom_bound(t_fil *fil);
void			get_top_bound(t_fil *fil);
void			get_right_bound(t_fil *fil);
void			get_left_bound(t_fil *fil);
int				get_piece(t_fil *fil, char *line);
void			piece_size(t_fil *fil, char *str);
void			board_size(t_fil *fil, char *str);
void			player_info(t_fil *fil, char *str);
void			print_coordinates(t_fil *fil);
void			fil_init(t_fil *fil);
void			work_towards_buffer_zone(t_fil *fil);
#endif
