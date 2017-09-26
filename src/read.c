/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyoung <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/08 12:05:32 by lyoung            #+#    #+#             */
/*   Updated: 2017/09/26 13:59:27 by lyoung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../filler.h"

int		set_piece(t_filler *data)
{
	int		i;
	char	*line;

	data->piece.piece = (char **)malloc(sizeof(char *) * data->piece.size_y);
	i = 0;
	while (i < data->piece.size_y)
	{
		data->piece.piece[i] = ft_strnew(data->piece.size_x);
		i++;
	}
	i = 0;
	while (i < data->piece.size_y)
	{
		if (get_next_line(STDIN_FILENO, &line) < 0)
			return (-1);
		ft_memcpy(data->piece.piece[i], line, data->piece.size_x);
		ft_strdel(&line);
		i++;
	}
	return (0);
}

int		get_piece(t_filler *data)
{
	char	*line;
	int		i;

	if (get_next_line(STDIN_FILENO, &line) < 0)
		return (-1);
	i = 0;
	while (!ft_isdigit(line[i]))
		i++;
	data->piece.size_y = ft_atoi(&line[i]);
	while (ft_isdigit(line[i]))
		i++;
	while (!ft_isdigit(line[i]))
		i++;
	data->piece.size_x = ft_atoi(&line[i]);
	ft_strdel(&line);
	set_piece(data);
	return (0);
}

int		read_map(t_filler *data, char *line)
{
	int		i;

	if (!ft_strncmp(line, "Plateau", 7))
	{
		ft_strdel(&line);
		if (get_next_line(STDIN_FILENO, &line) < 0)
			return (-1);
		ft_strdel(&line);
	}
	i = 0;
	while (i < data->map.bound_y)
	{
		if (get_next_line(STDIN_FILENO, &line) < 0)
			return (-1);
		ft_memcpy(data->map.board[i], &line[4], data->map.bound_x);
		ft_strdel(&line);
		i++;
	}
	return (0);
}
