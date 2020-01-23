/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: averheij <averheij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/20 11:57:39 by averheij       #+#    #+#                */
/*   Updated: 2020/01/23 13:56:05 by averheij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# define FOV	60
# define HALF_FOV	30
# define FRAME_WIDTH	720
# define HALF_HEIGHT	240
# define FRAME_HEIGHT	480

typedef struct	s_data {
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}				t_data;

typedef struct	s_world {
	char		**map;
	int			playerx;
	int			playery;
	float		lookdir;
	float		pxdeg;
	float		proj_plane_dist;
}				t_world;

typedef struct	s_ray {
	float		x;
	float		y;
	float		xincr;
	float		yincr;
}				t_ray;

typedef struct	s_caster {
	float		raydir;
	int			column;
	int			gridx;
	int			gridy;
	t_ray		a;
	t_ray		b;
	char		foundwall;
}				t_caster;

typedef struct	s_vars {
	void		*mlx;
	void		*win;
	t_data		img;
	t_world		world;
}				t_vars;

void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
void	my_mlx_sliver_put(t_data *data, int x, int y, int height, int color);
int		create_trgb(int t, int r, int g, int b);
int		close(t_vars *vars);
int		key_release(int keycode, t_vars *vars);
int		mouse_move(int var, int var2, int var3);
#endif