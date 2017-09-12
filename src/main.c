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
	while (y < data->map_y)
	{
		x = 0;
		while (x < data->map_x)
		{
			ft_printf("%4d", data->heatmap[y][x]);
			x++;
		}
		ft_printf("\n");
		y++;
	}
}


void	set_map(t_filler *data)
{
	int		i;

	data->map = (char **)malloc(sizeof(char *) * data->map_y);
	i = 0;
	while (i < data->map_y)
	{
		data->map[i] = ft_strnew(data->map_x);
		i++;
	}
	data->heatmap = (int **)malloc(sizeof(int *) * data->map_y);
	i = 0;
	while (i < data->map_y)
	{
		data->heatmap[i] = (int *)malloc(sizeof(int) * data->map_x);
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
	data->map_y = ft_atoi(&line[i]);
	while (ft_isdigit(line[i]))
		i++;
	while (!ft_isdigit(line[i]))
		i++;
	data->map_x = ft_atoi(&line[i]);
	data->range_y = data->map_y / 3;
	data->range_x = data->map_x / 6;
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
	data->player = (nb == 1) ? 'O' : 'X';
	data->opponent = (nb == 1) ? 'X' : 'O';
	ft_strdel(&line);
}

t_filler	*init_data(void)
{
	t_filler	*data;
	data = (t_filler*)malloc(sizeof(t_filler));
	data->player = 0;
	data->opponent = 0;
	data->map_x = 0;
	data->map_y = 0;
	data->map = 0;
	data->piece_x = 0;
	data->piece_y = 0;
	data->piece = 0;
	data->heatmap = 0;
	data->range_x = 0;
	data->range_y = 0;
	data->max_x = 0;
	data->max_y = 0;
	data->min_x = INT_MAX;
	data->min_y = INT_MAX;
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
		//get_piece(data);
		return (0);
	}
	return (0);
}