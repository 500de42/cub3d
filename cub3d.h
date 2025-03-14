/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcharbon <kcharbon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 15:26:28 by kcharbon          #+#    #+#             */
/*   Updated: 2025/03/14 19:21:28 by kcharbon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "minilibx-linux/mlx.h"
#include <stdio.h>

typedef struct t_data
{
	char	**map_test;
	char	**map;
	int		fd;
}			t_data;

//////////////// PARSING //////////////////////

void		check_(char **av, int ac);
char		**copy_map(t_data *data);
void		check_map(char *av, t_data *d);
void		free_struct(t_data *d);
