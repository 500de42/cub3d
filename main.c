/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcharbon <kcharbon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 16:38:04 by kcharbon          #+#    #+#             */
/*   Updated: 2025/03/14 19:29:02 by kcharbon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void init_struct(t_data *d)
{
	d->fd = -1;
}

int	main(int ac, char **av)
{
	t_data *d;
	
	check_(av, ac);
	d = malloc(sizeof (t_data));
	if (!d)
		return (1);
	check_map(av[1], d);
}
