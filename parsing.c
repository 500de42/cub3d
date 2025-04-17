/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalvin <kalvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 16:27:57 by kcharbon          #+#    #+#             */
/*   Updated: 2025/04/17 21:50:31 by kalvin           ###   ########.fr       */
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
	if (d->tex)
	    ft_free_array(d->texture_path);
	ft_putstr_fd(s, 2);
	ft_free_array(d->map_test);
	free(d);
	exit(1);
}

void	check_path_end(t_pars *d, char *st)
{
	if (access(st, X_OK) == -1)
	{
		free(st);
		free_parsing(d, "error\npermissions denied or bad path for sprite\n");
	}
	d->tex = 1;
	if (!ft_strncmp(d->id, "EA", 2))
	{
		d->texture_path[2] = ft_strdup(st);
		d->EA++;
	}
	else if (!ft_strncmp(d->id, "WE", 2))
	{
		d->texture_path[3] = ft_strdup(st);
		d->WE++;
	}
	else if (!ft_strncmp(d->id, "NO", 2))
	{
		d->texture_path[0] = ft_strdup(st);
		d->NO++;
	}
	else if (!ft_strncmp(d->id, "SO", 2))
	{
		d->texture_path[1] = ft_strdup(st);
		d->SO++;
	}
	free(st);
}

void	check_path_sprite(t_pars *d, int *y, int *x)
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
	check_path_end(d, st);
}

void	check_texture_and_pos(t_pars *d, int y, int x)
{
	while (d->map_test[y][++x])
	{
		if (d->map_test[y][x] != ' ' && d->map_test[y][x] != '\t')
		{
			if (!ft_strncmp("NO", &d->map_test[y][x], 2) ||
					!ft_strncmp("SO", &d->map_test[y][x], 2) ||
						!ft_strncmp("WE", &d->map_test[y][x], 2) ||
							!ft_strncmp("EA", &d->map_test[y][x], 2))
			{
				d->id[0] = d->map_test[y][x];
				d->id[1] = d->map_test[y][x + 1];
				d->id[2] = '\0';
				check_path_sprite(d, &y, &x);
				break ;
			}
			else if (!ft_strncmp("F ", &d->map_test[y][x], 2) ||
				!ft_strncmp("C ", &d->map_test[y][x], 2))
			{
				check_rgb(d, &y, &x);
				break ;
			}
			else
				free_parsing(d, "error\nBad character\n");
		}
	}
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
		check_texture_and_pos(d, y, x);
	}
	if ((d->EA != 1 || d->WE != 1 || d->SO != 1 || d->NO != 1 || d->C != 1
			|| d->F != 1))
		free_parsing(d, "error\nBad path or RGB number detected\n");
	d->save_y = y - 1;
}

void	first_check_rgb(t_pars *d, int *y, int *x, char *c)
{
	if (d->map_test[*y][*x] != 'C' && d->map_test[*y][*x] != 'F')
	{
		printf("\n%c\n", d->map_test[*y][*x]);
		free_parsing(d, "error\nBad character\n");
	}
	*c = d->map_test[*y][*x];
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
}

void	loops_check_rgb(t_pars *d, int i, int *y, char *nb)
{
	d->virg = 0;
	while (d->map_test[*y][d->j])
	{
		if (d->map_test[*y][d->j] > 32)
		{
			free(nb);
			free_parsing(d, "error\nBad RGB character\n");
		}
		d->j++;
	}
	while (d->map_test[*y][i])
	{
		if (d->map_test[*y][i] == '-')
		{
			free(nb);
			free_parsing(d, "error\nNegative number not accepted\n");
		}
		if (d->map_test[*y][i] == ',')
			d->virg++;
		i++;
	}
}

void	check_rgb(t_pars *d, int *y, int *x)
{
	char	**tab;
	int		i;
	int		k;
	char	*nb;
	char	c;

	first_check_rgb(d, y, x, &c);
	i = *x;
	d->j = i;
	while (d->map_test[*y][d->j] <= 32)
		d->j++;
	k = d->j;
	while (d->map_test[*y][d->j] > 32)
		d->j++;
	nb = malloc(sizeof(char) * ((d->j - k) + 1));
	if (!nb)
		free_parsing(d, "error\nmalloc nb\n");
	ft_strlcpy(nb, &d->map_test[*y][k], (d->j - k) + 1);
	loops_check_rgb(d, i, y, nb);
	tab = ft_split(nb, ',');
	free(nb);
	if ((!tab || !tab[0] || !tab[1] || !tab[2]) || ft_tablen(tab) != 3 || d->virg != 2)
		(ft_free_array(tab), free_parsing(d, "error\nSplit RGB\n"));
	check_value_rgb(c, d, tab);
}

