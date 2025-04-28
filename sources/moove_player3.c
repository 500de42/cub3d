/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moove_player3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcharbon <kcharbon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 12:12:59 by kcharbon          #+#    #+#             */
/*   Updated: 2025/04/28 13:09:07 by kcharbon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	rotate_player(t_data *data)
{
	double	old_plane_x;
	double	old_dir_x;
	double	angle_speed;

	old_plane_x = data->plane_x;
	old_dir_x = data->dir_x;
	angle_speed = 0.050 * data->rotate;
	data->dir_x = data->dir_x * cos(angle_speed) - data->dir_y
		* sin(angle_speed);
	data->dir_y = old_dir_x * sin(angle_speed) + data->dir_y * cos(angle_speed);
	data->plane_x = data->plane_x * cos(angle_speed) - data->plane_y
		* sin(angle_speed);
	data->plane_y = old_plane_x * sin(angle_speed) + data->plane_y
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
