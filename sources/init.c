/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalvin <kalvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 20:25:17 by kcharbon          #+#    #+#             */
/*   Updated: 2025/04/05 01:43:59 by kalvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	init_data(t_data *d, t_pars *p)
{
	d->dirX = 1;
	d->dirY = 1;
	d->planeX = 0;
	d->planeY = 0;
	d->camX = 0;
	d->y_player = p->y_player;
	d->x_player = p->x_player;
	d->ceiling_color = rbg_in_int(p->ceiling_rgb);
	d->floor_color = rbg_in_int(p->floor_rgb);
	d->tex_buff = 0;
}


