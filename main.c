/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalvin <kalvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 16:38:04 by kcharbon          #+#    #+#             */
/*   Updated: 2025/04/03 20:59:25 by kalvin           ###   ########.fr       */
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

int	main(int ac, char **av)
{
	t_pars	*p;
	t_data	*d;
	void	*mlx;
	
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
	mlx = mlx_init();
	if (init_buff_texture(d) == -1)
		//free tout
	load_textures(d, p);
	calcul_rayon(p, d);
}
