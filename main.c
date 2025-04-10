/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalvin <kalvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 16:38:04 by kcharbon          #+#    #+#             */
/*   Updated: 2025/04/10 21:01:08 by kalvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_pars(t_pars *p)
{
	p->fd = -1;
	p->save_y = 0;
	p->EA = 0;
	p->NO = 0;
	p->SO = 0;
	p->WE = 0;
	p->N = 0;
	p->C = 0;
	p->F = 0;
}

int	game_loop(t_data *d)
{
	move_player(d);
	mlx_destroy_image(d->mlx, d->img_ptr);
	d->img_ptr = mlx_new_image(d->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	d->img_addr = mlx_get_data_addr(d->img_ptr, &d->tex_bpp,
			&d->tex_line_length, &d->tex_endian);
	Raycasting(d->p, d);
	return (0);
}

int	main(int ac, char **av)
{
	t_pars	*p;
	t_data	*d;

	check_(av, ac);
	p = malloc(sizeof(t_pars));
	if (!p)
		return (1);
	init_pars(p);
	check_map(av[1], p);
	d = malloc(sizeof(t_data));
	if (!d)
		free_parsing(p, "Error\nMalloc t_data");
	init_data(d, p);
	d->mlx = mlx_init();
	if (!d->mlx)
		free_all(p, d, "Error\nInit mlx\n");
	d->mlx_window = mlx_new_window(d->mlx, SCREEN_WIDTH, SCREEN_HEIGHT,
			"Cub3D");
	if (!d->mlx_window)
		free_all(p, d, "Error\nInit mlx_window\n");
	d->p = p;
	d->img_ptr = mlx_new_image(d->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	d->img_addr = mlx_get_data_addr(d->img_ptr, &d->tex_bpp,
			&d->tex_line_length, &d->tex_endian);
	load_textures(d, p);
	// Raycasting(p, d);
	mlx_hook(d->mlx_window, 17, 0, &close_window, d);
	mlx_hook(d->mlx_window, KeyPress, KeyPressMask, key_press_handler, d);
	mlx_hook(d->mlx_window, KeyRelease, KeyReleaseMask, key_release_handler, d);
	//mlx_hook(d->mlx_window, MotionNotify, PointerMotionMask, mouse_handler,d);
	mlx_loop_hook(d->mlx, game_loop, d);
	mlx_loop(d->mlx);
}
