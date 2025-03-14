/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_array.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcharbon <kcharbon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 18:39:16 by kcharbon          #+#    #+#             */
/*   Updated: 2025/03/14 18:39:35 by kcharbon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	print_array(char **array)
{
	int	i;

	i = 0;
	if (!array)
	{
		ft_printf("The array is empty or NULL.\n");
		return ;
	}
	while (array[i])
	{
		ft_printf("Element %d: %s\n", i, array[i]);
		i++;
	}
}
