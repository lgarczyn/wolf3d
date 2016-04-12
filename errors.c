/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/16 00:52:30 by lgarczyn          #+#    #+#             */
/*   Updated: 2015/01/16 00:52:31 by lgarczyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void			error_memory(t_meta *meta)
{
	ft_putstr(meta->prog_name);
	ft_putstr(": Not enough memory\n");
	exit(1);
}

void			error_thread(t_meta *meta)
{
	ft_putstr(meta->prog_name);
	ft_putstr(": Failed to open new thread\n");
	exit(1);
}

void			error_argument(t_meta *meta, char *arg)
{
	ft_putstr(meta->prog_name);
	ft_putstr(": Invalid argument in: ");
	ft_putstr(arg);
	ft_putstr("\nPossible arguments: t\n");
	exit(1);
}

void			error_chargument(t_meta *meta, char arg)
{
	ft_putstr(meta->prog_name);
	ft_putstr(": Invalid argument in: ");
	write(1, &arg, 1);
	ft_putstr("\nPossible arguments: t\n");
	exit(1);
}

void			error_file(t_meta *meta, char *name)
{
	ft_putstr(meta->prog_name);
	ft_putstr(": Could not find, open or read file: ");
	ft_putstr(name);
	ft_putstr("\n");
	exit(1);
}
