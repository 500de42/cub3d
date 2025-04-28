/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcharbon <kcharbon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 20:17:55 by kcharbon          #+#    #+#             */
/*   Updated: 2025/04/28 18:08:31 by kcharbon         ###   ########.fr       */
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

void	check_first_line(char *s, t_pars *d)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] && s[i] != '1' && s[i] != ' ' && s[i] != '\t')
			free_parsing(d, "error\nNon-conforming map1");
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
