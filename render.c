/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/16 00:43:23 by lgarczyn          #+#    #+#             */
/*   Updated: 2015/01/16 00:43:25 by lgarczyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void				*render_sector(void *data)
{
	t_data			*d;
	t_meta			*m;
	t_cast			ray;
	int				i;
	int				max;

	d = (t_data*)data;
	m = d->meta;
	i = m->img_width * d->pos / d->thn;
	max = m->img_width * (d->pos + 1) / d->thn;
	while (i < max)
	{
		ray = get_ray(m, (double)i);
		cast_ray(m, ray, i++, m->level);
	}
	return (NULL);
}

int					render(t_meta *meta)
{
	t_data			d;

	d.pos = 0;
	d.thn = 1;
	d.meta = meta;
	render_sector(&d);
	mlx_put_image_to_window(meta->mlx, meta->win, meta->img, 0, 0);
	return (0);
}

int					render_threaded(t_meta *meta)
{
	pthread_t		t[THREAD_NUM];
	t_data			d[THREAD_NUM];
	int				i;
	int				rc;

	i = -1;
	while (++i < THREAD_NUM)
	{
		d[i] = (t_data){i, THREAD_NUM, meta};
		rc = pthread_create(&t[i], NULL, render_sector, &d[i]);
		if (rc)
			error_thread(meta);
	}
	i = -1;
	while (++i < THREAD_NUM)
	{
		pthread_join(t[i], NULL);
	}
	mlx_put_image_to_window(meta->mlx, meta->win, meta->img, 0, 0);
	return (0);
}
