/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalvin <kalvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 15:14:32 by kcharbon          #+#    #+#             */
/*   Updated: 2025/02/15 18:09:26 by kalvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	word(char const *s, char c)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i] != c && s[i])
			count++;
		while (s[i] && s[i] != c)
			i++;
	}
	return (count);
}

char	**st_free(char **tab)
{
	int	j;

	j = 0;
	while (tab[j])
	{
		free(tab[j]);
		j++;
	}
	free(tab);
	return (NULL);
}

void	rep(char const *s, char c, char **tab, int count)
{
	int	start;
	int	end;
	int	i;
	int	j;

	start = 0;
	j = 0;
	while (s[start] && j < count)
	{
		while (s[start] && s[start] == c)
			start++;
		end = start;
		while (s[end] && s[end] != c)
			end++;
		tab[j] = malloc(sizeof(char) * (end - start + 1));
		if (!tab[j])
			return ((void)st_free(tab));
		i = 0;
		while (start < end)
			tab[j][i++] = s[start++];
		tab[j++][i] = '\0';
		i++;
	}
	tab[j] = 0;
}

char	**ft_split(char const *s, char c)
{
	int		count;
	char	**tab;

	count = word(s, c);
	tab = malloc(sizeof(char *) * (count + 1));
	if (!tab)
		return (NULL);
	rep(s, c, tab, count);
	return (tab);
}
