/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Raycasting2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalvin <kalvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 20:12:36 by kcharbon          #+#    #+#             */
/*   Updated: 2025/04/21 13:32:49 by kalvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	def_per_side(t_ray *r, t_data *d)
{
	if (r->side == 0)
	{
		r->distance_wall = r->sideX - d->deltaX;
		r->wall_x = d->posY + r->distance_wall * d->ray_dirY;
		if (r->stepX > 0)
			r->dir = 3;
		else
			r->dir = 2;
	}
	else
	{
		r->distance_wall = r->sideY - d->deltaY;
		r->wall_x = d->posX + r->distance_wall * d->ray_dirX;
		if (r->stepY > 0)
			r->dir = 1;
		else
			r->dir = 0;
	}
}

void	def_before_draw(t_data *d, t_ray *r)
{
	r->wall_x -= floor(r->wall_x);
	r->distance_wall = r->distance_wall / fabs((d->ray_dirX * d->dirX)
			+ (d->ray_dirY * d->dirY));
	r->wall_height = SCREEN_HEIGHT / r->distance_wall;
	r->draw_start = -r->wall_height / 2 + SCREEN_HEIGHT / 2;
	r->draw_end = r->wall_height / 2 + SCREEN_HEIGHT / 2;
	if (r->draw_start < 0)
		r->draw_start = 0;
	if (r->draw_end > SCREEN_HEIGHT)
		r->draw_end = SCREEN_HEIGHT - 1;
	r->tex_x = (int)(r->wall_x * d->tex_width[r->dir]);
	if ((r->side == 0 && d->ray_dirX > 0) || (r->side == 1 && d->ray_dirY < 0))
		r->tex_x = d->tex_width[r->dir] - r->tex_x - 1;
	r->step = 1.0 * d->tex_height[r->dir] / r->wall_height;
	r->pos = (r->draw_start - SCREEN_HEIGHT / 2 + r->wall_height / 2) * r->step;
}

void	loop_put_pixel(t_data *d, t_ray *r)
{
	r->dw = 0;
	while (r->dw < SCREEN_HEIGHT)
	{
		if (r->dw < r->draw_start)
			put_pixel_to_img(d, r->x, r->dw, d->ceiling_color);
		else if (r->dw >= r->draw_end)
			put_pixel_to_img(d, r->x, r->dw, d->floor_color);
		else
		{
			r->tex_y = (int)r->pos;
			r->pos += r->step;
			if (r->tex_y < 0)
				r->tex_y = 0;
			if (r->tex_y >= d->tex_height[r->dir])
				r->tex_y = d->tex_height[r->dir] - 1;
			r->color = d->texture_buffer[r->dir][r->tex_y * d->tex_width[r->dir] + r->tex_x];
			put_pixel_to_img(d, r->x, r->dw, r->color);
		}
		r->dw++;
	}
}

void	ray(t_data *d, t_ray *r)
{
	r->x = 0;
	while (r->x++ < SCREEN_WIDTH)
	{
		ray_start(r, d);
		dir_ray(r, d);
		loop_length_ray(r, d);
		def_per_side(r, d);
		def_before_draw(d, r);
		loop_put_pixel(d, r);
	}
	mlx_put_image_to_window(d->mlx, d->mlx_window, d->img_ptr, 0, 0);
}
