/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   event_basic.c                                      :+:      :+:    :+:   */
/*                                                     +:+                    */
/*   By: averheij <marvin@42.fr>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/11 11:54:02 by averheij       #+#    #+#                */
/*   Updated: 2020/03/02 12:44:04 by averheij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <math.h>
#include <stdlib.h>
#include "cub3d.h"

int		close_window(t_vars *vars)
{
	mlx_destroy_window(vars->mlx, vars->win);
	free_everything(vars, -1, NULL);
	exit(0);
	return (0);
}

int		key_press(int keycode, t_vars *vars)
{
	if (keycode == WKEY)
		vars->move.forward = 1;
	else if (keycode == AKEY)
		vars->move.strafeleft = 1;
	else if (keycode == SKEY)
		vars->move.backward = 1;
	else if (keycode == DKEY)
		vars->move.straferight = 1;
	else if (keycode == LAKEY)
		vars->move.lookleft = 1;
	else if (keycode == RAKEY)
		vars->move.lookright = 1;
	return (0);
}

int		key_release(int keycode, t_vars *vars)
{
	if (keycode == WKEY)
		vars->move.forward = 0;
	else if (keycode == AKEY)
		vars->move.strafeleft = 0;
	else if (keycode == SKEY)
		vars->move.backward = 0;
	else if (keycode == DKEY)
		vars->move.straferight = 0;
	else if (keycode == LAKEY)
		vars->move.lookleft = 0;
	else if (keycode == RAKEY)
		vars->move.lookright = 0;
	else if (keycode == 53)
	{
		mlx_destroy_window(vars->mlx, vars->win);
		free_everything(vars, -1, NULL);
		exit(0);
	}
	return (0);
}
