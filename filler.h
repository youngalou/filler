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

# define HEATMAX 100
# define DIV 2

typedef struct      s_filler
{
    char            player;
    char            opponent;
	int				map_x;
	int				map_y;
	char			**map;
	int				piece_x;
	int				piece_y;
	char			**piece;
	int				**heatmap;
	int 			range_x;
	int 			range_y;
	int 			max_x;
	int				max_y;
	int				min_x;
	int 			min_y;
}                   t_filler;

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

void		skip_line(char **line);
void		read_map(t_filler *data);
void		get_piece(t_filler *data);
void		set_piece(t_filler *data);

/*
** --------------- heatmap.c --------------
*/

void		fill_heatmap(t_filler *data, int level);
void		set_heatmap(t_filler *data);