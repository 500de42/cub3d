/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcharbon <kcharbon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 16:28:48 by kcharbon          #+#    #+#             */
/*   Updated: 2024/10/20 18:09:10 by kcharbon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			check_check(char *line_map);

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

int	check_check2(char *line_map)
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
	if (check_check2(line) == 1)
		free(dest);
	return (line);
}
/*
#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

int	main(void)
{
	int		fd;
	char	*line;

	fd = open("hey.txt", O_RDONLY);
	if (fd < 0)
	{
		perror("Error opening file");
		return (1);
	}
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%s", line);
		free(line); // Libérer la mémoire allouée par get_next_line
	}
	if (close(fd) < 0)
	{
		perror("Error closing file");
		return (1);
	}
	return (0);
}*/
