/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoll.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcharbon <kcharbon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 19:58:32 by kcharbon          #+#    #+#             */
/*   Updated: 2025/03/18 16:04:39 by kcharbon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long long	ft_atoll(char *str)
{
	int			index;
	int			sign;
	long long	res;

	index = 0;
	sign = 1;
	res = 0;
	if (str[index] == '-')
	{
		index++;
		sign = -1;
	}
	while (str[index])
	{
		if (!ft_isdigit(str[index]))
			return (-1);
		res = res * 10 + str[index] - '0';
		index++;
	}
	return (res * sign);
}
