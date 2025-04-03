/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalvin <kalvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 15:26:28 by kcharbon          #+#    #+#             */
/*   Updated: 2025/04/03 20:58:09 by kalvin           ###   ########.fr       */
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
# ifndef SCREEN_WIDTH
#  define SCREEN_WIDTH 1920
# endif
# ifndef SCREEN_HEIGHT
#  define SCREEN_HEIGHT 1080
# endif


typedef struct t_data
{
	char	**map;
	double	cam;
	double	ray_dirX;
	double	ray_dirY;
	double	deltaX;
	double	deltaY;
	double	camX;
	double	posX;
	double	posY;
	double	dirX;
	double	dirY;
	int		y_player;
	int		x_player;
	int		planeX;
	int		planeY;
	int		*buff_texture[4];
	int 	*texture_buffer[4]; // Stocke les textures sous forme de tableau 1D
	void 	*ptr_img[4];      // Pointeurs vers les images MLX
	char 	*tex_addr[4];      // Adresses mémoire des textures
	int 	tex_bpp, tex_line_length, tex_endian;
	void	*window;
	void	*mlx;
}			t_data;

typedef struct t_pars
{
	int		fd;
	int		NO;
	int		SO;
	int		WE;
	int		EA;
	int		N;
	int		F;
	int		C;
	char	d;
	int		len;
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

void		calcul_rayon(t_pars *p, t_data *d);
int			init_buff_texture(t_data *d);
int			load_textures(t_data *d, t_pars *p);
void		put_pixel_to_img(t_data *d, int x, int y, int color, int dir);

/////////////// FREE ///////////////////////////

void		free_parsing(t_pars *d, char *s);

///////////////// UTILS/////////////////////////

void		init_data(t_data *d, t_pars *p);
void		init_pars(t_pars *p);
double		cdir(int degres);

#endif
