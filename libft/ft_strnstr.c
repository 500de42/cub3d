/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcharbon <kcharbon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 18:02:36 by kcharbon          #+#    #+#             */
/*   Updated: 2025/01/22 17:29:17 by kcharbon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t len)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	if (!(*s2))
		return ((char *)s1);
	while (s1[i] && i < len)
	{
		j = 0;
		if (s1[i + j] == s2[j])
		{
			while ((s1[i + j] == s2[j]) && (i + j < len))
			{
				if (!(s2[j]))
					return ((char *)&s1[i]);
				j++;
			}
			if (!(s2[j]))
				return ((char *)&s1[i]);
		}
		i++;
	}
	return (0);
}
