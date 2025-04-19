/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcharbon <kcharbon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 20:44:40 by kcharbon          #+#    #+#             */
/*   Updated: 2025/04/18 20:15:42 by kcharbon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	load_textures(t_data *d, t_pars *p)
{
	int	i;
	int	width;
	int	height;

	width = 0;
	height = 0;
	i = 0;
	while (i < 4)
	{
		d->tex_ptr[i] = mlx_xpm_file_to_image(d->mlx, p->texture_path[i],
				&width, &height);
		if (!d->tex_ptr[i])
			free_all(p, d, "Error\nLoad texture2\n");
		d->tex_addr[i] = mlx_get_data_addr(d->tex_ptr[i], &d->tex_bpp,
				&d->tex_line_length, &d->tex_endian);
		if (!d->tex_addr[i])
			free_all(p, d, "Error\nLoad texture1\n");
		d->texture_buffer[i] = (int *)d->tex_addr[i];
		printf("%d %d\n\n", width, height);
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
			break ;
		}
	}
}
