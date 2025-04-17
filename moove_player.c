#include "cub3d.h"

int	key_press_handler(int key, t_data *data)
{
	if (key == XK_Escape)
	{
		// function to clean and close the window
		printf("close wind\n");
		exit(0);
	}
	if (key == XK_Left)
	{
		data->left_rotate = true;
		data -> rotate -= 1;
	}
	if (key == XK_Right)
	{
		data->right_rotate = true;
		data -> rotate += 1;
	}
	if (key == XK_w)
		data->key_up = true;
	if (key == XK_s)
		data->key_down = true;
	if (key == XK_d)
		data->key_right = true;
	if (key == XK_a)
		data->key_left = true;
	return (0);
}

int	key_release_handler(int key, t_data *data)
{
	if (key == XK_Left)
	{
		data->left_rotate = false;
		data -> rotate = 0;
	}
	if (key == XK_Right)
	{
		data->right_rotate = false;
		data -> rotate = 0;
	}
	if (key == XK_w)
		data->key_up = false;
	if (key == XK_s)
		data->key_down = false;
	if (key == XK_d)
		data->key_right = false;
	if (key == XK_a)
		data->key_left = false;
	return (0);
}

void	rotate_player(t_data *data)
{
	double oldPlaneX;
	double oldDirX;
	double angle_speed;

	oldPlaneX = data -> planeX;
	oldDirX = data -> dirX;
	angle_speed = 0.015 * data -> rotate;

	data ->dirX = data ->dirX * cos(angle_speed) - data -> dirY * sin(angle_speed);
	data -> dirY = oldDirX * sin(angle_speed) + data -> dirY * cos(angle_speed);
	data -> planeX = data -> planeX * cos(angle_speed) - data -> planeY * sin(angle_speed);
	data -> planeY = oldPlaneX * sin(angle_speed) + data -> planeY * cos(angle_speed);
}

void	get_mouse_position(t_data *data, int x, int y)
{
	if (x > SCREEN_WIDTH - DIST_EDGE_MOUSE_WRAP)
	{
		x = DIST_EDGE_MOUSE_WRAP;
		mlx_mouse_move(data->mlx, data->mlx_window, x, y);
	}
	if (x < DIST_EDGE_MOUSE_WRAP)
	{
		x = SCREEN_WIDTH - DIST_EDGE_MOUSE_WRAP;
		mlx_mouse_move(data->mlx, data->mlx_window, x, y);
	}
}

int	mouse_handler(int x, int y, t_data *data)
{
	
	static int tmpX = SCREEN_WIDTH / 2;

	get_mouse_position(data, x, y);
	if (x == SCREEN_WIDTH / 2)
		return (0);
	else if (x > tmpX)
	{
		data -> rotate += 1;
		rotate_player(data);
		data -> rotate = 0;
	}
	else if (x < tmpX)
	{
		data -> rotate -= 1;
		rotate_player(data);
		data -> rotate = 0;	
	}
	tmpX = x;
	return (0);
}
void	move_player(t_data *data)
{
	if (data->left_rotate || data->right_rotate)
	{
		rotate_player(data);
		return ;
	}
	if (data->key_up)
	{
		data->posX += data->dirX * MSPEED;
		data->posY += data->dirY * MSPEED;
	}
	if (data->key_down)
	{
		data->posX -= data->dirX * MSPEED;
		data->posY -= data->dirY * MSPEED;
	}
	if (data->key_left)
	{
		data->posX += data->dirY * MSPEED;
		data->posY -= data->dirX * MSPEED;
	}
	if (data->key_right)
	{
		data->posX -= data->dirY * MSPEED;
		data->posY += data->dirX * MSPEED;
	}
}

// bool check_position(t_pars *p, double x, double y)
// {
//     if (!p->map[(int)y][(int)x] == '0')
// 		return (false);
//     //check pos in map width and height
//     return (true);
// }
