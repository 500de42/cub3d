/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcharbon <kcharbon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 20:09:26 by kcharbon          #+#    #+#             */
/*   Updated: 2024/05/31 20:15:51 by kcharbon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char			*pdest;
	unsigned const char		*psrc;
	size_t					i;

	i = 0;
	if (!dest && !src)
		return (NULL);
	pdest = (unsigned char *)dest;
	psrc = (const unsigned char *)src;
	if (pdest > psrc)
		while (n-- > 0)
			pdest[n] = psrc[n];
	else
	{
		while (i < n)
		{
			pdest[i] = psrc[i];
			i++;
		}
	}
	return (dest);
}
/*
#include <stdio.h>
#include <string.h>

int	main()
{
	char	dest[8];
	const char	*src = "salut";

	printf("%s", ft_memmove(dest, src, 6));
	printf("%s", memmove(dest, src, 6));
}*/
