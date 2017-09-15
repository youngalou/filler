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
		data->map.heatmap[y][i] = 1;
		i++;
	}
	i = 0;
	while (i < data->map.bound_y)
	{
		data->map.heatmap[i][x] = 1;
		i++;
	}
}

void	set_box(t_filler *data)
{
	int		max_x;
	int		max_y;
	int		min_x;
	int 	min_y;
	int 	i;

	max_x = data->opponent.max_x + data->map.range_x;
	max_y = data->opponent.max_x + data->map.range_y;
	min_x = data->opponent.min_x - data->map.range_x;
	min_y = data->opponent.min_y - data->map.range_y;
	i = (min_y >= 0) ? min_y : 0;
	while (i <= max_y)
	{
		if (max_x < data->map.bound_x)
			data->map.heatmap[i][max_x] = HEATMAX;
		if (min_x >= 0)
			data->map.heatmap[i][min_x] = HEATMAX;
		i++;
	}
	i = (min_x >= 0) ? min_x : 0;
	while (i <= max_x)
	{
		if (max_y < data->map.bound_y)
			data->map.heatmap[max_y][i] = HEATMAX;
		if (min_y >= 0)
			data->map.heatmap[min_y][i] = HEATMAX;
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

void	set_heatmap(t_filler *data)
{
	int		y;
	int		x;

	y = 0;
	while (y < data->map.bound_y)
	{
		x = 0;
		while (x < data->map.bound_x)
		{
			if (ft_toupper(data->map.board[y][x]) == data->opponent.ch)
			{
				data->map.heatmap[y][x] = -1;
				if (x > data->opponent.max_x)
					data->opponent.max_x = x;
				else if (x < data->opponent.min_x)
					data->opponent.min_x = x;
				if (y > data->opponent.max_y)
					data->opponent.max_y = y;
				else if (y < data->opponent.min_y)
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
	set_cross(data);
	set_box(data);
	fill_heatmap(data, 32);
}