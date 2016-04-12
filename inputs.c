/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/16 00:44:17 by lgarczyn          #+#    #+#             */
/*   Updated: 2015/01/16 00:44:20 by lgarczyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int				apply_key(int keycode, t_meta *meta, int is_down)
{
	if (keycode == KEYCODE_A || keycode == KEYCODE_LEFT)
		meta->input.left = is_down;
	else if (keycode == KEYCODE_W || keycode == KEYCODE_UP)
		meta->input.up = is_down;
	else if (keycode == KEYCODE_D || keycode == KEYCODE_RIGHT)
		meta->input.right = is_down;
	else if (keycode == KEYCODE_S || keycode == KEYCODE_DOWN)
		meta->input.down = is_down;
	else if (keycode == KEYCODE_4)
		meta->input.ccwise = is_down;
	else if (keycode == KEYCODE_6)
		meta->input.cwise = is_down;
	else
		return (0);
	mlx_loop_hook(meta->mlx, loop_hook, meta);
	return (0);
}

int				key_down(int keycode, t_meta *meta)
{
	if (!meta)
		return (0);
	if (keycode == KEYCODE_EXIT)
		exit(0);
	else
		apply_key(keycode, meta, 1);
	return (0);
}

int				key_up(int keycode, t_meta *meta)
{
	if (!meta)
		return (0);
	apply_key(keycode, meta, 0);
	return (0);
}

int				mouse_down(int button, int x, int y, t_meta *meta)
{
	if (!meta)
		return (0);
	if (button == 1)
	{
		meta->prev_mouse.y = y;
		meta->prev_mouse.x = x;
		meta->follow_mouse = 1;
	}
	mlx_loop_hook(meta->mlx, loop_hook, meta);
	return (0);
}

int				mouse_move(int x, int y, t_meta *meta)
{
	if (!meta)
		return (0);
	if (meta->follow_mouse)
	{
		meta->pos.r += (x - meta->prev_mouse.x) * ROT_SPEED;
		meta->prev_mouse.y = y;
		meta->prev_mouse.x = x;
	}
	mlx_loop_hook(meta->mlx, loop_hook, meta);
	return (0);
}
