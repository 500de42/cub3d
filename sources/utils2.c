/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcharbon <kcharbon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 19:49:25 by kcharbon          #+#    #+#             */
/*   Updated: 2025/04/22 19:29:19 by kcharbon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	free_all(t_data *d, char *s)
{
	ft_putstr_fd(s, 2);
	if (d)
	{
		free_data_close(d);
		destroy_texture(d);
		if (d->img_ptr)
			mlx_destroy_image(d->mlx, d->img_ptr);
		if (d->img_addr)
			free(d->img_addr);
		if (d->mlx_window && d->mlx)
			mlx_destroy_window(d->mlx, d->mlx_window);
		if (d->mlx)
		{
			mlx_destroy_display(d->mlx);
			free(d->mlx);
		}
		if (d->r)
			free(d->r);
		free(d);
	}
	exit(1);
}

void	free_data_close(t_data *d)
{
	if (d->p->map_test)
		ft_free_array(d->p->map_test);
	if (d->p->EA && d->p->texture_path[3])
		free(d->p->texture_path[3]);
	if (d->p->SO && d->p->texture_path[1])
		free(d->p->texture_path[1]);
	if (d->p->NO && d->p->texture_path[0])
		free(d->p->texture_path[0]);
	if (d->p->WE && d->p->texture_path[2])
		free(d->p->texture_path[2]);
	free(d->p);
}

int	close_window(t_data *d)
{
	if (d->p)
		free_data_close(d);
	if (d)
	{
		mlx_destroy_image(d->mlx, d->img_ptr);
		destroy_texture(d);
		if (d->mlx_window && d->mlx)
			mlx_destroy_window(d->mlx, d->mlx_window);
		if (d->mlx)
		{
			mlx_destroy_display(d->mlx);
			free(d->mlx);
		}
		free(d->r);
		free(d);
	}
	exit(0);
	return (0);
}
