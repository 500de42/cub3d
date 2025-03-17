/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcharbon <kcharbon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 18:15:56 by kcharbon          #+#    #+#             */
/*   Updated: 2025/03/17 19:43:58 by kcharbon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

char	**copy_map(t_pars *data)
{
	char	**cpy_map;
	char	*line_map;
	char	*old_line_map;
	char	*temp;

	line_map = ft_strdup("");
	temp = get_next_line(data->fd);
	while (temp)
	{
		old_line_map = line_map;
		line_map = ft_strjoin(line_map, temp);
		free(old_line_map);
		free(temp);
		temp = get_next_line(data->fd);
	}
	if (line_map == NULL)
	{
		free(line_map);
	}
	else
		cpy_map = ft_split(line_map, '\n');
	free(line_map);
	return (cpy_map);
}
