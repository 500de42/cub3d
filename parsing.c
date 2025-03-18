/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcharbon <kcharbon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 16:27:57 by kcharbon          #+#    #+#             */
/*   Updated: 2025/03/18 20:48:00 by kcharbon         ###   ########.fr       */
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
	if (d->map_test[y][x + 1] != ' ' && d->map_test[y][x + 1] != '\t')
		free_parsing(d, "error\nexepted format <F number,number,number>\n");
	check_rgb(d, &y, &x);
	while (d->map_test[++y])
	{
		if ((d->map_test[y][0] != 'C' && d->map_test[y][0] != 'F') && (d->F == 1
				&& d->C == 1))
			return ;
		x = -1;
		while (d->map_test[y][++x])
			if (d->map_test[y][x] != ' ' && d->map_test[y][x] != '\t')
			{
				check_rgb(d, &y, &x);
				d->save_y = y + 1;
				break ;
			}
	}
}

void	check_rgb(t_pars *d, int *y, int *x)
{
	char	**tab;
	int		nb_rgb[3];
	int		i;

	if ((*x) != 0)
		free_parsing(d, "error\nSpace not accepted\n");
	if (d->map_test[*y][0] != 'C' && d->map_test[*y][0] != 'F')
		free_parsing(d, "error\nBad character\n");
	if (ft_strlen(&d->map_test[*y][(*x)]) > 1)
		(*x) += 2;
	else
		free_parsing(d, "error\n");
	i = *x;
	while (d->map_test[*y][i])
	{
		if (d->map_test[*y][i] == ' ' || d->map_test[*y][i] == '\t')
			free_parsing(d, "error\nSpace not accepted\n");
		i++;
	}
	tab = ft_split(&d->map_test[*y][*x], ',');
	if ((!tab || !tab[0] || !tab[1] || !tab[2]) || ft_tablen(tab) != 3)
	{
		ft_free_array(tab);
		free_parsing(d, "error\nSplit RGB\n");
	}
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
	if (d->map_test[*y][0] == 'F')
		d->F++;
	else
		d->C++;
	print_array(tab);
	ft_free_array(tab);
}

int	found_the_most_insane_len(char **map)
{
	int	i;
	int	n;

	i = 0;
	n = ft_strlen(map[0]);
	while (map[i])
	{
		if (n < (int)ft_strlen(map[i]))
			n = ft_strlen(map[i]);
		i++;
	}
	return (n);
}

void	last_check(t_pars *d)
{
	char	**map;
	int		y;
	int		map_len;
	int		map_len_y;
	int		x;

	map = &d->map_test[d->save_y];
	y = -1;
	map_len = found_the_most_insane_len(map);
	map_len_y = ft_tablen(map);
	while (map[++y])
	{
		x = -1;
		while (map[y][++x] && x < map_len)
		{
			if (map[y][0] == '0')
				free_parsing(d, "error\nNon-conforming card");
			if (map[y][x] == '0' && x > 0)
				if (map[y][x - 1] <= 32)
					free_parsing(d, "error\nNon-conforming card");
			if (map[y][x] == '0' && y > 0)
				if (map[y - 1][x] <= 32)
					free_parsing(d, "error\nNon-conforming card");
			if ((x + 1 < (int)ft_strlen(map[y])) && map[y][x] == '0')
				if (map[y][x + 1] <= 32)
					free_parsing(d, "error\nNon-conforming card");
			if ((x + 1 >= (int)ft_strlen(map[y])) && map[y][x] == '0')
				free_parsing(d, "error\nNon-conforming card");
			if ((y + 1 < map_len_y) && map[y][x] == '0')
				if (map[y + 1][x] <= 32)
					free_parsing(d, "error\nNon-conforming card");
		}
	}
	printf("\nokokokokok\n");
	y = -1;
	while (map[++y])
	{
		x = -1;
		while (map[y][++x])
		{
			if (map[y][x] != '1' && map[y][x] != '0' && map[y][x] != ' '
				&& map[y][x] != 'N' && map[y][x] != 'S' && map[y][x] != 'E'
				&& map[y][x] != 'W')
				free_parsing(d, "error\nNon-conforming card");
			if (map[y][x] == 'N')
				d->N++;
			else if (map[y][x] == 'S')
				d->S++;
			else if (map[y][x] == 'E')
				d->E++;
			else if (map[y][x] == 'W')
				d->W++;
		}
	}
	if ((d->N > 0) && (d->S > 0 || d->W > 0 || d->E > 0))
		free_parsing(d, "error\nNon-conforming card");
	if ((d->S > 0) && (d->N > 0 || d->W > 0 || d->E > 0))
		free_parsing(d, "error\nNon-conforming card");
	if ((d->E > 0) && (d->S > 0 || d->W > 0 || d->N > 0))
		free_parsing(d, "error\nNon-conforming card");
	if ((d->W > 0) && (d->S > 0 || d->N > 0 || d->E > 0))
		free_parsing(d, "error\nNon-conforming card");
	printf("\nAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\n");
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
	last_check(d);
}
