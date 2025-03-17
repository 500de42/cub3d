/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcharbon <kcharbon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 16:27:57 by kcharbon          #+#    #+#             */
/*   Updated: 2025/03/17 20:17:40 by kcharbon         ###   ########.fr       */
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
		ft_putstr_fd("error\nAcces refuser pour le fichier: img\n", 2);
		exit(1);
	}
	if (len < 4 || ft_strncmp(&av[1][len - 4], ".cub", 4) != 0)
	{
		ft_putstr_fd("error\nFormat attendu pour la map: <map.cub>\n", 2);
		exit(1);
	}
	if (access(av[1], R_OK) == -1)
	{
		ft_printf("error\nAcces refuser pour le fichier: %s\n", av[1]);
		exit(1);
	}
}

void	free_parsing(t_pars *d, char *s)
{
	ft_putstr_fd(s, 2);
	ft_free_array(d->map_test);
	free(d);
	exit(1);
}

void	check_path_sprite(t_pars *d, int *y, int *x, int s)
{
	(*x) += 2;
	if (d->map_test[*y][*x] != ' ' && d->map_test[*y][*x] != '\t')
		free_parsing(d, "error\nexpected format: <NO ./path>\n");
	while (d->map_test[*y][*x] == ' ' || d->map_test[*y][*x] == '\t')
		(*x)++;
	if (access(&d->map_test[*y][*x], X_OK) == -1)
		free_parsing(d, "error\npermissions denied or bad path for sprite\n");
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
		x = 0;
		if (d->EA > 0 && d->WE > 0 && d->SO > 0 && d->NO > 0
			&& d->map_test[y][x] == 'F')
			break ;
		x = -1;
		while (d->map_test[y][++x])
		{
			if (d->map_test[y][x] != ' ' && d->map_test[y][x] != '\t')
			{
				if ((d->EA != 1 || d->WE != 1 || d->SO != 1 || d->NO != 1)
					&& d->map_test[y][x] == 'F')
					free_parsing(d, "Bad path number detected\n");
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
					free_parsing(d, "error\nbad character detected");
			}
		}
	}
	if ((d->EA != 1 || d->WE != 1 || d->SO != 1 || d->NO != 1))
		free_parsing(d, "error\nBad path number detected\n");
	printf("%c\n", d->map_test[y][x]);
	if (d->map_test[y][x + 1] != ' ' && d->map_test[y][x + 1] != '\t')
		free_parsing(d, "error\nexepted format <F number,number,number>\n");
	check_rgb(d, &y, &x);
}

void	check_rgb(t_pars *d, int *y, int *x)
{
	char	**tab;
	int		nb_rgb[3];
	int i;

	(*x) += 2;
	i = *x;
	while(d->map_test[*y][i])
	{
		if (d->map_test[*y][i] == ' ' || d->map_test[*y][i] == '\t')
			free_parsing(d, "error\nSpace not accepted\n");
		i++;
	}
	tab = ft_split(&d->map_test[*y][*x], ',');
	if ((!tab || !tab[0] || !tab[1] || !tab[2]) || ft_tablen(tab) > 3)
		free_parsing(d, "error\nSplit RGB\n");
	nb_rgb[0] = ft_atoll(tab[0]);
	nb_rgb[1] = ft_atoll(tab[1]);
	nb_rgb[2] = ft_atoll(tab[2]);
	if ((nb_rgb[0] < 0 || nb_rgb[0] > 255) || (nb_rgb[1] < 0 || nb_rgb[1] > 255)
		|| (nb_rgb[2] < 0 || nb_rgb[2] > 255))
	{
		ft_putstr_fd("error\nBad RGB value", 2);
		ft_free_array(tab);
		ft_free_array(d->map_test);
		free(d);
		exit(1);
	}
	print_array(tab);
}

void	check_map(char *av, t_pars *d)
{
	d->fd = open(av, O_RDONLY);
	if (d->fd == -1)
	{
		perror("error\nErreur lors de l'ouverture du fichier: ");
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
