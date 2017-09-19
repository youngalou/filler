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

# define HEATMAX 1000
# define DIV 1.5

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
	int					init_flag;
	int					place_x;
	int 				place_y;
	int 				heat;
}                   	t_filler;

/*
** --------------- main.c --------------
*/

void		print_map(t_filler *data);
void		print_heatmap(t_filler *data);
void		set_map(t_filler *data);
void		get_map(t_filler *data);
void		get_player(t_filler *data);
t_filler	*init_data(void);

/*
** --------------- read.c --------------
*/

void		skip_line(char **line);
void		read_map(t_filler *data);
void		get_piece(t_filler *data);
void		set_piece(t_filler *data);

/*
** --------------- heatmap.c --------------
*/

void		fill_heatmap(t_filler *data, int level);
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

void		place_piece(t_filler *data);