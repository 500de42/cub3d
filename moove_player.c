#include "cub3d.h"

int key_press_handler(t_data *data, int key)
{
    if (key == XK_Escape)
    {
        //function to clean and close the window
        printf("close wind\n");
        exit(0);
    }
    if (key == XK_Left)
        data -> left_rotate = true;
    if (key == XK_Right)
        data -> right_rotate = true;
    if (key == XK_w)
        data -> key_up = true;
    if (key == XK_s)
        data -> key_down = true;
    if (key == XK_d)
        data -> key_right = true;
    if (key == XK_a)
        data -> key_left = true;
    return 0;
}

int key_release_handler(t_data *data , int key)
{
    if (key == XK_Left)
        data -> left_rotate = false;
    if (key == XK_Right)
        data -> right_rotate = false;
    if (key == XK_w)
        data -> key_up = false;
    if (key == XK_s)
        data -> key_down = false;
    if (key == XK_d)
        data -> key_right = false;
    if (key == XK_a)
        data -> key_left = false;
    return 0;
}

void rotate_player(t_data *data)
{
    int speed;
    float angle_speed;
    float cos_angle;
    float sin_angle;

    speed = 3;
    angle_speed = 0.03;
    cos_angle = cos(data->angle);
    sin_angle = sin(data->angle);

    if (data->left_rotate)
        data->angle -= angle_speed;
    if (data->right_rotate)
        data->angle += angle_speed;
    if (data->angle > 2 * M_PI)
        data->angle = 0;
    if (data->angle < 0)
        data->angle = 2 * M_PI;
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

int mouse_handler(t_data *data, int x, int y)
{

    get_mouse_position(data, x, y);
    if (x == SCREEN_WIDTH / 2)
        return 0;
    else if (x > SCREEN_WIDTH / 2)
    {
        data -> right_rotate = true;
        rotate_player(data);
        data -> right_rotate = false;
    }
    else if (x < SCREEN_WIDTH / 2)
    {
        data -> left_rotate = true;
        rotate_player(data);
        data -> left_rotate = false;;
    }
    return 0;
}
void move_player(t_data *data)
{
    //TODO function to check if valid position

    if (data->left_rotate || data->right_rotate)
        rotate_player(data);
    if (data->key_up)
    {
        data->posX += data->dirX * MSPEED;
        data->posY += data->dirY * MSPEED;
    }
    if (data -> key_down)
    {
        data->posX -= data->dirX * MSPEED;
	    data->posY -= data->dirY * MSPEED;
    }
    if (data -> key_left)
    {
        data->posX += data->dirY * MSPEED;
	    data->posY -= data->dirX * MSPEED;
    }
    if (data-> key_right)
    {
        data->posX -= data->dirY * MSPEED;
	    data->posY += data->dirX * MSPEED;
    }
    
}

bool check_position(t_pars *p, double x, double y)
{
    if (!p->map[(int)y][(int)x] == '0')
		return false;
    //check pos in map width and height
    return true;
}

