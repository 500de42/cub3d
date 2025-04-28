/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcharbon <kcharbon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 20:25:17 by kcharbon          #+#    #+#             */
/*   Updated: 2025/04/28 13:04:27 by kcharbon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	init_data(t_data *d, t_pars *p)
{
	d->dir_x = 1;
	d->dir_y = 1;
	d->plane_x = 0;
	d->plane_y = 0;
	d->cam_x = 0;
	d->y_player = p->y_player;
	d->x_player = p->x_player;
	d->ceiling_color = rbg_in_int(p->ceiling_rgb);
	d->floor_color = rbg_in_int(p->floor_rgb);
	d->tex_buff = 0;
	d->rotate = 0;
	d->p = NULL;
	d->r = NULL;
	d->img_addr = NULL;
	d->img_ptr = NULL;
	d->mlx = NULL;
	d->mlx_window = NULL;
	d->tex_ptr[0] = NULL;
	d->tex_ptr[1] = NULL;
	d->tex_ptr[2] = NULL;
	d->tex_ptr[3] = NULL;
	init_dir_player(d, p);
	init_movement(d);
}

void	init_dir_player_norm(t_data *d, t_pars *p)
{
	if (p->d == 'E')
	{
		d->dir_x = 1;
		d->dir_y = 0;
		d->plane_x = 0;
		d->plane_y = 0.66;
	}
	if (p->d == 'W')
	{
		d->dir_x = -1;
		d->dir_y = 0;
		d->plane_x = 0;
		d->plane_y = 0.66;
	}
}

void	init_dir_player(t_data *d, t_pars *p)
{
	d->pos_x = d->x_player + 0.5;
	d->pos_y = d->y_player + 0.5;
	if (p->d == 'N')
	{
		d->dir_x = 0;
		d->dir_y = -1;
		d->plane_x = 0.66;
		d->plane_y = 0;
	}
	if (p->d == 'S')
	{
		d->dir_x = 0;
		d->dir_y = 1;
		d->plane_x = 0.66;
		d->plane_y = 0;
	}
	init_dir_player_norm(d, p);
}

void	init_movement(t_data *data)
{
	data->angle = M_PI / 2;
	data->left_rotate = false;
	data->right_rotate = false;
	data->key_down = false;
	data->key_left = false;
	data->key_right = false;
	data->key_up = false;
}

void	init_ray(t_ray *r)
{
	r->step_x = -1;
	r->step_y = -1;
	r->side_x = -1;
	r->side_y = -1;
	r->side = -1;
	r->map_x = -1;
	r->map_y = -1;
	r->x = -1;
	r->distance_wall = -1;
	r->wall_height = -1;
	r->draw_start = -1;
	r->draw_end = -1;
	r->wall_x = -1;
	r->tex_x = -1;
	r->tex_y = -1;
	r->color = -1;
	r->step = -1;
	r->pos = -1;
	r->dir = -1;
	r->dw = -1;
}
