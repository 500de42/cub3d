#include "../cub3d.h"

// #define TEXTURE_SIZE 64

// void	load_textures(t_data *d, t_pars *p)
// {
// 	int		i;
// 	int		width;
// 	int		height;
// 	char	*texture_path[4] = {"img/img.xpm", "img/img.xpm", "img/img.xpm",
// 			"img/img.xpm"};

// 	width = 0;
// 	height = 0;
// 	i = 0;
// 	while (i < 4)
// 	{
// 		d->tex_ptr[i] = mlx_xpm_file_to_image(d->mlx, texture_path[i], &width,
// 				&height);
// 		if (!d->tex_ptr[i])
// 			free_all(p, d, "Error\nLoad texture2\n");
// 		d->tex_addr[i] = mlx_get_data_addr(d->tex_ptr[i], &d->tex_bpp,
// 				&d->tex_line_length, &d->tex_endian);
// 		if (!d->tex_addr[i])
// 			free_all(p, d, "Error\nLoad texture1\n");
// 		d->texture_buffer[i] = (int *)d->tex_addr[i];
// 		i++;
// 	}
// 	d->tex_buff = 1;
// }

// void	put_pixel_to_img(t_data *d, int x, int y, int color)
// {
// 	if (x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT)
// 		return ;
// 	*(int *)(d->img_addr + (y * d->tex_line_length + x * (d->tex_bpp
// 					/ 8))) = color;
// }

// void	Raycasting(t_pars *p, t_data *d)
// {
// 	int		stepX;
// 	int		stepY;
// 	double	sideX;
// 	double	sideY;
// 	int		side;
// 	int		mapX;
// 	int		mapY;
// 	int		x;
// 	double	distance_wall;
// 	int		wall_height;
// 	int		draw_start;
// 	int		draw_end;
// 	double	wall_x;
// 	int		tex_x;
// 	int		tex_y;
// 	int		color;
// 	double	step;
// 	double	pos;
// 	int		dir;
// 	int		dw;

// 	x = 0;
// 	// print_array(p->map);
// 	while (x < SCREEN_WIDTH)
// 	{
// 		mapX = (int)p->x_player;
// 		mapY = (int)d->y_player;
// 		d->camX = 2 * x / (double)SCREEN_WIDTH - 1;
// 		d->ray_dirX = d->dirX + d->planeX * d->camX;
// 		d->ray_dirY = d->dirY + d->planeY * d->camX;
// 		d->deltaX = fabs(1 / d->ray_dirX); // la distance pour parcourir une
// 		d->deltaY = fabs(1 / d->ray_dirY); // case entière dans chaque direction
// 		if (d->ray_dirX < 0)
// 		{
// 			stepX = -1;
// 			sideX = ((d->posX - mapX) * d->deltaX);
// 		}
// 		else
// 		{
// 			stepX = 1;
// 			sideX = ((mapX + 1.0 - d->posX) * d->deltaX);
// 		}
// 		if (d->ray_dirY < 0)
// 		{
// 			stepY = -1;
// 			sideY = ((d->posY - mapY) * d->deltaY);
// 		}
// 		else
// 		{
// 			stepY = 1;
// 			sideY = ((mapY + 1.0 - d->posY) * d->deltaY);
// 		}
// 		while (1)
// 		{
// 			if (sideX < sideY)
// 			{
// 				sideX += d->deltaX;
// 				mapX += stepX;
// 				side = 0;
// 			}
// 			else
// 			{
// 				sideY += d->deltaY;
// 				mapY += stepY;
// 				side = 1;
// 			}
// 			if (p->map[mapY][mapX] == '1')
// 				break ;
// 		}
// 		if (side == 1)
// 		{
// 			distance_wall = sideX - d->deltaX;
// 			wall_x = d->posX + distance_wall * d->ray_dirX;
// 			if (d->ray_dirX > 0)
// 				dir = 3; // est
// 			else
// 				dir = 2; // ouest
// 		}
// 		else if (side == 0)
// 		{
// 			distance_wall = sideY - d->deltaY;
// 			wall_x = d->posY + distance_wall * d->ray_dirY;
// 			if (d->ray_dirY > 0)
// 				dir = 1; // sud
// 			else
// 				dir = 0; // nord
// 		}
// 		wall_x -= floor(wall_x);
// 		wall_height = SCREEN_HEIGHT / distance_wall;
// 		if (wall_height <= 0)
// 			wall_height = 1;
// 		draw_start = -wall_height / 2 + SCREEN_HEIGHT / 2;
// 		draw_end = wall_height / 2 + SCREEN_HEIGHT / 2;
// 		if (draw_start < 0)
// 			draw_start = 0;
// 		if (draw_end >= SCREEN_HEIGHT)
// 			draw_end = SCREEN_HEIGHT - 1;
// 		tex_x = (int)(wall_x * TEXTURE_SIZE); // 64 = taille pixel
// 		if ((side == 0 && d->ray_dirX < 0) || (side == 1 && d->ray_dirY > 0))
// 			tex_x = TEXTURE_SIZE - tex_x - 1;
// 		step = 1.0 * TEXTURE_SIZE / wall_height;
// 		pos = (draw_start - SCREEN_HEIGHT / 2 + wall_height / 2) * step;
// 		dw = 0;
// 		printf("distance_wall: %f, wall_height: %d, draw_start: %d, draw_end: %d\n", distance_wall, wall_height, draw_start, draw_end);
// 		while (dw < SCREEN_HEIGHT)
// 		{
// 			if (dw < draw_start)
// 				put_pixel_to_img(d, x, dw, d->ceiling_color);
// 			else if (dw >= draw_end)
// 				put_pixel_to_img(d, x, dw, d->floor_color);
// 			else
// 			{
// 				tex_y = (int)pos & (TEXTURE_SIZE - 1);
// 				pos += step;
// 				color = d->texture_buffer[dir][TEXTURE_SIZE * tex_y + tex_x];
// 				if (dir == 0 || dir == 1)
// 					color = (color >> 1) & 0x7F7F7F;
// 				put_pixel_to_img(d, x, dw, color);
// 			}
// 			dw++;
// 		}
// 		x++;
// 	}
// 	mlx_put_image_to_window(d->mlx, d->mlx_window, d->img_ptr, 0, 0);
// }

// // faire une fonction qui actualise la direction du joueur
