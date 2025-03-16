/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalvin <kalvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 16:27:57 by kcharbon          #+#    #+#             */
/*   Updated: 2025/03/16 20:12:58 by kalvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_(char **av, int ac)
{
	int	len;

	if (ac != 2)
		exit(1);
	len = ft_strlen(av[1]);
	if (access("img/img.xpm", X_OK) == -1)
	{
		ft_putstr_fd("Acces refuser pour le fichier: img\n", 2);
		exit(1);
	}
	if (len < 4 || ft_strncmp(&av[1][len - 4], ".cub", 4) != 0)
	{
		ft_putstr_fd("Format attendu pour la map: <map.cub>\n", 2);
		exit(1);
	}
	if (access(av[1], R_OK) == -1)
	{
		ft_printf("Acces refuser pour le fichier: %s\n", av[1]);
		exit(1);
	}

}

void	check_path_sprite(t_pars *d, int *y, int *x, int s)
{
	(*x) += 2;
	while (d->map_test[*y][*x] == ' ' || d->map_test[*y][*x] == '\t')
		(*x)++;
	if (access(&d->map_test[*y][*x], X_OK) == -1)
	{
		printf("\n%c\n", d->map_test[*y][*x]);
		ft_putstr_fd("permissions denied for sprite or bad path\n", 2);
		ft_free_array(d->map_test);
		free(d);
		exit(1);
	}
	if (s == 1)
		d->EA++;
	else if (s == 2)
		d->WE++;
	else if (s == 3)
		d->NO++;
	else if (s == 4)
		d->SO++;
}

void	check_sprite(t_pars *d)
{
	int	y;
	int	x;

	y = -1;
	while (d->map_test[++y])
	{
		// printf("\n NO %d, WE %d, SO %d, EA %d\n", d->NO, d->WE, d->SO, d->EA);
		if (d->EA > 0 && d->WE > 0 && d->SO > 0 && d->NO > 0 && d->map_test[y][x] == '1')
			break ;
		x = -1;
		while (d->map_test[y][++x])
		{
			if (d->map_test[y][x] != ' ' && d->map_test[y][x] != '\t')
			{
				printf("\n%c,   %d\n", d->map_test[y][x], y);
				if (ft_strncmp("NO", &d->map_test[y][x], 2) == 0)
				{
					check_path_sprite(d, &y, &x, 3);
					break ;
				}
				else if (ft_strncmp("SO", &d->map_test[y][x], 2) == 0)
				{
					check_path_sprite(d, &y, &x, 4);
					break ;
				}
				else if (ft_strncmp("WE", &d->map_test[y][x], 2) == 0)
				{
					check_path_sprite(d, &y, &x, 2);
					break ;
				}
				else if (ft_strncmp("EA", &d->map_test[y][x], 2) == 0)
				{
					check_path_sprite(d, &y, &x, 1);
					break ;
				}
				else
				{
					printf("\n%s,   %d\n", d->map_test[y], y);
					ft_putstr_fd("bad character detected", 2);
					ft_free_array(d->map_test);
					free(d);
					exit(1);
				}
			}
		}
	}
	if (d->EA != 1 || d->WE != 1 || d->SO != 1 || d->NO != 1)
	{
		ft_putstr_fd("Double path detected\n", 2);
		ft_free_array(d->map_test);
		close(d->fd);
		free(d);
		exit(1);
	}
	printf("\nmap ok\n");
}

void	check_map(char *av, t_pars *d)
{
	d->fd = open(av, O_RDONLY);
	if (d->fd == -1)
	{
		perror("Erreur lors de l'ouverture du fichier: ");
		free(d);
		exit(1);
	}
	d->map_test = copy_map(d);
	if (!d->map_test)
	{
		close(d->fd);
		free(d);
		exit(1);
	}
	close(d->fd);
	check_sprite(d);
}
