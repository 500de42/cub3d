/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcharbon <kcharbon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 15:26:28 by kcharbon          #+#    #+#             */
/*   Updated: 2025/03/22 21:52:33 by kcharbon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft/libft.h"
# include "minilibx-linux/mlx.h"
# include <math.h>
# include <stdio.h>

# ifndef M_PI
#  define M_PI 3.14159265
# endif

typedef struct t_data
{
	char	**map;
	int		y_player;
	int		x_player;
	int		dirX;
	int		dirY;
	int		planeX;
	int		planeY;
	int		camX;
	int		camY;
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
	int		y_player;
	int		x_player;
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

//////////////// RAYCASTING ////////////////////

/////////////// FREE ///////////////////////////

void		free_parsing(t_pars *d, char *s);

///////////////// UTILS/////////////////////////

void		init_data(t_data *d);
void		init_pars(t_pars *p);

#endif
