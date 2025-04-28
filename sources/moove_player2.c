/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moove_player2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcharbon <kcharbon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 19:52:10 by kcharbon          #+#    #+#             */
/*   Updated: 2025/04/28 12:12:44 by kcharbon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	mouse_handler(int x, int y, t_data *data)
{
	static int	tmp_x = SCREEN_WIDTH / 2;

	get_mouse_position(data, x, y);
	if (x == SCREEN_WIDTH / 2)
		return (0);
	else if (x > tmp_x)
	{
		data->rotate -= 1;
		if (data->p->d == 'E' || data->p->d == 'N')
			data->rotate += 2;
		rotate_player(data);
		data->rotate = 0;
	}
	else if (x < tmp_x)
	{
		data->rotate += 1;
		if (data->p->d == 'E' || data->p->d == 'N')
			data->rotate -= 2;
		rotate_player(data);
		data->rotate = 0;
	}
	tmp_x = x;
	return (0);
}

bool	check_wall(t_pars *p, double x, double y)
{
	if (p->map[(int)(y - HITBOX)][(int)(x - HITBOX)] == '1' || p->map[(int)(y
			- HITBOX)][(int)(x + HITBOX)] == '1' || p->map[(int)(y
			+ HITBOX)][(int)(x - HITBOX)] == '1' || p->map[(int)(y
			+ HITBOX)][(int)(x + HITBOX)] == '1')
		return (false);
	return (true);
}

bool	check_position(t_pars *p, double x, double y)
{
	if (!check_wall(p, x, y))
		return (false);
	if (p->map[(int)y][(int)x] == '1')
		return (false);
	return (true);
}

void	move_operation(t_data *data, double *x, double *y)
{
	if (data->key_up)
	{
		*x += data->dir_x * MSPEED;
		*y += data->dir_y * MSPEED;
	}
	if (data->key_down)
	{
		*x -= data->dir_x * MSPEED;
		*y -= data->dir_y * MSPEED;
	}
	if (data->key_left)
	{
		*x += data->dir_y * MSPEED;
		*y -= data->dir_x * MSPEED;
	}
	if (data->key_right)
	{
		*x -= data->dir_y * MSPEED;
		*y += data->dir_x * MSPEED;
	}
}

void	move_player(t_data *data)
{
	double	x;
	double	y;

	x = data->pos_x;
	y = data->pos_y;
	if (data->left_rotate || data->right_rotate)
	{
		rotate_player(data);
		return ;
	}
	move_operation(data, &x, &y);
	if (check_position(data->p, x, y))
	{
		data->pos_x = x;
		data->pos_y = y;
	}
}
