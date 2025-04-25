/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcharbon <kcharbon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 16:27:57 by kcharbon          #+#    #+#             */
/*   Updated: 2025/04/25 15:19:15 by kcharbon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	check_(char **av, int ac)
{
	int	len;

	if (ac != 2)
	{
		ft_putstr_fd("error\nToo arguments\n", 2);
		exit(1);
	}
	len = ft_strlen(av[1]);
	if (access("img", X_OK) == -1)
	{
		ft_putstr_fd("error\nPermission denied: img\n", 2);
		exit(1);
	}
	if (len < 4 || ft_strncmp(&av[1][len - 4], ".cub", 4) != 0)
	{
		ft_putstr_fd("error\nExpected format: <map.cub>\n", 2);
		exit(1);
	}
	if (access(av[1], R_OK) == -1)
	{
		ft_printf("error\nPermission denied: %s\n", av[1]);
		exit(1);
	}
}

void	if_check_path_end(t_pars *d, char *st)
{
	if (!ft_strncmp(d->id, "NO", 2))
	{
		if (d->NO)
			free(d->texture_path[0]);
		d->texture_path[0] = ft_strdup(st);
		d->NO++;
	}
	if (!ft_strncmp(d->id, "SO", 2))
	{
		if (d->SO)
			free(d->texture_path[1]);
		d->texture_path[1] = ft_strdup(st);
		d->SO++;
	}
}

void	check_path_end(t_pars *d, char *st)
{
	if (access(st, X_OK) == -1)
	{
		free(st);
		free_parsing(d, "error\npermissions denied or bad path for sprite\n");
	}
	if (!ft_strncmp(d->id, "EA", 2))
	{
		if (d->EA)
			free(d->texture_path[2]);
		d->texture_path[2] = ft_strdup(st);
		d->EA++;
	}
	if (!ft_strncmp(d->id, "WE", 2))
	{
		if (d->WE)
			free(d->texture_path[3]);
		d->texture_path[3] = ft_strdup(st);
		d->WE++;
	}
	if_check_path_end(d, st);
	free(st);
	if (d->EA > 1 || d->NO > 1 || d->WE > 1 || d->SO > 1)
		free_parsing(d, "error\nBad path\n");
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
			if (!ft_strncmp("NO", &d->map_test[y][x], 2) || !ft_strncmp("SO",
					&d->map_test[y][x], 2) || !ft_strncmp("WE",
					&d->map_test[y][x], 2) || !ft_strncmp("EA",
					&d->map_test[y][x], 2))
			{
				d->id[0] = d->map_test[y][x];
				d->id[1] = d->map_test[y][x + 1];
				check_path_sprite(d, &y, &x);
				break ;
			}
			else if (!ft_strncmp("F ", &d->map_test[y][x], 2)
				|| !ft_strncmp("C ", &d->map_test[y][x], 2))
			{
				check_rgb(d, &y, &x);
				break ;
			}
			else
				free_parsing(d, "error\nBad character\n");
		}
	}
}
