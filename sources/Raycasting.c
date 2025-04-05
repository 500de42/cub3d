/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalvin <kalvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 20:44:40 by kcharbon          #+#    #+#             */
/*   Updated: 2025/04/05 02:29:41 by kalvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

#define TEXTURE_SIZE 64

// int init_buff_texture(t_data *d)
// {
// 	int i = 0;

// 	while (i++ < 4)
// 	{
// 		d->texture_buffer[i] = malloc(TEXTURE_SIZE * TEXTURE_SIZE * (sizeof (int)));
// 		if (!d->texture_buffer[i])
// 			return (-1);
// 	}
// 	return(0);
// }

void load_textures(t_data *d, t_pars *p)
{
	int i;
	int	width;
	int	height;
	char *texture_path[4] = {
		"img/img",
		"img/img",
		"img/img",
		"img/img"
	};
	i = 0;
	while (i < 4)
	{
		d->ptr_img[i] = mlx_xpm_file_to_image(d->mlx, (char *)texture_path[i], &width, &height);
		if (!d->ptr_img[i])
			free_all(p, d, "Error\nLoad texture\n");
		d->tex_addr[i] = mlx_get_data_addr(d->ptr_img[i], &d->tex_bpp, &d->tex_line_length, &d->tex_endian);
		d->texture_buffer[i] = (int *)d->tex_addr[i];
		i++;
	}
	d->tex_buff = 1;
}

void put_pixel_to_img(t_data *d, int x, int y, int color, int dir)
{
	if (x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT)
		return ;
	*(int *)(d->tex_addr[dir] + (y * d->tex_line_length + x * (d->tex_bpp / 8))) = color;
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
	int 	tex_y;
	int		color;
	double 	step;
	double	pos;
	int		dir;
	int		dw;
	
	x = 0;
	d->posX = d->x_player + 0.5;
	d->posY = d->y_player + 0.5;
	mapX = d->x_player;
	mapY = d->y_player;
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
	while (x++ < SCREEN_WIDTH)
	{
		d->camX = 2 * x / (double)SCREEN_WIDTH - 1;
		d->ray_dirX = d->dirX + d->planeX * d->camX;
		d->ray_dirY = d->dirY + d->planeY * d->camX;
		d->deltaX = fabs(1 / d->ray_dirX); // la distance pour parcourir une
		d->deltaY = fabs(1 / d->ray_dirY); // case entière dans chaque direction
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
			if (p->map_test[mapY][mapX] == '1')
				break ;
		}
		if (side == 1)
		{
			distance_wall = sideY - d->deltaY;
			wall_x = d->posX + distance_wall * d->ray_dirX;
			if (d->ray_dirX > 0)
				dir = 3; //est
			else
				dir = 2;//ouest
		}
		else if (side == 0)
		{
			distance_wall = sideX - d->deltaX;
			wall_x = d->posY + distance_wall * d->ray_dirY;
			if (d->ray_dirY > 0)
				dir = 1;//sud
			else
				dir = 0;//nord
		}
		wall_x -= floor(wall_x);
		distance_wall = distance_wall / fabs((d->ray_dirX * d->dirX)
				+ (d->ray_dirY * d->dirY));
		wall_height = SCREEN_HEIGHT / distance_wall;
		draw_start = -wall_height / 2 + SCREEN_HEIGHT / 2;
		draw_end = wall_height / 2 + SCREEN_HEIGHT / 2;
		if (draw_start < 0)
			draw_start = 0;
		if (draw_end > SCREEN_HEIGHT)
			draw_end = SCREEN_HEIGHT - 1;
		tex_x = (int)(wall_x * TEXTURE_SIZE); // 64 = taille pixel
		if ((side == 0 && d->ray_dirX > 0) || (side == 1 && d->ray_dirY < 0))
			tex_x = TEXTURE_SIZE - tex_x - 1;
		step = 1.0 * TEXTURE_SIZE / wall_height;
		pos = (draw_start - SCREEN_HEIGHT / 2 + wall_height / 2) * step;
		dw = 0;
		while (dw < SCREEN_HEIGHT)
		{
			if (dw < draw_start)
				put_pixel_to_img(d, x, dw, d->ceiling_color, 0);
			else if (dw >= draw_end)
				put_pixel_to_img(d, x, dw, d->floor_color, 0);
			else
			{
				tex_y = (int)pos & (TEXTURE_SIZE - 1);
				pos += step;
				color = d->texture_buffer[dir][TEXTURE_SIZE * tex_y + tex_x];
				if (dir == 0 || dir == 1)
					color = (color >> 1) & 0x7F7F7F;
				put_pixel_to_img(d, x, dw, color, dir);
			}
			dw++;
		}
	}
}

//faire une fonction qui actualise la direction du joueur
