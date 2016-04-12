/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/20 23:27:40 by lgarczyn          #+#    #+#             */
/*   Updated: 2015/01/20 23:28:13 by lgarczyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int				expose_hook(t_meta *m)
{
	if (!m)
		return (0);
	if (m->is_init)
		mlx_put_image_to_window(m->mlx, m->win, m->img, 0, 0);
	else
	{
		if (m->is_threaded)
			render_threaded(m);
		else
			render(m);
		m->is_init = 1;
	}
	return (0);
}

void			move_player(t_meta *meta, float rot, float speed)
{
	t_ray		new;
	int			wall;

	new.r = meta->pos.r;
	new.x = meta->pos.x + cos(new.r + rot) * speed;
	new.y = meta->pos.y + sin(new.r + rot) * speed;
	wall = get_wall(meta, floor(new.x), floor(new.y), meta->level);
	if (IS_WALL(wall))
	{
		return ;
	}
	else if (IS_PORTAL(wall))
	{
		setup_level(meta, GET_PORTAL(wall));
	}
	else if (IS_POINT(wall))
	{
		meta->points++;
		set_wall(meta, floor(new.x), floor(new.y), 0);
	}
	meta->pos = new;
}

void			apply_input(t_input input, t_meta *meta)
{
	if (input.left)
		move_player(meta, -PI_1_2, KEY_SPEED / 2);
	if (input.up)
		move_player(meta, 0, KEY_SPEED);
	if (input.right)
		move_player(meta, PI_1_2, KEY_SPEED / 2);
	if (input.down)
		move_player(meta, PI, KEY_SPEED);
	if (input.ccwise)
		meta->pos.r -= ROT_SPEED;
	if (input.cwise)
		meta->pos.r += ROT_SPEED;
}

int				loop_hook(t_meta *m)
{
	if (!m)
		return (0);
	apply_input(m->input, m);
	if (m->is_threaded)
		render_threaded(m);
	else
		render(m);
	if (m->points < 49)
		put_string(ft_itoa(m->points, m->buff), m);
	else
		put_string("YOU WON!", m);
	return (0);
}
