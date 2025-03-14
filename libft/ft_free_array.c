/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_array.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcharbon <kcharbon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 16:12:28 by kcharbon          #+#    #+#             */
/*   Updated: 2025/02/23 16:12:45 by kcharbon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free_array(char **tab)
{
	int	j;

	j = 0;
	if (tab)
	{
		while (tab[j])
		{
			free(tab[j]);
			j++;
		}
		free(tab);
		tab = NULL;
	}
}
