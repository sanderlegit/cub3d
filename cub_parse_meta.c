/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub_parse_meta.c                                   :+:      :+:    :+:   */
/*                                                     +:+                    */
/*   By: averheij <marvin@42.fr>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/28 13:27:44 by averheij       #+#    #+#                */
/*   Updated: 2020/03/02 12:00:41 by averheij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <mlx.h>
#include "cub3d.h"

int		parse_rgb_partial(int *color, char **str, int notlast)
{
	if (ft_skip_passed_func(str, &ft_iswhitespace))
		return (1);
	if (!ft_isdigit(**str))
		return (1);
	*color = ft_atoi(*str);
	if (notlast && ft_skip_passed_func(str, &ft_isdigit))
		return (1);
	if (notlast && ft_skip_comma(str))
		return (1);
	return (0);
}

int		parse_color(t_vars *vars, char *line)
{
	int	red;
	int	green;
	int	blue;
	int	*colorpointer;

	if (!ft_strncmp(line, "C", 1))
		colorpointer = &(vars->world.colorceiling);
	else if (!ft_strncmp(line, "F", 1))
		colorpointer = &(vars->world.colorfloor);
	line++;
	if (parse_rgb_partial(&red, &line, 1))
		return (1);
	if (parse_rgb_partial(&green, &line, 1))
		return (1);
	if (parse_rgb_partial(&blue, &line, 0))
		return (1);
	if (red > 255 || blue > 255 || green > 255)
		return (1);
	*colorpointer = create_trgb(0, red, green, blue);
	return (0);
}

int		parse_res(t_vars *vars, char *line)
{
	line++;
	if (ft_skip_passed_func(&line, &ft_iswhitespace))
		return (1);
	if (!ft_isdigit(*line))
		return (1);
	vars->img.resx = ft_atoi(line);
	if (ft_skip_passed_func(&line, &ft_isdigit))
		return (1);
	if (ft_skip_passed_func(&line, &ft_iswhitespace))
		return (1);
	if (!ft_isdigit(*line))
		return (1);
	vars->img.resy = ft_atoi(line);
	if (!(vars->img.resx) || !(vars->img.resy))
		return (1);
	if (vars->img.resx > MAX_RESX)
		vars->img.resx = MAX_RESX;
	if (vars->img.resy > MAX_RESY)
		vars->img.resy = MAX_RESY;
	vars->img.halfresy = vars->img.resy / 2;
	return (0);
}

int		parse_tex(t_vars *vars, char *line)
{
	t_tex	*tex;

	if (!ft_strncmp(line, "NO", 2))
		tex = &(vars->no);
	else if (!ft_strncmp(line, "SO", 2))
		tex = &(vars->so);
	else if (!ft_strncmp(line, "WE", 2))
		tex = &(vars->we);
	else if (!ft_strncmp(line, "EA", 2))
		tex = &(vars->ea);
	else if (!ft_strncmp(line, "S ", 2))
		tex = &(vars->s);
	if (ft_skip_passed_func(&line, &ft_isalpha))
		return (1);
	if (ft_skip_passed_func(&line, &ft_iswhitespace))
		return (1);
	tex->img.img = mlx_png_file_to_image(vars->mlx,
			line, &tex->width, &tex->height);
	if (!tex->img.img)
		return (1);
	tex->img.addr = mlx_get_data_addr(tex->img.img,
			&tex->img.bits_per_pixel, &tex->img.line_length, &tex->img.endian);
	if (!tex->img.addr)
		return (1);
	return (0);
}

