/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcharbon <kcharbon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 15:33:48 by kcharbon          #+#    #+#             */
/*   Updated: 2024/10/14 14:39:49 by kcharbon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(char *s, int c)
{
	unsigned int	i;
	char			st;

	st = (char) c;
	i = 0;
	while (s[i])
	{
		if (s[i] == st)
		{
			return ((char *) &s[i]);
		}
		i++;
	}
	if (s[i] == st)
		return ((char *) &s[i]);
	return (NULL);
}
