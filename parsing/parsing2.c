/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcharbon <kcharbon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 20:17:11 by kcharbon          #+#    #+#             */
/*   Updated: 2025/04/22 19:37:07 by kcharbon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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
		free_parsing(d, "error\nBad character\n");
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
		if (d->map_test[*y][i] == '-' || d->map_test[*y][i] == '"'
			|| d->map_test[*y][i] == '\'')
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
	if ((!tab || !tab[0] || !tab[1] || !tab[2]) || ft_tablen(tab) != 3
		|| d->virg != 2)
		(ft_free_array(tab), free_parsing(d, "error\nSplit RGB\n"));
	check_value_rgb(c, d, tab);
}

void	free_cv_rgb(char **tab, t_pars *d)
{
	ft_putstr_fd("error\nBad RGB value", 2);
	ft_free_array(tab);
	ft_free_array(d->map_test);
	free(d);
	exit(1);
}
