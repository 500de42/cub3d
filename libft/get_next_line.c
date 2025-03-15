/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcharbon <kcharbon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 14:24:55 by kcharbon          #+#    #+#             */
/*   Updated: 2024/10/14 14:25:07 by kcharbon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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

char	*get_next_line(int fd)
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
	return (line);
}
