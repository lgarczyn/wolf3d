/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   casting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/16 00:43:23 by lgarczyn          #+#    #+#             */
/*   Updated: 2015/01/16 00:43:25 by lgarczyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void				draw_wall(t_meta *meta, int i, t_vint d, t_cast r)
{
	double			rem;
	t_color			cur;
	float			ratio;

	rem = 1.0 - fmod(meta->img_height / 2 + r.height, 1.0);
	ratio = 1.0 / (float)d.x * 0.7;
	while (i < d.x)
	{
		cur = finterpolate(r.cola, (t_color)0, 0.7 - i * ratio);
		put_pixel(i, cur, meta);
		i += meta->sizeline;
	}
	if (i < d.y)
	{
		put_pixel(i, finterpolate(r.cola, r.colb, rem), meta);
		i += meta->sizeline;
	}
	ratio = 1 / (float)(d.y - d.x) * 0.7;
	while (i < d.y)
	{
		cur = finterpolate(r.colb, (t_color)0, (i - d.x) * ratio);
		put_pixel(i, cur, meta);
		i += meta->sizeline;
	}
}

void				render_column(t_meta *meta, t_cast r, int x, int side)
{
	double			t;
	t_vint			pos;
	int				i;

	if (side == 0)
		r.dist = fabs((r.map.x - meta->pos.x + (1 - r.step.x) / 2) / r.cosi.x);
	else
		r.dist = fabs((r.map.y - meta->pos.y + (1 - r.step.y) / 2) / r.cosi.y);
	r.height = 150 / r.dist;
	t = CLAMP(r.height / 100, 0.5, 1.0);
	if (side)
		r.cola.color = (r.step.y > 0) ? 0x993333 : 0x773333;
	else
		r.cola.color = (r.step.x > 0) ? 0x883333 : 0x663333;
	r.cola = finterpolate((t_color)(0x444444), r.cola, t);
	t = MIN(t, 0.8);
	r.colb = finterpolate((t_color)(0x444444), (t_color)(0x338833), t);
	i = x * meta->inc;
	pos.x = (meta->img_height / 2 + r.height) * meta->sizeline + i;
	pos.y = meta->sizeline * (meta->img_height - 1) + i;
	if (pos.x > pos.y)
		pos.x = pos.y;
	draw_wall(meta, i, pos, r);
}

void				render_column_gold(t_meta *meta, t_cast r, int x, int side)
{
	double			t;
	t_vint			pos;
	int				i;

	if (side == 0)
		r.dist = fabs((r.map.x - meta->pos.x + (1 - r.step.x) / 2) / r.cosi.x);
	else
		r.dist = fabs((r.map.y - meta->pos.y + (1 - r.step.y) / 2) / r.cosi.y);
	r.height = 150 / r.dist;
	t = CLAMP(r.height / 100, 0.5, 1.0);
	if (side)
		r.cola.color = (r.step.y > 0) ? 0xFFFF00 : 0x00FFFF;
	else
		r.cola.color = (r.step.x > 0) ? 0xFF00FF : 0x0000FF;
	r.cola = finterpolate((t_color)(0x444444), r.cola, t);
	t = MIN(t, 0.8);
	r.colb = finterpolate((t_color)(0x444444), (t_color)(0x338833), t);
	i = x * meta->inc;
	pos.x = (meta->img_height / 2 + r.height) * meta->sizeline + i;
	pos.y = meta->sizeline * (meta->img_height - 1) + i;
	if (pos.x > pos.y)
		pos.x = pos.y;
	draw_wall(meta, i, pos, r);
}

void				render_column_blue(t_meta *meta, t_cast r, int x, int side)
{
	double			t;
	t_vint			pos;
	int				i;

	if (side == 0)
		r.dist = fabs((r.map.x - meta->pos.x + (1 - r.step.x) / 2) / r.cosi.x);
	else
		r.dist = fabs((r.map.y - meta->pos.y + (1 - r.step.y) / 2) / r.cosi.y);
	r.height = 150 / r.dist;
	t = CLAMP(r.height / 100, 0.5, 1.0);
	if (side)
		r.cola.color = (r.step.y > 0) ? 0x333399 : 0x333377;
	else
		r.cola.color = (r.step.x > 0) ? 0x333388 : 0x333366;
	r.cola = finterpolate((t_color)(0x444444), r.cola, t);
	t = MIN(t, 0.8);
	r.colb = finterpolate((t_color)(0x444444), (t_color)(0x338833), t);
	i = x * meta->inc;
	pos.x = (meta->img_height / 2 + r.height) * meta->sizeline + i;
	pos.y = meta->sizeline * (meta->img_height - 1) + i;
	if (pos.x > pos.y)
		pos.x = pos.y;
	draw_wall(meta, i, pos, r);
}