void free_cv_rgb(char **tab, t_pars *d)
{
	ft_putstr_fd("error\nBad RGB value", 2);
	ft_free_array(tab);
	ft_free_array(d->map_test);
	free(d);
	exit(1);
}

void	check_value_rgb(char c, t_pars *d, char **tab)
{
	int		nb_rgb[3];
	
	nb_rgb[0] = ft_atoll(tab[0]);
	nb_rgb[1] = ft_atoll(tab[1]);
	nb_rgb[2] = ft_atoll(tab[2]);
	if ((nb_rgb[0] < 0 || nb_rgb[0] > 255) || (nb_rgb[1] < 0 || nb_rgb[1] > 255)
		|| (nb_rgb[2] < 0 || nb_rgb[2] > 255))
		free_cv_rgb(tab, d);
	if (c == 'F')
	{
		d->floor_rgb[0] = ft_atoll(tab[0]);
		d->floor_rgb[1] = ft_atoll(tab[1]);
		d->floor_rgb[2] = ft_atoll(tab[2]);
	}
	else if (c == 'C')
	{
		d->ceiling_rgb[0] = ft_atoll(tab[0]);
		d->ceiling_rgb[1] = ft_atoll(tab[1]);
		d->ceiling_rgb[2] = ft_atoll(tab[2]);
	}
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

void	check_start_of_map(t_pars *d, char ***map, int *map_len_y, int *map_len)
{
	if (ft_tablen(d->map_test) <= 7)
		free_parsing(d, "error\nEmpty map\n");
	*map = &d->map_test[d->save_y + 1];
	*map = parse_map(*map);
	if (!*map)
		free_parsing(d, "error\nEmpty map\n");
	d->map = parse_map(*map);
	*map_len_y = ft_tablen(*map);
	check_first_line((*map)[0], d);
	check_last_line((*map)[*map_len_y - 1], d);
	*map_len = found_the_most_insane_len(*map);
	d->len = *map_len;
}

void	check_map_space(t_pars *d, char **map, int y, int x)
{
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
			{
				d->N++;
				d->d = map[y][x];
				d->x_player = x;
				d->y_player = y;
			}
		}
	}
	if (map[y - 1][x - 1] != '1' || d->N != 1)
		free_parsing(d, "error\nNon-conforming card1");
}

void	loop_last_check(t_pars *d, int x, int y, int map_len_y)
{
	if (d->map[y][x] == '0' && x > 0)
		if (d->map[y][x - 1] <= 32)
			free_parsing(d, "error\nNon-conforming card9");
	if (d->map[y][x] == '0' && y > 0)
		if (d->map[y - 1][x] <= 32)
			free_parsing(d, "error\nNon-conforming card10");
	if ((x + 1 < (int)ft_strlen(d->map[y])) && d->map[y][x] == '0')
		if (d->map[y][x + 1] <= 32 || !d->map[y][x + 1])
			free_parsing(d, "error\nNon-conforming card11");
	if ((x + 1 >= (int)ft_strlen(d->map[y])) && d->map[y][x] == '0')
		free_parsing(d, "error\nNon-conforming card12");
	if ((y + 1 < map_len_y) && d->map[y][x] == '0')
		if (d->map[y + 1][x] <= 32 || !d->map[y][x + 1])
			free_parsing(d, "error\nNon-conforming card13");	
}

void	last_check(t_pars *d)
{
	char	**map;
	int		y;
	int		map_len;
	int		map_len_y;
	int		x;

	check_start_of_map(d, &map, &map_len_y, &map_len);
	y = -1;
	while (map[++y])
	{
		x = -1;
		while (map[y][++x] && x < map_len)
			loop_last_check(d, x, y, map_len_y);
	}
	check_map_space(d, map, y, x);
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
