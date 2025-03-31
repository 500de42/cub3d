/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcharbon <kcharbon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 20:44:40 by kcharbon          #+#    #+#             */
/*   Updated: 2025/03/31 19:58:27 by kcharbon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	calcul_rayon(t_pars *p, t_data *d)
{
	int		stepX;
	int		stepY;
	double	sideX;
	double	sideY;
	int		sens_Wall;
	int		mapX;
	int		mapY;
	int		hit;
	int		x;
	double	distance_wall;
	int		wall_height;
	int		draw_start;
	int		draw_end;
	double	wall_x;
	int		textureX;
	
	hit = 0;
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
				sens_Wall = 0;
			}
			else
			{
				sideY += d->deltaY;
				mapY += stepY;
				sens_Wall = 1;
			}
			if (d->map[mapY][mapX] == '1')
				break ;
			;
		}
		if (sens_Wall == 1)
		{
			distance_wall = sideY - d->deltaY;
			wall_x = d->posX + distance_wall * d->ray_dirX;
		}
		else if (sens_Wall == 0)
		{
			distance_wall = sideX - d->deltaX;
			wall_x = d->posY + distance_wall * d->ray_dirY;
		}
		wall_x -= floor(wall_x);
		distance_wall = distance_wall / fabs(d->ray_dirX * d->dirX + d->ray_dirY
				* d->dirY);
		wall_height = SCREEN_HEIGHT / distance_wall;
		draw_start = -wall_height / 2 + SCREEN_HEIGHT / 2;
		draw_end = wall_height / 2 + SCREEN_HEIGHT / 2;
		if (draw_start < 0)
			draw_start = 0;
		if (draw_end > SCREEN_HEIGHT)
			draw_end = SCREEN_HEIGHT - 1;
		textureX = (int)(wall_x * 64); //64 = taille pixel
		if (sens_Wall == 0 && d->ray_dirX > 0)
			textureX = 64 - textureX - 1;
		if (sens_Wall == 1 && d->ray_dirY < 0)
			textureX = 64 - textureX - 1;
	}
}
