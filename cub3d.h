/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcharbon <kcharbon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 15:26:28 by kcharbon          #+#    #+#             */
/*   Updated: 2025/03/17 19:55:38 by kcharbon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "minilibx-linux/mlx.h"
#include <stdio.h>

// typedef struct t_data
// {
// 	int		fd;
// 	char	**map;
// 	int		y_p;
// 	int		x_p;
// 	t_pars	*p;
// }			t_data;

typedef struct t_pars
{
	int		fd;
	int		NO;
	int		SO;
	int		WE;
	int		EA;
	int		x_line;
	int		y_line;
	int		t_player;
	char	**map_test;

}			t_pars;

//////////////// PARSING //////////////////////

void		check_(char **av, int ac);
char		**copy_map(t_pars *data);
void		check_map(char *av, t_pars *d);
void		check_sprite(t_pars *d);
void		check_path_sprite(t_pars *d, int *y, int *x, int s);
void		check_rgb(t_pars *d, int *y, int *x);

/////////////// FREE /////////////////////////

void		free_parsing(t_pars *d, char *s);
