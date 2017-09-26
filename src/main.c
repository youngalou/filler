/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyoung <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/23 12:53:39 by lyoung            #+#    #+#             */
/*   Updated: 2017/09/26 14:00:47 by lyoung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../filler.h"

void		set_map(t_filler *data)
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

int			get_map(t_filler *data)
{
	char	*line;
	int		i;

	if (get_next_line(STDIN_FILENO, &line) < 0)
		return (-1);
	i = 0;
	while (!ft_isdigit(line[i]))
		i++;
	data->map.bound_y = ft_atoi(&line[i]);
	while (ft_isdigit(line[i]))
		i++;
	while (!ft_isdigit(line[i]))
		i++;
	data->map.bound_x = ft_atoi(&line[i]);
	data->map.range_y = 1;
	data->map.range_x = 1;
	set_map(data);
	ft_strdel(&line);
	return (0);
}

int			get_player(t_filler *data)
{
	char	*line;
	char	*tmp;
	int		nb;

	if (get_next_line(STDIN_FILENO, &line) < 0)
		return (-1);
	tmp = ft_strchr(line, 'p');
	if (!tmp)
		return (-1);
	tmp++;
	nb = ft_atoi(tmp);
	data->player.ch = (nb == 1) ? 'O' : 'X';
	data->opponent.ch = (nb == 1) ? 'X' : 'O';
	ft_strdel(&line);
	return (0);
}

t_filler	*init_data(void)
{
	t_filler	*data;

	data = (t_filler*)malloc(sizeof(t_filler));
	data->opponent.max_x = 0;
	data->opponent.max_y = 0;
	data->opponent.min_x = INT_MAX;
	data->opponent.min_y = INT_MAX;
	data->place_x = 0;
	data->place_y = 0;
	data->heat = 0;
	data->init_flag = 0;
	return (data);
}

int			main(void)
{
	t_filler	*data;
	char		*line;

	data = init_data();
	if (get_player(data) < 0 || get_map(data) < 0)
	{
		ft_printf("%{red}Invalid file.\n%{eoc}");
		return (0);
	}
	while (get_next_line(STDIN_FILENO, &line) > 0)
	{
		if (read_map(data, line) < 0)
			return (0);
		set_heatmap(data);
		if (get_piece(data) < 0)
			return (0);
		set_newpiece(data);
		place_piece(data);
	}
	return (0);
}
