/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim_piece.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyoung <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/13 12:55:32 by lyoung            #+#    #+#             */
/*   Updated: 2017/09/13 12:55:38 by lyoung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../filler.h"

int		get_topmargin(t_filler *data)
{
	int		y;
	int 	x;

	y = 0;
	while (y < data->piece.size_y)
	{
		x = 0;
		while (x < data->piece.size_x)
		{
			if (data->piece.piece[y][x] == '*')
				return (y);
			x++;
		}
		y++;
	}
	return (0);
}

int		get_leftmargin(t_filler *data)
{
	int		x;
	int		y;

	x = 0;
	while (x < data->piece.size_x)
	{
		y = 0;
		while (y < data->piece.size_y)
		{
			if (data->piece.piece[y][x] == '*')
				return (x);
			y++;
		}
		x++;
	}
	return (0);
}

int		get_bottommargin(t_filler *data)
{
	int		y;
	int 	x;

	y = data->piece.size_y - 1;
	while (y >= 0)
	{
		x = data->piece.size_x - 1;
		while (x >= 0)
		{
			if (data->piece.piece[y][x] == '*')
				return (y);
			x--;
		}
		y--;
	}
	return (0);
}

int		get_rightmargin(t_filler *data)
{
	int		x;
	int 	y;


	x = data->piece.size_x - 1;
	while (x >= 0)
	{
		y = data->piece.size_y - 1;
		while (y >= 0)
		{
			if (data->piece.piece[y][x] == '*')
				return (x);
			y--;
		}
		x--;
	}
	return (0);
}

void	set_newpiece(t_filler *data)
{
	int		margin[4];
	int		i;
	int		j;
	int		x;
	int		y;

	margin[0] = get_topmargin(data);
	margin[1] = get_leftmargin(data);
	margin[2] = get_bottommargin(data);
	margin[3] = get_rightmargin(data);
	data->piece.margin_x = margin[1];
	data->piece.margin_y = margin[0];
	data->piece.trim_y = margin[2] - margin[0] + 1;
	data->piece.trim_x = margin[3] - margin[1] + 1;
	data->piece.trimmed = (char**)malloc(sizeof(char*) * data->piece.trim_y);
	i = 0;
	while (i < data->piece.trim_y)
	{
		data->piece.trimmed[i] = ft_strnew(data->piece.trim_x);
		i++;
	}
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