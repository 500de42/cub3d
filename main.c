/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcharbon <kcharbon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 16:38:04 by kcharbon          #+#    #+#             */
/*   Updated: 2025/03/18 20:49:08 by kcharbon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// void init_struct(t_data *d)
// {
// 	d->fd = -1;
// }

void	init_pars(t_pars *p)
{
	p->fd = -1;
	p->save_y = 0;
	p->EA = 0;
	p->NO = 0;
	p->SO = 0;
	p->WE = 0;
	p->E = 0;
	p->W = 0;
	p->N = 0;
	p->S = 0;
	p->C = 0;
	p->F = 0;
}

int	main(int ac, char **av)
{
	t_pars	*d;

	check_(av, ac);
	d = malloc(sizeof(t_pars));
	if (!d)
		return (1);
	init_pars(d);
	check_map(av[1], d);
}
