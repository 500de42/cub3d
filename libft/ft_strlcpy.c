/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcharbon <kcharbon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 12:30:31 by kcharbon          #+#    #+#             */
/*   Updated: 2024/11/12 14:27:03 by kcharbon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t n)
{
	size_t	a;

	a = 0;
	if (n > 0)
	{
		while (src[a] && a < n - 1)
		{
			dest[a] = src[a];
			a++;
		}
		dest[a] = '\0';
	}
	return (ft_strlen(src));
}
/*
#include <stdio.h>
#include <string.h>

int		main(void)
{
	char	dest[50];
	char	*src;
	int		size;

	src = "ceci est un test tu voissss";
	size = 10;
	printf("%ld\n", ft_strlcpy(dest, src, size));
	printf(".%s.\n\n", dest);
	//printf("%ld\n", strlcpy(dest, src, size));
	printf(".%s.\n\n", dest);
}*/
