/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memalloc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/04 15:37:43 by lgarczyn          #+#    #+#             */
/*   Updated: 2015/02/04 15:37:43 by lgarczyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void			*xmalloc(size_t len, t_meta *meta)
{
	void		*ret;

	ret = malloc(len);
	if (ret)
		return (ret);
	error_memory(meta);
	return (NULL);
}

void			*xmemalloc(size_t len, t_meta *meta)
{
	uint8_t		*ret;
	UINT		inc;

	ret = xmalloc(len, meta);
	inc = 0;
	while (inc < len)
		ret[inc++] = 0;
	return (ret);
}

int				xopen(char *path, int oflag, t_meta *meta)
{
	int			fd;

	fd = open(path, oflag);
	if (fd <= 0)
		error_file(meta, path);
	return (fd);
}
