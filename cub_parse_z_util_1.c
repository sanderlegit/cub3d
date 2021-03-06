/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub_parse_z_util_1.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: averheij <averheij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/29 13:42:34 by averheij      #+#    #+#                 */
/*   Updated: 2020/09/02 11:42:15 by averheij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <libft.h>
#include "cub3d.h"

int		is_valid_cub_char(char c)
{
	int			i;
	static char	set[8] = {' ', '0', '1', '2', 'N', 'S', 'W', 'E'};

	i = 0;
	while (i < 8)
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int		array_append(char ***map, char *line, int currentlength)
{
	char	**res;
	int		i;

	res = (char **)ft_calloc(currentlength + 1, sizeof(char *));
	if (!res)
		return (1);
	i = 0;
	while (i < currentlength)
	{
		res[i] = (*map)[i];
		i++;
	}
	res[currentlength] = line;
	free((*map));
	*map = res;
	return (0);
}

double	get_lookdir(char *c)
{
	double	lookdir;

	lookdir = -1;
	if (*c == 'N')
		lookdir = DEG90;
	else if (*c == 'E')
		lookdir = 0;
	else if (*c == 'W')
		lookdir = DEG180;
	else if (*c == 'S')
		lookdir = DEG270;
	*c = '0';
	return (lookdir);
}

int		map_line_sanitize(char **line)
{
	int		i;

	i = 0;
	while ((*line)[i])
	{
		if (!is_valid_cub_char((*line)[i]))
			return (1);
		i++;
	}
	return (0);
}

int		create_sprite(t_sprite **sprite, int x, int y)
{
	*sprite = (t_sprite *)ft_calloc(sizeof(t_sprite), 1);
	if (!sprite)
		return (1);
	(*sprite)->x = x * GRID + (GRID >> 1);
	(*sprite)->y = y * GRID + (GRID >> 1);
	return (0);
}
