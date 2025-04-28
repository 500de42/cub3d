/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Raycasting2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcharbon <kcharbon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 20:12:36 by kcharbon          #+#    #+#             */
/*   Updated: 2025/04/28 13:10:36 by kcharbon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	load_textures(t_data *d, t_pars *p)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		d->tex_ptr[i] = mlx_xpm_file_to_image(d->mlx, p->texture_path[i],
				&d->tex_width[i], &d->tex_height[i]);
		if (!d->tex_ptr[i])
			free_all(d, "Error\nLoad texture2\n");
		d->tex_addr[i] = mlx_get_data_addr(d->tex_ptr[i], &d->tex_bpp,
				&d->tex_line_length, &d->tex_endian);
		if (!d->tex_addr[i])
			free_all(d, "Error\nLoad texture1\n");
		d->texture_buffer[i] = (int *)d->tex_addr[i];
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
	r->map_x = (int)d->pos_x;
	r->map_y = (int)d->pos_y;
	d->cam_x = 2 * r->x / (double)SCREEN_WIDTH - 1;
	d->ray_dir_x = d->dir_x + d->plane_x * d->cam_x;
	d->ray_dir_y = d->dir_y + d->plane_y * d->cam_x;
	d->delta_x = fabs(1 / d->ray_dir_x);
	d->delta_y = fabs(1 / d->ray_dir_y);
}

void	dir_ray(t_ray *r, t_data *d)
{
	if (d->ray_dir_x < 0)
	{
		r->step_x = -1;
		r->side_x = ((d->pos_x - r->map_x) * d->delta_x);
	}
	else
	{
		r->step_x = 1;
		r->side_x = ((r->map_x + 1.0 - d->pos_x) * d->delta_x);
	}
	if (d->ray_dir_y < 0)
	{
		r->step_y = -1;
		r->side_y = ((d->pos_y - r->map_y) * d->delta_y);
	}
	else
	{
		r->step_y = 1;
		r->side_y = ((r->map_y + 1.0 - d->pos_y) * d->delta_y);
	}
}

void	loop_length_ray(t_ray *r, t_data *d)
{
	while (1)
	{
		if (r->side_x < r->side_y)
		{
			r->side_x += d->delta_x;
			r->map_x += r->step_x;
			r->side = 0;
		}
		else
		{
			r->side_y += d->delta_y;
			r->map_y += r->step_y;
			r->side = 1;
		}
		if (d->p->map[r->map_y][r->map_x] == '1')
		{
			break ;
		}
	}
}
