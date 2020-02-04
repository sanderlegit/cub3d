/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   event_basic.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: averheij <averheij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/20 12:58:52 by averheij       #+#    #+#                */
/*   Updated: 2020/02/03 12:51:44 by averheij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <math.h>
#include <stdlib.h>
#include "cub3d.h"

#include <stdio.h>

int		close(t_vars *vars)
{
	mlx_destroy_window(vars->mlx, vars->win);
	exit(0);
}

int     key_press(int keycode, t_vars *vars)
{
	printf("PRESS code: %d\n", keycode);
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
	printf("RELEASE code: %d\n", keycode);
    /*if (keycode == 53)*/
    if (keycode == 65307)
	{
		mlx_destroy_window(vars->mlx, vars->win);
		exit(0);
	}
    else if (keycode == WKEY)
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
	return (0);
}

int		mouse_move(int x, int y)
{
	printf("x: %d y: %d\n", x, y);
	return (0);
}
