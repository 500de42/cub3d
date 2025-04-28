/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moove_player.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcharbon <kcharbon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 19:21:53 by kcharbon          #+#    #+#             */
/*   Updated: 2025/04/28 12:12:30 by kcharbon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	close_handler(t_data *data)
{
	close_window(data);
	return (0);
}

int	handle_east_north(t_data *data, int key)
{
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

int	key_press_handler(int key, t_data *data)
{
	if (key == XK_Escape)
		close_handler(data);
	if (data->p->d == 'N' || data->p->d == 'E')
		return (handle_east_north(data, key));
	if (key == XK_Left)
	{
		data->right_rotate = true;
		data->rotate += 1;
	}
	if (key == XK_Right)
	{
		data->left_rotate = true;
		data->rotate -= 1;
	}
	if (key == XK_w)
		data->key_up = true;
	if (key == XK_s)
		data->key_down = true;
	if (key == XK_d)
		data->key_left = true;
	if (key == XK_a)
		data->key_right = true;
	return (0);
}

int	release_east_north(int key, t_data *data)
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

int	key_release_handler(int key, t_data *data)
{
	if (data->p->d == 'E' || data->p->d == 'N')
		return (release_east_north(key, data));
	if (key == XK_Left)
	{
		data->right_rotate = false;
		data->rotate = 0;
	}
	if (key == XK_Right)
	{
		data->left_rotate = false;
		data->rotate = 0;
	}
	if (key == XK_w)
		data->key_up = false;
	if (key == XK_s)
		data->key_down = false;
	if (key == XK_d)
		data->key_left = false;
	if (key == XK_a)
		data->key_right = false;
	return (0);
}
