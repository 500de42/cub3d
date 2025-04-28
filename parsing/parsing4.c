/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcharbon <kcharbon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 20:19:00 by kcharbon          #+#    #+#             */
/*   Updated: 2025/04/28 12:14:32 by kcharbon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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
				free_parsing(d, "error\nNon-conforming map");
			if (map[y][x] == 'N' || map[y][x] == 'S' || map[y][x] == 'E'
				|| map[y][x] == 'W')
			{
				d->n++;
				d->d = map[y][x];
				d->x_player = x;
				d->y_player = y;
				d->pp = map[y][x];
			}
		}
	}
	if (map[y - 1][x - 1] != '1' || d->n != 1)
		free_parsing(d, "error\nNon-conforming map");
}

void	loop_last_check(t_pars *d, int x, int y, int map_len_y)
{
	if ((d->map[y][x] == '0' || d->map[y][x] == d->pp) && x > 0)
		if (d->map[y][x - 1] <= 32)
			free_parsing(d, "error\nNon-conforming map");
	if ((d->map[y][x] == '0' || d->map[y][x] == d->pp) && x == 0)
		free_parsing(d, "error\nNon-conforming map");
	if ((d->map[y][x] == '0' || d->map[y][x] == d->pp) && y > 0)
		if (((int)ft_strlen(d->map[y - 1]) < x) || (d->map[y - 1][x] <= 32))
			free_parsing(d, "error\nNon-conforming map");
	if ((x + 1 < (int)ft_strlen(d->map[y])) && (d->map[y][x] == '0'
		|| d->map[y][x] == d->pp))
		if (d->map[y][x + 1] <= 32 || !d->map[y][x + 1])
			free_parsing(d, "error\nNon-conforming map");
	if ((x + 1 >= (int)ft_strlen(d->map[y])) && (d->map[y][x] == '0'
		|| d->map[y][x] == d->pp))
		free_parsing(d, "error\nNon-conforming map");
	if ((y + 1 < map_len_y) && (d->map[y][x] == '0' || d->map[y][x] == d->pp))
		if (((int)ft_strlen(d->map[y + 1]) < x) || (d->map[y + 1][x] <= 32)
		|| (!d->map[y][x + 1]))
			free_parsing(d, "error\nNon-conforming map");
}

void	last_check(t_pars *d)
{
	char	**map;
	int		y;
	int		map_len;
	int		map_len_y;
	int		x;

	x = -1;
	check_start_of_map(d, &map, &map_len_y, &map_len);
	y = -1;
	check_map_space(d, map, y, x);
	while (map[++y])
	{
		x = -1;
		while (map[y][++x] && x < map_len)
			loop_last_check(d, x, y, map_len_y);
	}
}

void	check_map(char *av, t_pars *d)
{
	d->fd = open(av, O_RDONLY);
	if (d->fd == -1)
	{
		perror("error\nOpening file: \n");
		free(d);
		exit(1);
	}
	d->map_test = copy_map(d);
	if (!d->map_test)
	{
		close(d->fd);
		free(d);
		perror("Error\nCopy_map\n");
		exit(1);
	}
	close(d->fd);
	check_sprite(d);
	last_check(d);
}
