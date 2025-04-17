/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalvin <kalvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 20:44:40 by kcharbon          #+#    #+#             */
/*   Updated: 2025/04/17 22:07:26 by kalvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

#define TEXTURE_SIZE 64

void	load_textures(t_data *d, t_pars *p)
{
	int		i;
	int		width;
	int		height;

	width = 0;
	height = 0;
	i = 0;
	while (i < 4)
	{
		d->tex_ptr[i] = mlx_xpm_file_to_image(d->mlx, p->texture_path[i], &width,
				&height);
		if (!d->tex_ptr[i])
			free_all(p, d, "Error\nLoad texture2\n");
		d->tex_addr[i] = mlx_get_data_addr(d->tex_ptr[i], &d->tex_bpp,
				&d->tex_line_length, &d->tex_endian);
		if (!d->tex_addr[i])
			free_all(p, d, "Error\nLoad texture1\n");
		d->texture_buffer[i] = (int *)d->tex_addr[i];
		printf("%d %d\n\n",width, height);
		i++;
	}
	d->tex_buff = 1;
}

void	put_pixel_to_img(t_data *d, int x, int y, int color)
{
	if (x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT)
		return ;
	*(int *)(d->img_addr + (y * d->tex_line_length + x * (d->tex_bpp
					/ 8))) = color;
}

void	ray_start(t_ray *r, t_data *d)
{
	r->mapX = (int)d->posX;
	r->mapY = (int)d->posY;
	d->camX = 2 * r->x / (double)SCREEN_WIDTH - 1;
	d->ray_dirX = d->dirX + d->planeX * d->camX;
	d->ray_dirY = d->dirY + d->planeY * d->camX;
	d->deltaX = fabs(1 / d->ray_dirX);
	d->deltaY = fabs(1 / d->ray_dirY);
}

void	dir_ray(t_ray *r, t_data *d)
{
	if (d->ray_dirX < 0)
	{
		r->stepX = -1;
		r->sideX = ((d->posX - r->mapX) * d->deltaX);
	}
	else
	{
		r->stepX = 1;
		r->sideX = ((r->mapX + 1.0 - d->posX) * d->deltaX);
	}
	if (d->ray_dirY < 0)
	{
		r->stepY = -1;
		r->sideY = ((d->posY - r->mapY) * d->deltaY);
	}
	else
	{
		r->stepY = 1;
		r->sideY = ((r->mapY + 1.0 - d->posY) * d->deltaY);
	}
}

void	loop_length_ray(t_ray *r, t_data *d)
{
	while (1)
	{
		if (r->sideX < r->sideY)
		{
			r->sideX += d->deltaX;
			r->mapX += r->stepX;
			r->side = 0;
		}
		else
		{
			r->sideY += d->deltaY;
			r->mapY += r->stepY;
			r->side = 1;
		}
		if (d->p->map[r->mapY][r->mapX] == '1')
		{
			break;
		}
	}
}

void	def_per_side(t_ray *r, t_data *d)
{
	if (r->side == 1)
	{
		r->distance_wall = r->sideY - d->deltaY;
		r->wall_x = d->posX + r->distance_wall * d->ray_dirX;
		if (d->ray_dirX > 0)
			r->dir = 3; // est
		else
			r->dir = 2; // ouest
	}
	else
	{
		r->distance_wall = r->sideX - d->deltaX;
		r->wall_x = d->posY + r->distance_wall * d->ray_dirY;
		if (d->ray_dirY > 0)
			r->dir = 1; // sud
		else
			r->dir = 0; // nord
	}
}

void	def_before_draw(t_data *d, t_ray *r)
{
	r->wall_x -= floor(r->wall_x);
	r->distance_wall = r->distance_wall / fabs((d->ray_dirX * d->dirX) + (d->ray_dirY * d->dirY));
	r->wall_height = SCREEN_HEIGHT / r->distance_wall;
	r->draw_start = -r->wall_height / 2 + SCREEN_HEIGHT / 2;
	r->draw_end = r->wall_height / 2 + SCREEN_HEIGHT / 2;
	if (r->draw_start < 0)
		r->draw_start = 0;
	if (r->draw_end > SCREEN_HEIGHT)
		r->draw_end = SCREEN_HEIGHT - 1;
	r->tex_x = (int)(r->wall_x * TEXTURE_SIZE);
	if ((r->side == 0 && d->ray_dirX > 0) || (r->side == 1 && d->ray_dirY < 0))
		r->tex_x = TEXTURE_SIZE - r->tex_x - 1;
	r->step = 1.0 * TEXTURE_SIZE / r->wall_height;
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
			r->tex_y = (int)r->pos & (TEXTURE_SIZE - 1);
			r->pos += r->step;
			r->color = d->texture_buffer[r->dir][TEXTURE_SIZE * r->tex_y + r->tex_x];
			put_pixel_to_img(d, r->x, r->dw, r->color);
		}
		r->dw++;
	}
}

void	Ray(t_data *d, t_ray *r)
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

void	Raycasting(t_pars *p, t_data *d)
{
	int		stepX;
	int		stepY;
	double	sideX;
	double	sideY;
	int		side;
	int		mapX;
	int		mapY;
	int		x;
	double	distance_wall;
	int		wall_height;
	int		draw_start;
	int		draw_end;
	double	wall_x;
	int		tex_x;
	int		tex_y;
	int		color;
	double	step;
	double	pos;
	int		dir;
	int		dw;

	x = 0;
	while (x++ < SCREEN_WIDTH)
	{
		mapX = (int)d->posX;
		mapY = (int)d->posY;
		d->camX = 2 * x / (double)SCREEN_WIDTH - 1;
		d->ray_dirX = d->dirX + d->planeX * d->camX;
		d->ray_dirY = d->dirY + d->planeY * d->camX;
		d->deltaX = fabs(1 / d->ray_dirX);
		d->deltaY = fabs(1 / d->ray_dirY);
		if (d->ray_dirX < 0)
		{
			stepX = -1;
			sideX = ((d->posX - mapX) * d->deltaX);
		}
		else
		{
			stepX = 1;
			sideX = ((mapX + 1.0 - d->posX) * d->deltaX);
		}
		if (d->ray_dirY < 0)
		{
			stepY = -1;
			sideY = ((d->posY - mapY) * d->deltaY);
		}
		else
		{
			stepY = 1;
			sideY = ((mapY + 1.0 - d->posY) * d->deltaY);
		}
		while (1)
		{
			if (sideX < sideY)
			{
				sideX += d->deltaX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideY += d->deltaY;
				mapY += stepY;
				side = 1;
			}
			if (p->map[mapY][mapX] == '1')
			{
				break;
			}
		}
		if (side == 1)
		{
			distance_wall = sideY - d->deltaY;
			wall_x = d->posX + distance_wall * d->ray_dirX;
			if (d->ray_dirX > 0)
				dir = 3; // est
			else
				dir = 2; // ouest
		}
		else
		{
			distance_wall = sideX - d->deltaX;
			wall_x = d->posY + distance_wall * d->ray_dirY;
			if (d->ray_dirY > 0)
				dir = 1; // sud
			else
				dir = 0; // nord
		}
		wall_x -= floor(wall_x);
		distance_wall = distance_wall / fabs((d->ray_dirX * d->dirX) + (d->ray_dirY * d->dirY));
		wall_height = SCREEN_HEIGHT / distance_wall;
		draw_start = -wall_height / 2 + SCREEN_HEIGHT / 2;
		draw_end = wall_height / 2 + SCREEN_HEIGHT / 2;
		if (draw_start < 0)
			draw_start = 0;
		if (draw_end > SCREEN_HEIGHT)
			draw_end = SCREEN_HEIGHT - 1;
		tex_x = (int)(wall_x * TEXTURE_SIZE);
		if ((side == 0 && d->ray_dirX > 0) || (side == 1 && d->ray_dirY < 0))
			tex_x = TEXTURE_SIZE - tex_x - 1;
		step = 1.0 * TEXTURE_SIZE / wall_height;
		pos = (draw_start - SCREEN_HEIGHT / 2 + wall_height / 2) * step;
		dw = 0;
		while (dw < SCREEN_HEIGHT)
		{
			if (dw < draw_start)
				put_pixel_to_img(d, x, dw, d->ceiling_color);
			else if (dw >= draw_end)
				put_pixel_to_img(d, x, dw, d->floor_color);
			else
			{
				tex_y = (int)pos & (TEXTURE_SIZE - 1);
				pos += step;
				color = d->texture_buffer[dir][TEXTURE_SIZE * tex_y + tex_x];
				put_pixel_to_img(d, x, dw, color);
			}
			dw++;
		}
	}
	mlx_put_image_to_window(d->mlx, d->mlx_window, d->img_ptr, 0, 0);
}
