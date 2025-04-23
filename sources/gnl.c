/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcharbon <kcharbon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 16:13:30 by kcharbon          #+#    #+#             */
/*   Updated: 2025/04/22 16:29:01 by kcharbon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static char	*ft_next_line(char *line)
{
	char	*dest;
	int		i;

	i = 0;
	while (line[i] != '\0' && line[i] != '\n')
		i++;
	if (line[i] == '\0')
		return (NULL);
	dest = ft_substr(line, i + 1, ft_strlen(line) - i);
	if (*dest == 0)
	{
		free(dest);
		dest = NULL;
	}
	line[i + 1] = '\0';
	return (dest);
}

static char	*ft_free(char *s1, char *s2)
{
	char	*dest;

	dest = ft_strjoin(s1, s2);
	free(s1);
	s1 = NULL;
	return (dest);
}

static char	*ft_line(int fd, char *dest, char *buffer)
{
	int		i;
	char	*tmp;

	i = 1;
	while (i > 0)
	{
		i = read(fd, buffer, BUFFER_SIZE);
		if (i == -1)
		{
			free(dest);
			return (NULL);
		}
		else if (i == 0)
			break ;
		buffer[i] = 0;
		if (dest == NULL)
			dest = ft_strdup("");
		tmp = dest;
		dest = ft_free(tmp, buffer);
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	return (dest);
}

char	*gnl(int fd, t_pars *d)
{
	static char	*dest = NULL;
	char		*line;
	char		*buffer;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (buffer == NULL)
		return (NULL);
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		if (dest)
			free(dest);
		free(buffer);
		dest = NULL;
		buffer = NULL;
		return (NULL);
	}
	line = ft_line(fd, dest, buffer);
	free(buffer);
	if (line == NULL)
		return (NULL);
	dest = ft_next_line(line);
	if (d->check && line[0] == '\n')
		free(dest);
	return (line);
}
