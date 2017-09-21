/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heatmap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyoung <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/08 14:34:40 by lyoung            #+#    #+#             */
/*   Updated: 2017/09/08 14:34:42 by lyoung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../filler.h"

void	set_cross(t_filler *data)
{
	int 	y;
	int 	x;
	int		i;

	y = data->player.init_y;
	x = data->player.init_x;
	i = 0;
	while (i < data->map.bound_x)
	{
		data->map.heatmap[y][i] = HEATMAX / DIV;
		i++;
	}
	i = 0;
	while (i < data->map.bound_y)
	{
		data->map.heatmap[i][x] = HEATMAX / DIV;
		i++;
	}
}

void	fill_heatmap(t_filler *data, int level)
{
	int		y;
	int		x;
	int		val;

	if (level <= 1)
		return ;
	y = 0;
	while (y < data->map.bound_y)
	{
		x = 0;
		while (x < data->map.bound_x)
		{
			if (data->map.heatmap[y][x] > 0)
			{
				val = data->map.heatmap[y][x];
				if (x - 1 >= 0 && data->map.heatmap[y][x - 1] < val && data->map.heatmap[y][x - 1] >= 0)
					data->map.heatmap[y][x - 1] = val / DIV;
				if (x + 1 < data->map.bound_x && data->map.heatmap[y][x + 1] < val && data->map.heatmap[y][x + 1] >= 0)
					data->map.heatmap[y][x + 1] = val / DIV;
				if (y - 1 >= 0 && data->map.heatmap[y - 1][x] < val && data->map.heatmap[y - 1][x] >= 0)
					data->map.heatmap[y - 1][x] = val / DIV;
				if (y + 1 < data->map.bound_y && data->map.heatmap[y + 1][x] < val && data->map.heatmap[y + 1][x] >= 0)
					data->map.heatmap[y + 1][x] = val / DIV;
			}
			x++;
		}
		y++;
	}
	fill_heatmap(data, level / DIV);
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

void	set_heatmap(t_filler *data)
{
	int		y;
	int		x;

	clear_heatmap(data);
	y = 0;
	while (y < data->map.bound_y)
	{
		x = 0;
		while (x < data->map.bound_x)
		{
			if (ft_toupper(data->map.board[y][x]) == data->opponent.ch)
			{
				data->map.heatmap[y][x] = 5000;
				if (x > data->opponent.max_x)
					data->opponent.max_x = x;
				if (x < data->opponent.min_x)
					data->opponent.min_x = x;
				if (y > data->opponent.max_y)
					data->opponent.max_y = y;
				if (y < data->opponent.min_y)
					data->opponent.min_y = y;
			}
			else if (data->init_flag == 0 && ft_toupper(data->map.board[y][x]) == data->player.ch)
			{
				data->player.init_x = x;
				data->player.init_y = y;
				data->init_flag = 1;
			}
			x++;
		}
		y++;
	}
	fill_heatmap(data, ITER);
	if (data->map.bound_x > 75 && data->map.bound_y > 75)
		set_cross(data);
}