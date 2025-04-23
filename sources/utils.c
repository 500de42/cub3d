/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcharbon <kcharbon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 18:15:56 by kcharbon          #+#    #+#             */
/*   Updated: 2025/04/22 19:37:17 by kcharbon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	check_check(char *line_map)
{
	int	i;

	i = 0;
	if (!line_map || !line_map[0])
		return (1);
	if (line_map[0] == '\n' || !line_map[0])
		return (1);
	while (line_map[i])
	{
		if (line_map[i] == '\n' || line_map[i] == '\t' || line_map[i] == ' ')
			i++;
		else
			return (0);
	}
	return (1);
}

int	checkk(char *s)
{
	int	i;
	int	len;
	int	check;

	i = 0;
	check = 0;
	if (!s)
		return (0);
	len = ft_strlen(s);
	while (s[i])
	{
		if (s[i] == '1')
			check++;
		i++;
	}
	if (check == (len - 1) && ft_strncmp(s, "\n", 1))
		return (1);
	return (0);
}

char	**copy_map(t_pars *data)
{
	char	**cpy_map;
	char	*line_map;
	char	*old_line_map;
	char	*temp;

	cpy_map = NULL;
	line_map = ft_strdup("");
	temp = gnl(data->fd, data);
	if (!temp)
		return (NULL);
	while (temp)
	{
		old_line_map = line_map;
		line_map = ft_strjoin(line_map, temp);
		free(old_line_map);
		free(temp);
		temp = gnl(data->fd, data);
		if (checkk(temp))
			data->check = 1;
		if (temp && data->check)
		{
			if (!ft_strncmp(temp, "\n", 1))
			{
				free(temp);
				free(line_map);
				return (NULL);
			}
		}
	}
	if (line_map == NULL)
		free(line_map);
	else
	{
		cpy_map = ft_split(line_map, '\n');
		free(line_map);
	}
	return (cpy_map);
}

double	cdir(int degres)
{
	return ((degres * M_PI) / 180);
}

int	rbg_in_int(int tab[3])
{
	return ((tab[0] << 16) | (tab[1] << 8) | tab[2]);
}

void	destroy_texture(t_data *data)
{
	if (data->tex_ptr[0])
		mlx_destroy_image(data->mlx, data->tex_ptr[0]);
	if (data->tex_ptr[1])
		mlx_destroy_image(data->mlx, data->tex_ptr[1]);
	if (data->tex_ptr[2])
		mlx_destroy_image(data->mlx, data->tex_ptr[2]);
	if (data->tex_ptr[3])
		mlx_destroy_image(data->mlx, data->tex_ptr[3]);
}
