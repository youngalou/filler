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

/*void	set_heatmap(t_filler *data)
{
	int		i;
	int		j;
	int		shift_x;
	int		shift_y;

	data->heatmap = (int **)malloc(sizeof(int *) * data->map_y);
	i = 0;
	while (i < data->map_y)
	{
		data->heatmap[i] = (int *)malloc(sizeof(int) * data->map_x);
		i++;
	}
	shift_x = data->map_x / 2;
	shift_y = data->map_y / 2;
	i = 0;
	while (i < data->map_y)
	{
		j = 0;
		while (j < data->map_x)
		{
			data->heatmap[i][j] = ft_abs((i - shift_y) * (j - shift_x));
			j++;
		}
		i++;
	}
}*/

/*void	fill_heatmap(t_filler *data)
{
}*/

void	set_cross(t_filler *data)
{
	int		max_x;
	int		max_y;
	int		min_x;
	int 	min_y;
	int 	i;

	max_x = data->max_x + data->range_x;
	max_y = data->max_y + data->range_y;
	min_x = data->min_x - data->range_x;
	min_y = data->min_y - data->range_y;
	i = (min_y >= 0) ? min_y : 0;
	while (i <= max_y)
	{
		if (max_x < data->map_x)
			data->heatmap[i][max_x] = HEATMAX;
		if (min_x >= 0)
		data->heatmap[i][min_x] = HEATMAX;
		i++;
	}
	i = (min_x >= 0) ? min_x : 0;
	while (i <= max_x)
	{
		if (max_y < data->map_y)
			data->heatmap[max_y][i] = HEATMAX;
		if (min_y >= 0)
		data->heatmap[min_y][i] = HEATMAX;
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
	while (y < data->map_y)
	{
		x = 0;
		while (x < data->map_x)
		{
			if (data->heatmap[y][x] > 0)
			{
				val = data->heatmap[y][x];
				if (x - 1 >= 0 && data->heatmap[y][x - 1] < val && data->heatmap[y][x - 1] >= 0)
					data->heatmap[y][x - 1] = val / DIV;
				if (x + 1 < data->map_x && data->heatmap[y][x + 1] < val && data->heatmap[y][x + 1] >= 0)
					data->heatmap[y][x + 1] = val / DIV;
				if (y - 1 >= 0 && data->heatmap[y - 1][x] < val && data->heatmap[y - 1][x] >= 0)
					data->heatmap[y - 1][x] = val / DIV;
				if (y + 1 < data->map_y && data->heatmap[y + 1][x] < val && data->heatmap[y + 1][x] >= 0)
					data->heatmap[y + 1][x] = val / DIV;
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

	//ft_printf("%d\t%d\n", data->map_x, data->map_y);
	y = 0;
	while (y < data->map_y)
	{
		x = 0;
		while (x < data->map_x)
		{
			if (ft_toupper(data->map[y][x]) == data->opponent)
			{
				data->heatmap[y][x] = -1;
				if (x > data->max_x)
					data->max_x = x;
				else if (x < data->min_x)
					data->min_x = x;
				if (y > data->max_y)
					data->max_y = y;
				else if (y < data->min_y)
					data->min_y = y;
			}
			x++;
		}
		y++;
	}
	set_cross(data);
	fill_heatmap(data, 8);
}