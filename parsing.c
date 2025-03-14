/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcharbon <kcharbon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 16:27:57 by kcharbon          #+#    #+#             */
/*   Updated: 2025/03/14 16:39:40 by kcharbon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_(char **av, int ac)
{
	int	len;

    if (ac <= 1)
        exit(1);
	len = ft_strlen(av[1]);
	if (access("img", X_OK) == -1)
	{
		ft_printf("Acces refuser pour le fichier: img\n");
		exit(1);
	}
	if (access(av[1], X_OK) == -1)
	{
		ft_printf("Acces refuser pour le fichier: %s\n", av[1]);
		exit(1);
	}
	if (len < 4 || ft_strncmp(&av[1][len - 4], ".cub", 4) != 0)
	{
		ft_printf("Format attendu pour la map: <.cub>\n");
		exit(1);
	}
}

