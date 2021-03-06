/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   place_piece.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyoung <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/14 14:08:24 by lyoung            #+#    #+#             */
/*   Updated: 2017/09/22 11:17:51 by lyoung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../filler.h"

int		check_place(t_filler *data, int x, int y)
{
	int		i;
	int		j;

	if (x + data->piece.trim_x > data->map.bound_x
			|| y + data->piece.trim_y > data->map.bound_y)
		return (0);
	data->overlap = 0;
	i = -1;
	while (++i < data->piece.trim_y)
	{
		j = -1;
		while (++j < data->piece.trim_x)
		{
			if (data->piece.trimmed[i][j] == '*')
			{
				if (ft_toupper(data->map.board[y + i][x + j])
						== data->player.ch)
					data->overlap++;
				else if (ft_toupper(data->map.board[y + i][x + j])
						== data->opponent.ch)
					return (0);
			}
		}
	}
	return ((data->overlap == 1) ? 1 : 0);
}

int		check_heat(t_filler *data, int x, int y)
{
	int		heat;
	int		i;
	int		j;

	heat = 0;
	i = 0;
	while (i < data->piece.trim_y)
	{
		j = 0;
		while (j < data->piece.trim_x)
		{
			if (data->piece.trimmed[i][j] == '*')
				heat += data->map.heatmap[y + i][x + j];
			j++;
		}
		i++;
	}
	return (heat);
}

void	place_piece(t_filler *data)
{
	int		heat;
	int		y;
	int		x;

	data->heat = -1;
	heat = 0;
	y = -1;
	while (++y <= data->map.bound_y - data->piece.trim_y)
	{
		x = -1;
		while (++x <= data->map.bound_x - data->piece.trim_x)
		{
			if (check_place(data, x, y))
			{
				heat = check_heat(data, x, y);
				if (heat > data->heat)
				{
					data->heat = heat;
					data->place_x = x - data->piece.margin_x;
					data->place_y = y - data->piece.margin_y;
				}
			}
		}
	}
	ft_printf("%d %d\n", data->place_y, data->place_x);
}
