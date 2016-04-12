/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/16 00:09:47 by lgarczyn          #+#    #+#             */
/*   Updated: 2015/01/20 18:23:46 by lgarczyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H

# include "X.h"
# include <mlx.h>
# include <math.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>

# include "get_next_line.h"

# include <pthread.h>

# define MIN(a,b)		(((a)<(b))?(a):(b))
# define MAX(a,b)		(((a)>(b))?(a):(b))
# define CLAMP(x,lo,hi)	MIN( hi, MAX(lo,x) )

# define EMPTY_INPUT	(t_input){0}

# define PI				M_PI
# define PI_2			(M_PI * 2)
# define PI_1_2			M_PI_2

# define WALL_1			1
# define WALL_2			2
# define POINT			3

# define PORTAL_1		11
# define PORTAL_2		12
# define PORTAL_3		13
# define PORTAL_4		14
# define PORTAL_5		15

# define IS_WALL(i)		(i == WALL_1 || i == WALL_2)
# define IS_POINT(i)	(i == POINT)
# define IS_PORTAL(i)	(i >= PORTAL_1 && i <= PORTAL_5)
# define GET_PORTAL(i)	(i - PORTAL_1)

# define R				rgb.r
# define G				rgb.g
# define B				rgb.b
# define UINT			uint32_t
# define UCHAR			uint8_t
# define SCHAR			int8_t
# define KEYCODE_EXIT	53
# define KEYCODE_MULT	257
# define KEYCODE_LEFT	123
# define KEYCODE_UP		126
# define KEYCODE_RIGHT	124
# define KEYCODE_DOWN	125
# define KEYCODE_A		0
# define KEYCODE_W		13
# define KEYCODE_D		2
# define KEYCODE_S		1
# define KEYCODE_R		15
# define KEYCODE_4		65460
# define KEYCODE_6		65462

# define SCREEN_WIDTH	(2560 / 2)
# define SCREEN_HEIGHT	(1440 / 2)
# define KEY_SPEED		0.1
# define ROT_SPEED		(PI / 250.0)
# define THREAD_NUM		8

typedef	struct			s_input
{
	UINT				left : 1;
	UINT				right : 1;
	UINT				up : 1;
	UINT				down : 1;
	UINT				cwise : 1;
	UINT				ccwise : 1;
}						t_input;

typedef struct			s_vdouble
{
	double				x;
	double				y;
}						t_vdouble;

typedef struct			s_rgb
{
	UCHAR				r;
	UCHAR				g;
	UCHAR				b;
	UCHAR				a;
}						t_rgb;

typedef union			u_color
{
	t_rgb				rgb;
	uint32_t			color;
	int					colorb;
}						t_color;

typedef struct			s_vint
{
	int					x;
	int					y;
}						t_vint;

typedef struct			s_ray
{
	double				x;
	double				y;
	double				r;
}						t_ray;

typedef struct			s_cast
{
	t_vint				step;
	t_vint				map;
	t_ray				pos;
	t_vdouble			side;
	t_vdouble			delt;
	t_vdouble			cosi;
	double				dist;
	double				height;
	t_color				cola;
	t_color				colb;
}						t_cast;

typedef struct			s_map
{
	int					width;
	int					height;
	UCHAR				**data;
}						t_map;

typedef struct			s_meta
{
	char				*prog_name;
	void				*mlx;
	void				*win;
	void				*img;
	char				*pixels;
	int					sizeline;
	int					endian;
	int					bpp;
	int					inc;
	int					img_height;
	int					img_width;

	t_ray				pos;
	double				fov;

	int					is_init;
	int					is_threaded;

	int					follow_mouse;
	t_vint				prev_mouse;
	t_input				input;
	int					points;
	int					level;
	t_map				maps[5];

	char				buff[20];
}						t_meta;

typedef struct			s_tdata
{
	int					pos;
	int					thn;
	t_meta				*meta;
}						t_data;

int						main(int ac, char **av);

void					setup_maps(t_meta *meta);
void					setup_coord(t_meta *meta);
void					setup_level(t_meta *meta, int level);
void					setup_args(t_meta *meta, int ac, char **av);
void					setup_window(t_meta *meta, char *n);
void					close_window(t_meta **meta);

t_map					load_map(t_meta *meta, char *name);

void					error_memory(t_meta *meta);
void					error_thread(t_meta *meta);
void					error_file(t_meta *meta, char *name);
void					error_argument(t_meta *meta, char *arg);
void					error_chargument(t_meta *meta, char arg);
void					quit(t_meta *meta);

void					*xmalloc(size_t len, t_meta *meta);
void					*xmemalloc(size_t len, t_meta *meta);
int						xopen(char *path, int oflag, t_meta *meta);

int						ft_strcmp(char *s1, char *s2);
void					ft_putstr(char *str);
int						ft_intlen(int32_t n);
char					*ft_itoa(size_t n, char *str);
int						ft_atoi(char *str);

int						render(t_meta *meta);
int						render_threaded(t_meta *meta);
void					render_column(t_meta *m, t_cast r, int x, int s);
void					render_column_gold(t_meta *m, t_cast r, int x, int s);
void					render_column_blue(t_meta *m, t_cast r, int x, int s);

void					cast_ray(t_meta *meta, t_cast ray, int x, int level);
t_cast					get_ray(t_meta *meta, int x);

SCHAR					get_wall(t_meta *meta, int x, int y, int level);
void					set_wall(t_meta *meta, int x, int y, SCHAR val);

t_color					interpolate(t_color a, t_color b);
t_color					finterpolate(t_color a, t_color b, float ta);
void					put_pixel(int i, t_color color, t_meta *meta);
void					put_string(char *str, t_meta *m);

int						key_up(int keycode, t_meta *meta);
int						key_down(int keycode, t_meta *meta);
int						mouse_down(int button, int x, int y, t_meta *meta);
int						mouse_move(int x, int y, t_meta *meta);
int						loop_hook(t_meta *meta);
int						expose_hook(t_meta *meta);

#endif
