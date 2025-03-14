/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcharbon <kcharbon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 16:06:39 by kcharbon          #+#    #+#             */
/*   Updated: 2024/05/31 20:06:46 by kcharbon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	unsigned int	i;
	char			st;

	st = (char) c;
	i = ft_strlen(s);
	while (i > 0)
	{
		if (s[i] == st)
			return ((char *) &s[i]);
		i--;
	}
	if (s[i] == st)
		return ((char *) &s[i]);
	return (NULL);
}
