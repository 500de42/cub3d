/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcharbon <kcharbon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 16:38:04 by kcharbon          #+#    #+#             */
/*   Updated: 2025/04/28 12:18:01 by kcharbon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_parsing(t_pars *d, char *s)
{
	if (d->ea)
		free(d->texture_path[2]);
	if (d->so)
		free(d->texture_path[1]);
	if (d->no)
		free(d->texture_path[0]);
	if (d->we)
		free(d->texture_path[3]);
	ft_putstr_fd(s, 2);
	ft_free_array(d->map_test);
	free(d);
	exit(1);
}

void	init_pars(t_pars *p)
{
	p->fd = -1;
	p->save_y = 0;
	p->ea = 0;
	p->no = 0;
	p->so = 0;
	p->we = 0;
	p->n = 0;
	p->c = 0;
	p->f = 0;
	p->virg = 0;
	p->j = 0;
	p->tex = 0;
	p->check = 0;
	p->pp = '\0';
	p->map = NULL;
	p->map_test = NULL;
}

int	game_loop(t_data *d)
{
	move_player(d);
	mlx_destroy_image(d->mlx, d->img_ptr);
	d->img_ptr = mlx_new_image(d->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	if (!d->img_ptr)
		free_all(d, "Error\nImg_ptr");
	d->img_addr = mlx_get_data_addr(d->img_ptr, &d->tex_bpp,
			&d->tex_line_length, &d->tex_endian);
	if (!d->img_addr)
		free_all(d, "Error\nImg_addr");
	ray(d, d->r);
	return (0);
}

void	init_mlx_and_loop(t_pars *p, t_data *d)
{
	d->mlx = mlx_init();
	if (!d->mlx)
		free_all(d, "Error\nInit mlx\n");
	d->mlx_window = mlx_new_window(d->mlx, SCREEN_WIDTH, SCREEN_HEIGHT,
			"Cub3D");
	if (!d->mlx_window)
		free_all(d, "Error\nInit mlx_window\n");
	d->p = p;
	d->img_ptr = mlx_new_image(d->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	if (!d->img_ptr)
		free_all(d, "Error\nInit mlx_img");
	d->img_addr = mlx_get_data_addr(d->img_ptr, &d->tex_bpp,
			&d->tex_line_length, &d->tex_endian);
	load_textures(d, p);
	mlx_hook(d->mlx_window, 17, 0, &close_window, d);
	mlx_hook(d->mlx_window, KeyPress, KeyPressMask, key_press_handler, d);
	mlx_hook(d->mlx_window, KeyRelease, KeyReleaseMask, key_release_handler, d);
	mlx_hook(d->mlx_window, MotionNotify, PointerMotionMask, mouse_handler, d);
	mlx_loop_hook(d->mlx, game_loop, d);
	mlx_loop(d->mlx);
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
	d->r = malloc(sizeof(t_ray));
	if (!d->r)
		free_all(d, "Error\nInit mlx\n");
	init_ray(d->r);
	init_mlx_and_loop(p, d);
}

/*
(ulimit -v 108000 ; valgrind --leak-check=full ./cub3D map.cub)
probleme quand on ce detache du mur
*/