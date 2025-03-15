/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcharbon <kcharbon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 16:38:04 by kcharbon          #+#    #+#             */
/*   Updated: 2025/03/15 21:17:55 by kcharbon         ###   ########.fr       */
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
	p->x_line = 0;
	p->y_line = 0;
	p->EA = 0;
	p->NO = 0;
	p->SO = 0;
	p->WE = 0;
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
