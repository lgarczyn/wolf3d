/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/16 00:43:23 by lgarczyn          #+#    #+#             */
/*   Updated: 2015/01/16 00:43:25 by lgarczyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void			setup_args(t_meta *meta, int ac, char **av)
{
	int			i;
	int			j;
	char		c;

	meta->is_threaded = 0;
	i = 0;
	while (++i < ac)
	{
		j = 0;
		if (av[i][0] != '-')
			error_argument(meta, av[i]);
		while ((c = av[i][++j]))
			if (c == 't')
				meta->is_threaded = 1;
			else
				error_chargument(meta, c);
	}
}
