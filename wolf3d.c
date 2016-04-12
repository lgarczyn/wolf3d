/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wold3d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/20 21:43:15 by lgarczyn          #+#    #+#             */
/*   Updated: 2015/01/20 21:43:17 by lgarczyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int				main(int ac, char **av)
{
	t_meta		meta;

	meta.level = 0;
	meta.points = 0;
	meta.prog_name = av[0];
	meta.follow_mouse = 0;
	meta.input = EMPTY_INPUT;
	setup_maps(&meta);
	setup_coord(&meta);
	setup_args(&meta, ac, av);
	meta.mlx = mlx_init();
	if (!meta.mlx)
		error_memory(&meta);
	setup_window(&meta, "Wolf 3d");
	mlx_loop(meta.mlx);
	return (1);
}

void			setup_maps(t_meta *meta)
{
	meta->maps[0] = load_map(meta, "maps/map0");
	meta->maps[1] = load_map(meta, "maps/map1");
	meta->maps[2] = load_map(meta, "maps/map2");
	meta->maps[3] = load_map(meta, "maps/map3");
	meta->maps[4] = load_map(meta, "maps/map4");
}

void			setup_level(t_meta *meta, int level)
{
	meta->level = level;
	setup_coord(meta);
	mlx_loop_hook(meta->mlx, loop_hook, meta);
}

void			setup_coord(t_meta *meta)
{
	meta->img_height = SCREEN_HEIGHT;
	meta->img_width = SCREEN_WIDTH;
	meta->fov = PI / 4 * 3;
	meta->pos.x = 1.5;
	meta->pos.y = 8.5;
	meta->pos.r = 0;
}

void			setup_window(t_meta *m, char *name)
{
	m->win = mlx_new_window(m->mlx, m->img_width, m->img_height, name);
	if (!m->win)
		error_memory(m);
	m->img = mlx_new_image(m->mlx, m->img_width, m->img_height);
	if (!m->img)
		error_memory(m);
	m->pixels = mlx_get_data_addr(m->img, &m->bpp, &m->sizeline, &m->endian);
	m->inc = m->bpp / 8;
	m->is_init = 0;
	mlx_expose_hook(m->win, expose_hook, m);
	mlx_hook(m->win, KeyPress, KeyPressMask, key_down, m);
	mlx_hook(m->win, KeyRelease, KeyReleaseMask, key_up, m);
	mlx_hook(m->win, ButtonPress, ButtonPressMask, mouse_down, m);
	mlx_hook(m->win, MotionNotify, PointerMotionMask, mouse_move, m);
}
