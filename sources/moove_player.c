/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moove_player.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcharbon <kcharbon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 19:21:53 by kcharbon          #+#    #+#             */
/*   Updated: 2025/04/25 13:46:32 by kcharbon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	close_handler(t_data *data)
{
	close_window(data);
	return (0);
}

int	key_press_handler(int key, t_data *data)
{
	if (key == XK_Escape)
		close_handler(data);
	if (key == XK_Left)
	{
		data->left_rotate = true;
		data->rotate -= 1;
	}
	if (key == XK_Right)
	{
		data->right_rotate = true;
		data->rotate += 1;
	}
	if (key == XK_w)
		data->key_up = true;
	if (key == XK_s)
		data->key_down = true;
	if (key == XK_d)
		data->key_right = true;
	if (key == XK_a)
		data->key_left = true;
	return (0);
}

int	key_release_handler(int key, t_data *data)
{
	if (key == XK_Left)
	{
		data->left_rotate = false;
		data->rotate = 0;
	}
	if (key == XK_Right)
	{
		data->right_rotate = false;
		data->rotate = 0;
	}
	if (key == XK_w)
		data->key_up = false;
	if (key == XK_s)
		data->key_down = false;
	if (key == XK_d)
		data->key_right = false;
	if (key == XK_a)
		data->key_left = false;
	return (0);
}

void	rotate_player(t_data *data)
{
	double	old_plane_x;
	double	old_dir_x;
	double	angle_speed;

	old_plane_x = data->planeX;
	old_dir_x = data->dirX;
	angle_speed = 0.050 * data->rotate;
	data->dirX = data->dirX * cos(angle_speed) - data->dirY * sin(angle_speed);
	data->dirY = old_dir_x * sin(angle_speed) + data->dirY * cos(angle_speed);
	data->planeX = data->planeX * cos(angle_speed) - data->planeY
		* sin(angle_speed);
	data->planeY = old_plane_x * sin(angle_speed) + data->planeY
		* cos(angle_speed);
}

void	get_mouse_position(t_data *data, int x, int y)
{
	if (x > SCREEN_WIDTH - DIST_EDGE_MOUSE_WRAP)
	{
		x = DIST_EDGE_MOUSE_WRAP;
		mlx_mouse_move(data->mlx, data->mlx_window, x, y);
	}
	if (x < DIST_EDGE_MOUSE_WRAP)
	{
		x = SCREEN_WIDTH - DIST_EDGE_MOUSE_WRAP;
		mlx_mouse_move(data->mlx, data->mlx_window, x, y);
	}
}
