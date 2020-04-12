/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub_parse_map.c                                    :+:      :+:    :+:   */
/*                                                     +:+                    */
/*   By: averheij <averheij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/20 11:57:39 by averheij       #+#    #+#                */
/*   Updated: 2020/03/09 12:40:49 by averheij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <get_next_line.h>
#include <libft.h>
#include <mlx.h>
#include "cub3d.h"

void	printf_map(char **map, int map_height)
{
	int     y;

    y = 0;
    while (y < map_height)
    {
        printf("%s\n", map[y]);
        y++;
    }
    printf("\n");
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

int		map_line_sanitize(char *line)
{
	char	*res;
	int		i;
	int		valid;

	i = 0;
	while (line[i])
	{
		if (!is_valid_cub_char(*line))
			return (1);
		i++;
	}
	return (0);
}

int     ismap(int y, int x, t_vars *vars)
{
	if (y < 0 || y >= vars->world.map_height)
		return (0);
	vars->world.map_width = ft_strlen(vars->world.map[y]);
	if (x < 0 || x >= vars->world.map_width)
		return (0);
	return (1);

}

int     validate_map_edges(int y, int x, char **map, t_vars *vars)
{
	int		invalid;

    printf_map(map, vars->world.map_height);
	invalid = 0;
	if (map[y][x] == '0' || map[y][x] == ' ')
		map[y][x] = 'O';
    if (ismap(y - 1, x, vars))
	{
        if ((map[y - 1][x] == '0' || map[y - 1][x] == ' ')
			&& validate_map_edges(y - 1, x, map, vars))
			invalid = 1;
	}
	else
		invalid = 1;
    if (ismap(y + 1, x, vars))
	{
        if ((map[y + 1][x] == '0' || map[y + 1][x] == ' ')
			&& validate_map_edges(y + 1, x, map, vars))
			invalid = 1;
	}
	else
		invalid = 1;
    if (ismap(y, x - 1, vars))
	{
        if ((map[y][x - 1] == '0' || map[y][x - 1] == ' ')
			&& validate_map_edges(y, x - 1, map, vars))
			invalid = 1;
	}
	else
		invalid = 1;
    if (ismap(y, x + 1, vars))
	{
        if ((map[y][x + 1] == '0' || map[y][x + 1] == ' ')
			&& validate_map_edges(y, x + 1, map, vars))
			invalid = 1;
	}
	else
		invalid = 1;
	if (ismap(y + 1, x, vars) && map[y + 1][x] == '1' &&
		ismap(y, x + 1, vars) && map[y][x + 1] == '1')
			map[y + 1][x + 1] = '1';
	if (ismap(y - 1, x, vars) && map[y - 1][x] == '1' &&
		ismap(y, x + 1, vars) && map[y][x + 1] == '1')
			map[y - 1][x + 1] = '1';
	if (ismap(y - 1, x, vars) && map[y - 1][x] == '1' &&
		ismap(y, x - 1, vars) && map[y][x - 1] == '1')
			map[y - 1][x - 1] = '1';
	if (ismap(y + 1, x, vars) && map[y + 1][x] == '1' &&
		ismap(y, x - 1, vars) && map[y][x - 1] == '1')
			map[y + 1][x - 1] = '1';
	return (invalid);
}

int		validate_map(char **map, t_vars *vars)
{
	int		playerfound;
	int		i;
	int		i2;

    playerfound = 0;
	i = 0;
	while (i < vars->world.map_height)
	{
		i2 = 0;
		while (map[i][i2])
		{
			if (map[i][i2] == 'N')
				vars->world.lookdir = DEG90;
			else if (map[i][i2] == 'E')
				vars->world.lookdir = 0;
			else if (map[i][i2] == 'W')
				vars->world.lookdir = DEG180;
			else if (map[i][i2] == 'S')
				vars->world.lookdir = DEG270;
			if (map[i][i2] == 'N' || map[i][i2] == 'E' ||
					map[i][i2] == 'W' || map[i][i2] == 'S')
			{
				vars->world.playerx = GRID * i2 + (GRID / 2);
				vars->world.playery = GRID * i + (GRID / 2);
                if (playerfound || validate_map_edges(i, i2, map, vars))
                    return (1);
                printf_map(map, vars->world.map_height);
                playerfound = 1;
			}
			i2++;
		}
		i++;
	}
	return (0);
}

int		parse_map(t_vars *vars, int fd)
{
	int		ret;
	char	*line;

	vars->world.map_height = 0;
	while (1)
	{
		line = NULL;
		ret = get_next_line(fd, &line);
		if (ret == 0)
			break ;
		if (ret == -1)
			free_everything(vars, fd, line);
		if (map_line_sanitize(line))
			return (free_everything(vars, fd, line));
		if (array_append(&(vars->world.map), line, vars->world.map_height))
			return (free_everything(vars, fd, line));
		vars->world.map_height++;
	}
	free(line);
	if (validate_map(vars->world.map, vars))
		return (free_everything(vars, fd, NULL));
	//2d array of t_sprite pointers with maps dimensions
	//loop over map
	//malloc for a link at every '2' and assign pointer
	//lst
	//	int	gridx;
	//	int	gridy;
	//	int queued;
	//	t_sprite *next
	//	t_sprite *prev
	vars->world.max_y = vars->world.map_height * GRID;
	return (0);
}
