/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcharbon <kcharbon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 15:26:28 by kcharbon          #+#    #+#             */
/*   Updated: 2025/04/08 20:37:31 by kcharbon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft/libft.h"
# include "minilibx-linux/mlx.h"
# include "minilibx-linux/mlx_int.h"
# include <math.h>
# include <stdio.h>
#include <stdbool.h>
#include <unistd.h>

# ifndef M_PI
#  define M_PI 3.14159265
# endif
# ifndef SCREEN_WIDTH
#  define SCREEN_WIDTH 1920
# endif
# ifndef SCREEN_HEIGHT
#  define SCREEN_HEIGHT 1080
# endif
# ifndef MSPEED
#	define MSPEED 0.0150
# endif
# define DIST_EDGE_MOUSE_WRAP 20

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
	char	**map;
	int		floor_rgb[3];
	int		ceiling_rgb[3];
}			t_pars;

typedef struct t_data
{
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
	double		planeX;
	double		planeY;
	int		ceiling_color;
	int		floor_color;
	int 	*texture_buffer[4]; // Stocke les textures sous forme de tableau 1D
	void 	*tex_ptr[4];      // Pointeurs vers les textures MLX
	char 	*tex_addr[4];    // Adresses mémoire des textures
	void	*img_ptr;	// Pointeur vers les img
	void	*img_addr;	// pointeur vers l adresse de l img
	int 	tex_bpp, tex_line_length, tex_endian;
	void	*mlx_window;
	void	*mlx;
	int		tex_buff;
	t_pars	*p;
	
	float angle;
	bool key_up; 
    bool key_down; 
    bool key_right; 
    bool key_left;
    bool left_rotate; 
    bool right_rotate;
}			t_data;



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

void		Raycasting(t_pars *p, t_data *d);
int			init_buff_texture(t_data *d);
void		load_textures(t_data *d, t_pars *p);
void		put_pixel_to_img(t_data *d, int x, int y, int color);
int			rbg_in_int(int tab[3]);

/////////////// FREE ///////////////////////////

void		free_parsing(t_pars *d, char *s);
void		destroy_texture(t_data *data);
void		free_all(t_pars *p, t_data *d, char *s);

///////////////// UTILS/////////////////////////

void		init_data(t_data *d, t_pars *p);
void		init_pars(t_pars *p);
double		cdir(int degres);
int			close_window(t_data *d, t_pars *p);
int			game_loop(t_data *d);
void		init_dir_player(t_data *d, t_pars *p);

/////////////// MOOVE PLAYER //////////////////

void 		init_movement(t_data *data);
int 		key_press_handler(t_data *data, int key);
int 		key_release_handler(t_data *data , int key);
void 		rotate_player(t_data *data);
void		get_mouse_position(t_data *data, int x, int y);
int 		mouse_handler(t_data *data, int x, int y);
void		move_player(t_data *data);
//bool 		check_position(t_pars *p, double x, double y);

#endif
