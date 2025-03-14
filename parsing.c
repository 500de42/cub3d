/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcharbon <kcharbon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 16:27:57 by kcharbon          #+#    #+#             */
/*   Updated: 2025/03/14 19:27:49 by kcharbon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_(char **av, int ac)
{
	int	len;

	if (ac != 2)
		exit(1);
	len = ft_strlen(av[1]);
	if (access("img", X_OK) == -1)
	{
		ft_putstr_fd("Acces refuser pour le fichier: img\n", 2);
		exit(1);
	}
	if (access(av[1], R_OK) == -1)
	{
		ft_printf("Acces refuser pour le fichier: %s\n", av[1]);
		exit(1);
	}
	if (len < 4 || ft_strncmp(&av[1][len - 4], ".cub", 4) != 0)
	{
		ft_putstr_fd("Format attendu pour la map: 'map.cub'\n", 2);
		exit(1);
	}
}

void	check_map(char *av, t_data *d)
{
	d->fd = open(av, O_RDONLY);
	if (d->fd == -1)
	{
		perror("Erreur lors de l'ouverture du fichier: ");
		free_struct(d);
		exit(1);
	}
	d->map_test = copy_map(d);
	if (!d->map_test)
	{
		free_struct(d);
		exit(1);
	}
	print_array(d->map_test);
}
