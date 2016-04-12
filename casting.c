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

void				cast_ray(t_meta *meta, t_cast ray, int x, int level)
{
	int				wall;
	int				side;

	wall = 0;
	while (wall <= 0)
	{
		side = !(ray.side.x < ray.side.y);
		if (ray.side.x < ray.side.y)
			ray.side.x += ray.delt.x, ray.map.x += ray.step.x;
		else
			ray.side.y += ray.delt.y, ray.map.y += ray.step.y;
		wall = get_wall(meta, ray.map.x, ray.map.y, level);
	}
	if (wall == POINT)
		render_column_gold(meta, ray, x, side);
	else if (IS_PORTAL(wall))
		cast_ray(meta, ray, x, GET_PORTAL(wall));
	else if (wall == WALL_2)
		render_column_blue(meta, ray, x, side);
	else
		render_column(meta, ray, x, side);
}

t_cast				get_ray(t_meta *meta, int x)
{
	t_cast			ray;

	ray.pos = meta->pos;
	ray.pos.r += (meta->fov / 2.0) *
		(double)(x - meta->img_width / 2) /
		(double)meta->img_width;
	ray.map.x = (int)ray.pos.x;
	ray.map.y = (int)ray.pos.y;
	ray.cosi.x = cos(ray.pos.r);
	ray.cosi.y = sin(ray.pos.r);
	ray.delt.x = hypot(1, ray.cosi.y / ray.cosi.x);
	ray.delt.y = hypot(1, ray.cosi.x / ray.cosi.y);
	ray.step.x = (ray.cosi.x < 0) ? -1 : 1;
	ray.step.y = (ray.cosi.y < 0) ? -1 : 1;
	ray.side.x = (ray.cosi.x < 0) ? (meta->pos.x - ray.map.x) * ray.delt.x
		: (ray.map.x + 1.0 - meta->pos.x) * ray.delt.x;
	ray.side.y = (ray.cosi.y < 0) ? (meta->pos.y - ray.map.y) * ray.delt.y
		: (ray.map.y + 1.0 - meta->pos.y) * ray.delt.y;
	return (ray);
}
