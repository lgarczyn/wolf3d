/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/30 17:41:32 by lgarczyn          #+#    #+#             */
/*   Updated: 2015/01/30 17:41:35 by lgarczyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

SCHAR				get_wall(t_meta *meta, int x, int y, int level)
{
	return (meta->maps[level].data[x][y]);
}

void				set_wall(t_meta *meta, int x, int y, SCHAR val)
{
	meta->maps[meta->level].data[x][y] = val;
}

UCHAR				*analyse_data(UCHAR *data, t_meta *meta, char *name)
{
	int				i;

	i = 0;
	while (data[i])
	{
		if (data[i] == ' ')
			data[i] = (0);
		else if (data[i] >= '0' && data[i] <= '9')
			data[i] = data[i] - '0' + 1;
		else if (data[i] >= 'A' && data[i] <= 'Z')
			data[i] = data[i] - 'A' + PORTAL_1;
		else
			error_file(meta, name);
		i++;
	}
	return (data);
}

t_map				load_map(t_meta *meta, char *name)
{
	int				fd;
	int				i;
	int				ret;
	UCHAR			*line;
	t_map			map;

	fd = xopen(name, O_RDONLY, meta);
	map.data = xmemalloc(sizeof(UCHAR*) * 3000, meta);
	i = 0;
	map.width = -1;
	while ((ret = get_next_line(fd, (char**)&line)) > 0)
	{
		map.data[i] = analyse_data(line, meta, name);
		if (++i >= 3000)
			error_file(meta, name);
		if (map.width == -1)
			map.width = ret;
		else if (ret != map.width)
			error_file(meta, name);
	}
	close(fd);
	map.height = i;
	if (ret < 0 || map.height == 0 || map.width == 0)
		error_file(meta, name);
	return (map);
}
