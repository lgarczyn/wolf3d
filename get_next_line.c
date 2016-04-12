/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/07 18:02:55 by lgarczyn          #+#    #+#             */
/*   Updated: 2014/11/07 18:02:56 by lgarczyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "get_next_line.h"

int					set_struct(t_struct **prevs, int fd, char **line)
{
	t_struct		*prev;

	prev = prevs[fd];
	if (prev != NULL)
		return (0);
	prev = (t_struct*)malloc(sizeof(t_struct));
	if (prev == NULL)
	{
		free(*line);
		*line = NULL;
		return (1);
	}
	prev->pos = 0;
	prev->max = 0;
	prev->str = (char*)malloc(BUFF_SIZE);
	if (prev->str == NULL)
	{
		free(prev);
		free(*line);
		*line = NULL;
		return (1);
	}
	prevs[fd] = prev;
	return (0);
}

void				free_struct(t_struct **prev)
{
	free((*prev)->str);
	free(*prev);
	*prev = NULL;
}

int					get_char(t_struct **prevs, int fd, char *str)
{
	t_struct		*prev;

	prev = prevs[fd];
	if (prev->pos >= prev->max)
	{
		prev->pos = 0;
		prev->max = read(fd, prev->str, BUFF_SIZE);
		if (prev->max <= 0)
		{
			free_struct(prevs + fd);
			return (prev->max);
		}
	}
	*str = prev->str[prev->pos++];
	return (1);
}

int					realloc_line(char **line, int size, t_struct **prev, int d)
{
	char			*str;
	int				i;

	if (!d)
		str = (char*)malloc(size * 2);
	if (str == NULL || d)
	{
		free_struct(prev);
		free(*line);
		*line = NULL;
		return (-1);
	}
	i = size;
	while (i-- > 0)
		str[i] = line[0][i];
	free(*line);
	*line = str;
	return (size * 2);
}

int					get_next_line(int const fd, char **line)
{
	static t_struct	*prevs[256];
	int				size;
	int				err;
	int				i;

	if (BUFF_SIZE < 1 || line == NULL)
		return (-1);
	i = 0;
	size = 200;
	line[0] = malloc(size);
	if (line[0] == NULL)
		return (-1);
	if (set_struct(prevs, fd, line))
		return (-1);
	while ((err = get_char(prevs, fd, line[0] + i)) > 0 && line[0][i] != '\n')
		if (++i >= size - 1)
			if ((size = realloc_line(line, size, prevs + fd, 0)) == -1)
				return (-1);
	line[0][i] = '\0';
	if (err < 0)
		return (realloc_line(line, 0, prevs + fd, 1));
	if (err > 0 || i > 0)
		return (1);
	free(line[0]);
	return (0);
}
