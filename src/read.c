/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyoung <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/08 12:05:32 by lyoung            #+#    #+#             */
/*   Updated: 2017/09/08 12:05:35 by lyoung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../filler.h"

void	skip_line(char **line)
{
	if (!ft_strncmp(*line, "Plateau", 7))
	{
		ft_strdel(line);
		get_next_line(STDIN_FILENO, line);
		ft_strdel(line);
	}
}

void	read_map(t_filler *data)
{
	int		i;
	char	*line;

	i = 0;
	while (i < data->map_y)
	{
		get_next_line(STDIN_FILENO, &line);
		ft_memcpy(data->map[i], &line[4], data->map_x);
		ft_strdel(&line);
		i++;
	}
}

void	get_piece(t_filler *data)
{
	char	*line;
	int		i;

	get_next_line(STDIN_FILENO, &line);
	i = 0;
	while (!ft_isdigit(line[i]))
		i++;
	data->piece_x = ft_atoi(&line[i]);
	while (ft_isdigit(line[i]))
		i++;
	while (!ft_isdigit(line[i]))
		i++;
	data->piece_y = ft_atoi(&line[i]);
	ft_strdel(&line);
	set_piece(data);
}

void	set_piece(t_filler *data)
{
	int		i;
	char	*line;

	data->piece = (char **)malloc(sizeof(char *) * data->piece_y);
	i = 0;
	while (i < data->piece_y)
	{
		data->piece[i] = ft_strnew(data->piece_x);
		i++;
	}
	i = 0;
	while (i < data->piece_y)
	{
		get_next_line(STDIN_FILENO, &line);
		ft_memcpy(data->piece[i], line, data->piece_x);
		ft_strdel(&line);
		i++;
	}
}