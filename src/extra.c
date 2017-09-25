/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyoung <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/25 12:07:26 by lyoung            #+#    #+#             */
/*   Updated: 2017/09/25 12:07:28 by lyoung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../filler.h"

void	print_piece(t_filler *data)
{
	int		y;
	int		x;

	y = 0;
	while (y < data->piece.trim_y)
	{
		x = 0;
		while (x < data->piece.trim_x)
		{
			ft_dprintf(2, "%c ", data->piece.trimmed[y][x]);
			x++;
		}
		ft_dprintf(2, "\n");
		y++;
	}
}

void	print_map(t_filler *data)
{
	int		y;
	int		x;

	y = 0;
	while (y < data->map.bound_y)
	{
		x = 0;
		while (x < data->map.bound_x)
		{
			ft_dprintf(2, "%c ", data->map.board[y][x]);
			x++;
		}
		ft_dprintf(2, "\n");
		y++;
	}
}

void	print_heatmap(t_filler *data)
{
	int		y;
	int		x;

	y = 0;
	while (y < data->map.bound_y)
	{
		x = 0;
		while (x < data->map.bound_x)
		{
			if (data->map.heatmap[y][x] >= HEATMAX)
				ft_dprintf(2, "%{red}5d%{eoc}", data->map.heatmap[y][x]);
			else
				ft_dprintf(2, "%5d", data->map.heatmap[y][x]);
			x++;
		}
		ft_dprintf(2, "\n");
		y++;
	}
}

void	clear_heatmap(t_filler *data)
{
	int		y;
	int		x;

	y = 0;
	while (y < data->map.bound_y)
	{
		x = 0;
		while (x < data->map.bound_x)
		{
			data->map.heatmap[y][x] = 0;
			x++;
		}
		y++;
	}
}

void	set_trimpiece(t_filler *data, int *margin)
{
	int		i;
	int		j;
	int		y;
	int		x;

	data->piece.trimmed = (char**)malloc(sizeof(char*) * data->piece.trim_y);
	i = -1;
	while (++i < data->piece.trim_y)
		data->piece.trimmed[i] = ft_strnew(data->piece.trim_x);
	i = 0;
	y = margin[0];
	while (i < data->piece.trim_y)
	{
		j = 0;
		x = margin[1];
		while (j < data->piece.trim_x)
		{
			data->piece.trimmed[i][j] = data->piece.piece[y][x];
			j++;
			x++;
		}
		i++;
		y++;
	}
}
