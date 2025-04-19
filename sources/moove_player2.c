/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moove_player2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcharbon <kcharbon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 19:52:10 by kcharbon          #+#    #+#             */
/*   Updated: 2025/04/19 14:43:47 by kcharbon         ###   ########.fr       */
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
		data->rotate += 1;
		rotate_player(data);
		data->rotate = 0;
	}
	else if (x < tmp_x)
	{
		data->rotate -= 1;
		rotate_player(data);
		data->rotate = 0;
	}
	tmp_x = x;
	return (0);
}

bool	check_position(t_pars *p, double x, double y)
{
	if (p->map[(int)y][(int)x] == '1')
		return (false);
	return (true);
}

void	move_operation(t_data *data, double *x, double *y)
{
	if (data->key_up)
	{
		*x += data->dirX * MSPEED;
		*y += data->dirY * MSPEED;
	}
	if (data->key_down)
	{
		*x -= data->dirX * MSPEED;
		*y -= data->dirY * MSPEED;
	}
	if (data->key_left)
	{
		*x += data->dirY * MSPEED;
		*y -= data->dirX * MSPEED;
	}
	if (data->key_right)
	{
		*x -= data->dirY * MSPEED;
		*y += data->dirX * MSPEED;
	}
}

void	move_player(t_data *data)
{
	double	x;
	double	y;

	x = data->posX;
	y = data->posY;
	if (data->left_rotate || data->right_rotate)
	{
		rotate_player(data);
		return ;
	}
	move_operation(data, &x, &y);
	if (check_position(data->p, x, y))
	{
		data->posX = x;
		data->posY = y;
	}
}
