/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcharbon <kcharbon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 14:23:58 by kcharbon          #+#    #+#             */
/*   Updated: 2024/05/31 15:16:25 by kcharbon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t n)
{
	size_t	i;
	size_t	j;
	size_t	s;

	i = ft_strlen(dest);
	j = ft_strlen(src);
	if (n <= 0)
		return (j);
	s = 0;
	if (n < i)
		return (j + n);
	while (src[s] && ((i + s) < n - 1))
	{
		dest[i + s] = src[s];
		s++;
	}
	dest[s + i] = '\0';
	return (j + i);
}
