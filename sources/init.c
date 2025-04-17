/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalvin <kalvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 20:25:17 by kcharbon          #+#    #+#             */
/*   Updated: 2025/04/13 16:31:59 by kalvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	init_tex(t_data *d)
{
	int i;

	i = 0;
	while (i < 4)
	{
		d->tex_addr[i] = malloc (sizeof(char));
		d->tex_ptr[i] = malloc (sizeof(void));
		d->texture_buffer[i] = malloc(sizeof(void));
		i++;
	}
}

void	init_data(t_data *d, t_pars *p)
{
	d->dirX = 1;
	d->dirY = 1;
	d->planeX = 0;
	d->planeY = 0;
	d->camX = 0;
	d->y_player = p->y_player;
	d->x_player = p->x_player;
	d->ceiling_color = rbg_in_int(p->ceiling_rgb);
	d->floor_color = rbg_in_int(p->floor_rgb);
	d->tex_buff = 0;
	d->rotate = 0;
	init_dir_player(d, p);
	init_movement(d);
}

void	init_dir_player(t_data *d, t_pars *p)
{
	d->posX = d->x_player + 0.5;
	d->posY = d->y_player + 0.5;
	if (p->d == 'N')
	{
		d->dirX = 0;
		d->dirY = -1;
		d->planeX = 0.66;
		d->planeY = 0;
	}
	else if (p->d == 'S')
	{
		d->dirX = 0;
		d->dirY = 1;
		d->planeX = 0.66;
		d->planeY = 0;
	}
	else if (p->d == 'E')
	{
		d->dirX = 1;
		d->dirY = 0;
		d->planeX = 0;
		d->planeY = 0.66;
	}
	else if (p->d == 'W')
	{
		d->dirX = -1;
		d->dirY = 0;
		d->planeX = 0;
		d->planeY = 0.66;
	}
}

void init_movement(t_data *data)
{
    data -> angle = M_PI / 2;
    // data -> posX = SCREEN_WIDTH / 2;
    // data -> posY = SCREEN_HEIGHT / 2;
    data -> left_rotate = false;
    data -> right_rotate = false;
    data -> key_down = false;
    data -> key_left = false;
    data -> key_right = false;
    data -> key_up = false;
}

void	init_ray(t_ray *r)
{
	r->stepX = -1;
	r->stepY = -1;
	r->sideX = -1;
	r->sideY = -1;
	r->side = -1;
	r->mapX = -1;
	r->mapY = -1;
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
