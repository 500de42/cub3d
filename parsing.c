/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcharbon <kcharbon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 16:27:57 by kcharbon          #+#    #+#             */
/*   Updated: 2025/03/21 17:59:42 by kcharbon         ###   ########.fr       */
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
	int		i;
	char	*st;

	(*x) += 2;
	if (d->map_test[*y][*x] != ' ' && d->map_test[*y][*x] != '\t')
		free_parsing(d, "error\nexpected format: <NO ./path>\n");
	while (d->map_test[*y][*x] == ' ' || d->map_test[*y][*x] == '\t')
		(*x)++;
	i = (*x);
	while (d->map_test[*y][i] > 32)
		i++;
	st = malloc(sizeof(char) * ((i - (*x)) + 1));
	if (!st)
		free_parsing(d, "error\n");
	ft_strlcpy(st, &d->map_test[*y][*x], (i - (*x)) + 1);
	while (d->map_test[*y][i])
	{
		if (d->map_test[*y][i] > 32)
		{
			free(st);
			free_parsing(d, "error\nBad character for sprite\n");
		}
		i++;
	}
	if (access(st, X_OK) == -1)
	{
		free(st);
		free_parsing(d, "error\npermissions denied or bad path for sprite\n");
	}
	if (s == 1)
		d->EA++;
	else if (s == 2)
		d->WE++;
	else if (s == 3)
		d->NO++;
	else if (s == 4)
		d->SO++;
	free(st);
}

void	check_sprite(t_pars *d)
{
	int	y;
	int	x;

	y = -1;
	while (d->map_test[++y])
	{
		x = 0;
		if (d->EA > 0 && d->WE > 0 && d->SO > 0 && d->NO > 0 && d->F > 0
			&& d->C > 0)
			break ;
		x = -1;
		while (d->map_test[y][++x])
		{
			if (d->map_test[y][x] != ' ' && d->map_test[y][x] != '\t')
			{
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
				else if (ft_strncmp("F ", &d->map_test[y][x], 2) == 0)
				{
					check_rgb(d, &y, &x);
					break ;
				}
				else if (ft_strncmp("C ", &d->map_test[y][x], 2) == 0)
				{
					check_rgb(d, &y, &x);
					break ;
				}
				else
					free_parsing(d, "error\nBad character\n");
			}
		}
	}
	if ((d->EA != 1 || d->WE != 1 || d->SO != 1 || d->NO != 1 || d->C != 1
			|| d->F != 1))
		free_parsing(d, "error\nBad path or RGB number detected\n");
	d->save_y = y - 1;
}

void	check_rgb(t_pars *d, int *y, int *x)
{
	char	**tab;
	int		nb_rgb[3];
	int		i;
	int		j;
	int		k;
	char	*nb;

	if (d->map_test[*y][*x] != 'C' && d->map_test[*y][*x] != 'F')
	{
		printf("\n%c\n", d->map_test[*y][*x]);
		free_parsing(d, "error\nBad character\n");
	}
	if (d->map_test[*y][(*x) + 1] != ' ')
		free_parsing(d, "error\nexepted format <F number,number,number>\n");
	if (d->map_test[*y][*x] == 'F')
		d->F++;
	else
		d->C++;
	if (ft_strlen(&d->map_test[*y][(*x)]) > 1)
		(*x) += 2;
	else
		free_parsing(d, "error\n");
	i = *x;
	j = i;
	while (d->map_test[*y][j] <= 32)
		j++;
	k = j;
	while (d->map_test[*y][j] > 32)
		j++;
	nb = malloc(sizeof(char) * ((j - k) + 1));
	if (!nb)
		free_parsing(d, "error\nmalloc nb\n");
	ft_strlcpy(nb, &d->map_test[*y][k], (j - k) + 1);
	ft_putstr(nb);
	printf("\n%s\n", nb);
	while (d->map_test[*y][j])
	{
		if (d->map_test[*y][j] > 32)
		{
			free(nb);
			free_parsing(d, "error\nBad RGB character\n");
		}
		j++;
	}
	while (d->map_test[*y][i])
	{
		if (d->map_test[*y][i] == '-')
		{
			free(nb);
			free_parsing(d, "error\nNegative number not accepted\n");
		}
		i++;
	}
	tab = ft_split(nb, ',');
	free(nb);
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
		printf("%d %d %d\n", nb_rgb[0], nb_rgb[1], nb_rgb[2]);
		free(d);
		exit(1);
	}
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

char	**parse_map(char **map)
{
	int	i;
	int	j;
	int	c;

	i = -1;
	c = 0;
	while (map[++i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] <= 32)
				j++;
			else if (map[i][j] > 32)
			{
				c = 1;
				break ;
			}
			j++;
		}
		if (c == 1)
			break ;
	}
	if (!c)
		return (NULL);
	return (&map[i]);
}

void	check_first_line(char *s, t_pars *d)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] != '1' && s[i] != ' ' && s[i] != '\t')
			free_parsing(d, "error\nNon-conforming map5");
		i++;
	}
}

void	check_last_line(char *s, t_pars *d)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] != '1' && s[i] != ' ' && s[i] != '\t')
			free_parsing(d, "error\nNon-conforming map55");
		i++;
	}
}

void	last_check(t_pars *d)
{
	char	**map;
	int		y;
	int		map_len;
	int		map_len_y;
	int		x;

	if (ft_tablen(d->map_test) <= 7)
		free_parsing(d, "error\nEmpty map\n");
	map = &d->map_test[d->save_y + 1];
	print_array(map);
	map = parse_map(map);
	if (!map)
		free_parsing(d, "error\nEmpty map\n");
	print_array(map);
	map_len_y = ft_tablen(map);
	y = -1;
	check_first_line(map[0], d);
	check_last_line(map[map_len_y - 1], d);
	map_len = found_the_most_insane_len(map);
	while (map[++y])
	{
		x = -1;
		while (map[y][++x] && x < map_len)
		{
			if (map[y][x] == '0' && x > 0)
				if (map[y][x - 1] <= 32)
					free_parsing(d, "error\nNon-conforming card9");
			if (map[y][x] == '0' && y > 0)
				if (map[y - 1][x] <= 32)
					free_parsing(d, "error\nNon-conforming card10");
			if ((x + 1 < (int)ft_strlen(map[y])) && map[y][x] == '0')
				if (map[y][x + 1] <= 32 || !map[y][x + 1])
					free_parsing(d, "error\nNon-conforming card11");
			if ((x + 1 >= (int)ft_strlen(map[y])) && map[y][x] == '0')
				free_parsing(d, "error\nNon-conforming card12");
			if ((y + 1 < map_len_y) && map[y][x] == '0')
				if (map[y + 1][x] <= 32 || !map[y][x + 1])
					free_parsing(d, "error\nNon-conforming card13");
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
				free_parsing(d, "error\nNon-conforming card7");
			if (map[y][x] == 'N' || map[y][x] == 'S' || map[y][x] == 'E'
				|| map[y][x] == 'W')
				d->N++;
		}
	}
	if (map[y - 1][x - 1] != '1' || d->N != 1)
		free_parsing(d, "error\nNon-conforming card1");
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
		printf("\n\nrffrfrf\n\n");
		close(d->fd);
		free(d);
		exit(1);
	}
	close(d->fd);
	check_sprite(d);
	last_check(d);
}
