/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyoung <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/23 12:53:39 by lyoung            #+#    #+#             */
/*   Updated: 2017/08/23 12:56:29 by lyoung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../filler.h"

void	print_map(t_filler *data)
{
	int		y;
	int 	x;

	y = 0;
	while (y < data->map.bound_y)
	{
		x = 0;
		while (x < data->map.bound_x)
		{
			ft_printf("%4d", data->map.heatmap[y][x]);
			x++;
		}
		ft_printf("\n");
		y++;
	}
}

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
			ft_printf("%c ", data->piece.trimmed[y][x]);
			x++;
		}
		ft_printf("\n");
		y++;
	}
}

void	set_map(t_filler *data)
{
	int		i;

	data->map.board = (char **)malloc(sizeof(char *) * data->map.bound_y);
	i = 0;
	while (i < data->map.bound_y)
	{
		data->map.board[i] = ft_strnew(data->map.bound_x);
		i++;
	}
	data->map.heatmap = (int **)malloc(sizeof(int *) * data->map.bound_y);
	i = 0;
	while (i < data->map.bound_y)
	{
		data->map.heatmap[i] = (int *)malloc(sizeof(int) * data->map.bound_x);
		i++;
	}
}

void	get_map(t_filler *data)
{
	char	*line;
	int		i;

	get_next_line(STDIN_FILENO, &line);
	i = 0;
	while (!ft_isdigit(line[i]))
		i++;
	data->map.bound_y = ft_atoi(&line[i]);
	while (ft_isdigit(line[i]))
		i++;
	while (!ft_isdigit(line[i]))
		i++;
	data->map.bound_x = ft_atoi(&line[i]);
	data->map.range_y = data->map.bound_y / 3;
	data->map.range_x = data->map.bound_x / 6;
	set_map(data);
	ft_strdel(&line);
}

void	get_player(t_filler *data)
{
	char	*line;
	char	*tmp;
	int		nb;

	get_next_line(STDIN_FILENO, &line);
	tmp = ft_strchr(line, 'p');
	tmp++;
	nb = ft_atoi(tmp);
	data->player.ch = (nb == 1) ? 'O' : 'X';
	data->opponent.ch = (nb == 1) ? 'X' : 'O';
	ft_strdel(&line);
}

t_filler	*init_data(void)
{
	t_filler	*data;
	data = (t_filler*)malloc(sizeof(t_filler));
	data->opponent.max_x = 0;
	data->opponent.max_y = 0;
	data->opponent.min_x = INT_MAX;
	data->opponent.min_y = INT_MAX;
	data->init_flag = 0;
	return (data);
}

int     main(void)
{
    t_filler	*data;
	char		*line;

	data = init_data();
	get_player(data);
	get_map(data);
	while (get_next_line(STDIN_FILENO, &line) > 0)
	{
		skip_line(&line);
		read_map(data);
		set_heatmap(data);
		print_map(data);
		get_piece(data);
		set_newpiece(data);
		print_piece(data);
	}
	return (0);
}