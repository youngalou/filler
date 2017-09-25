/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyoung <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/23 12:54:48 by lyoung            #+#    #+#             */
/*   Updated: 2017/08/23 12:56:09 by lyoung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/superlibft.h"

# define HEATMAX 5000
# define DIV 1.1

typedef struct		s_player
{
	char			ch;
	int				max_x;
	int				max_y;
	int 			min_x;
	int				min_y;
	int 			init_x;
	int 			init_y;
}					t_player;

typedef struct		s_opponent
{
	char			ch;
	int				max_x;
	int				max_y;
	int 			min_x;
	int				min_y;
}					t_opponent;

typedef struct		s_map
{
	char			**board;
	int				bound_x;
	int 			bound_y;
	int 			range_x;
	int				range_y;
	int				**heatmap;
}					t_map;

typedef struct		s_piece
{
	char 			**piece;
	int 			size_x;
	int 			size_y;
	char			**trimmed;
	int 			trim_x;
	int 			trim_y;
	int 			margin_x;
	int				margin_y;
}					t_piece;

typedef struct      	s_filler
{
	struct s_player		player;
	struct s_opponent	opponent;
	struct s_map		map;
	struct s_piece		piece;
	int					place_x;
	int 				place_y;
	int 				heat;
	int					init_flag;
	int					overlap;
}                   	t_filler;

/*
** --------------- main.c --------------
*/

void		set_map(t_filler *data);
void		get_map(t_filler *data);
void		get_player(t_filler *data);
t_filler	*init_data(void);

/*
** --------------- read.c --------------
*/

void		set_piece(t_filler *data);
void		get_piece(t_filler *data);
void		read_map(t_filler *data, char *line);

/*
** --------------- heatmap.c --------------
*/

void		set_cross(t_filler *data);
void		fill_adjacent(t_filler *data, int x, int y);
void		fill_heatmap(t_filler *data, int level);
void		init_heatmap(t_filler *data, int x, int y);
void		set_heatmap(t_filler *data);

/*
** --------------- trim_piece.c --------------
*/

int			get_topmargin(t_filler *data);
int			get_leftmargin(t_filler *data);
int			get_bottommargin(t_filler *data);
int			get_rightmargin(t_filler *data);
void		set_newpiece(t_filler *data);

/*
** --------------- place_piece.c --------------
*/

int			check_place(t_filler *data, int x, int y);
int			check_heat(t_filler *data, int x, int y);
void		place_piece(t_filler *data);

/*
** --------------- extra.c --------------
*/

void		print_piece(t_filler *data);
void		print_map(t_filler *data);
void		print_heatmap(t_filler *data);
void		clear_heatmap(t_filler *data);
void		set_trimpiece(t_filler *data, int *margin);