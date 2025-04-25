/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcharbon <kcharbon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 20:17:55 by kcharbon          #+#    #+#             */
/*   Updated: 2025/04/25 13:52:41 by kcharbon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	check_value_rgb(char c, t_pars *d, char **tab)
{
	int	nb_rgb[3];

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
		j = -1;
		while (map[i][++j])
		{
			if (map[i][j] <= 32)
				j++;
			else if (map[i][j] > 32)
			{
				c = 1;
				break ;
			}
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
			free_parsing(d, "error\nNon-conforming map");
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
			free_parsing(d, "error\nNon-conforming map");
		i++;
	}
}
