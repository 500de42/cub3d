/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcharbon <kcharbon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 15:26:28 by kcharbon          #+#    #+#             */
/*   Updated: 2025/04/22 19:00:32 by kcharbon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft/libft.h"
# include "minilibx-linux/mlx.h"
# include "minilibx-linux/mlx_int.h"
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <unistd.h>

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
#  define MSPEED 0.0150
# endif
# define DIST_EDGE_MOUSE_WRAP 20
# ifndef TEXTURE_SIZE
#  define TEXTURE_SIZE 64
# endif
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
	char	id[2];
	char	*texture_path[4];
	int		tex;
	int		virg;
	int		j;
	int check;
	char	pp;
}			t_pars;

typedef struct t_ray
{
	int		stepX;
	int		stepY;
	double	sideX;
	double	sideY;
	int		side;
	int		mapX;
	int		mapY;
	int		x;
	double	distance_wall;
	int		wall_height;
	int		draw_start;
	int		draw_end;
	double	wall_x;
	int		tex_x;
	int		tex_y;
	int		color;
	double	step;
	double	pos;
	int		dir;
	int		dw;
}			t_ray;

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
	double	planeX;
	double	planeY;
	int		ceiling_color;
	int		floor_color;
	int *texture_buffer[4]; // Stocke les textures sous forme de tableau 1D
	void *tex_ptr[4];       // Pointeurs vers les textures MLX
	char *tex_addr[4];      // Adresses mémoire des textures
	void *img_ptr;          // Pointeur vers les img
	void *img_addr;         // pointeur vers l adresse de l img
	int tex_width[4];
	int tex_height[4];
	int tex_bpp, tex_line_length, tex_endian;
	void	*mlx_window;
	void	*mlx;
	int		tex_buff;
	t_pars	*p;
	t_ray	*r;
	int		rotate;
	float	angle;
	bool	key_up;
	bool	key_down;
	bool	key_right;
	bool	key_left;
	bool	left_rotate;
	bool	right_rotate;
}			t_data;

//////////////// PARSING //////////////////////

void		check_(char **av, int ac);
char		**copy_map(t_pars *data);
void		check_map(char *av, t_pars *d);
void		check_sprite(t_pars *d);
void		check_path_sprite(t_pars *d, int *y, int *x);
void		check_rgb(t_pars *d, int *y, int *x);
void		last_check(t_pars *d);
int			found_the_most_insane_len(char **map);
void		check_path_end(t_pars *d, char *st);
void		check_value_rgb(char c, t_pars *d, char **tab);
void		first_check_rgb(t_pars *d, int *y, int *x, char *c);
void		check_start_of_map(t_pars *d, char ***map, int *map_len_y,
				int *map_len);
void		check_map_space(t_pars *d, char **map, int y, int x);
void		loop_last_check(t_pars *d, int x, int y, int map_len_y);
void		loops_check_rgb(t_pars *d, int i, int *y, char *nb);
void		check_texture_and_pos(t_pars *d, int y, int x);
char		**parse_map(char **map);
void		check_first_line(char *s, t_pars *d);
void		check_last_line(char *s, t_pars *d);
void		if_check_path_end(t_pars *d, char *st);

//////////////// RAYCASTING ////////////////////

void		ray(t_data *d, t_ray *r);
void		load_textures(t_data *d, t_pars *p);
void		put_pixel_to_img(t_data *d, int x, int y, int color);
int			rbg_in_int(int tab[3]);
void		loop_length_ray(t_ray *r, t_data *d);
void		ray_start(t_ray *r, t_data *d);
void		loop_put_pixel(t_data *d, t_ray *r);
void		dir_ray(t_ray *r, t_data *d);
void		def_per_side(t_ray *r, t_data *d);
void		def_before_draw(t_data *d, t_ray *r);

/////////////// FREE ///////////////////////////

void		free_parsing(t_pars *d, char *s);
void		destroy_texture(t_data *data);
void		free_all(t_data *d, char *s);
void		free_cv_rgb(char **tab, t_pars *d);
void		free_data_close(t_data *d);

///////////////// UTILS/////////////////////////

void		init_data(t_data *d, t_pars *p);
void		init_pars(t_pars *p);
double		cdir(int degres);
int			close_window(t_data *d);
int			game_loop(t_data *d);
void		init_dir_player(t_data *d, t_pars *p);
void		init_ray(t_ray *r);
void		init_mlx_and_loop(t_pars *p, t_data *d);
void		init_dir_player_norm(t_data *d, t_pars *p);
char		*gnl(int fd, t_pars *d);

/////////////// MOOVE PLAYER //////////////////

void		init_movement(t_data *data);
int			key_press_handler(int key, t_data *data);
int			key_release_handler(int key, t_data *data);
void		rotate_player(t_data *data);
void		get_mouse_position(t_data *data, int x, int y);
int			mouse_handler(int x, int y, t_data *data);
void		move_player(t_data *data);
// bool 		check_position(t_pars *p, double x, double y);

#endif
