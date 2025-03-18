/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcharbon <kcharbon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 15:26:28 by kcharbon          #+#    #+#             */
/*   Updated: 2025/03/18 20:37:45 by kcharbon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "minilibx-linux/mlx.h"
#include <stdio.h>

typedef struct t_data
{
	char	**map;
	int		y_p;
	int		x_p;
}			t_data;

typedef struct t_pars
{
	int		fd;
	int		NO;
	int		SO;
	int		WE;
	int		EA;
	int		N;
	int		S;
	int		E;
	int		W;
	int		F;
	int		C;
	int		save_y;
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
void		last_check(t_pars *d);
int			found_the_most_insane_len(char **map);
/////////////// FREE /////////////////////////

void		free_parsing(t_pars *d, char *s);
