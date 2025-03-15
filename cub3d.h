/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcharbon <kcharbon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 15:26:28 by kcharbon          #+#    #+#             */
/*   Updated: 2025/03/15 22:01:43 by kcharbon         ###   ########.fr       */
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

/////////////// FREE /////////////////////////

void		free_struct(t_pars *d);
