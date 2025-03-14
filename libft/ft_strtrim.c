/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcharbon <kcharbon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 19:24:06 by kcharbon          #+#    #+#             */
/*   Updated: 2024/10/14 14:40:29 by kcharbon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *str);
size_t	ft_strlcpy(char *dest, const char *src, size_t n);
char	*ft_strdup(char *str);

size_t	found_c(char const *set, char c)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

size_t	found_c_reverse(char const *s1, char const *set)
{
	size_t	j;

	j = ft_strlen(s1);
	while (j > 0 && found_c(set, s1[j - 1]))
		j--;
	return (j);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char		*str;
	size_t		start;
	size_t		len;
	size_t		end;

	start = 0;
	if ((!s1) || (!set))
		return (NULL);
	while (found_c(set, s1[start]) && s1[start])
		start++;
	end = found_c_reverse(s1, set);
	if (start >= end)
		return (ft_strdup(""));
	len = end - start;
	str = (char *)malloc (sizeof (char) * (len + 1));
	if (str == NULL)
		return (NULL);
	ft_strlcpy(str, &s1[start], len + 1);
	return (str);
}
