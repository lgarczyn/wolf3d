/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/20 21:47:00 by lgarczyn          #+#    #+#             */
/*   Updated: 2015/01/20 21:47:02 by lgarczyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void			put_string(char *str, t_meta *m)
{
	mlx_string_put(m->mlx, m->win, 0, 10, 0xFFFFFF, str);
}

void			put_pixel(int i, t_color color, t_meta *meta)
{
	meta->pixels[i] = color.R;
	meta->pixels[i + 1] = color.G;
	meta->pixels[i + 2] = color.B;
}

t_color			interpolate(t_color a, t_color b)
{
	t_color		ret;

	ret.R = (a.R + b.R) >> 1;
	ret.G = (a.G + b.R) >> 1;
	ret.B = (a.B + b.R) >> 1;
	return (ret);
}

t_color			finterpolate(t_color a, t_color b, float ta)
{
	t_color		ret;
	float		tb;

	tb = 1.0 - ta;
	ret.R = (float)a.R * tb + (float)b.R * ta;
	ret.G = (float)a.G * tb + (float)b.G * ta;
	ret.B = (float)a.B * tb + (float)b.B * ta;
	return (ret);
}
