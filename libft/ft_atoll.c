/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoll.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcharbon <kcharbon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 19:58:32 by kcharbon          #+#    #+#             */
/*   Updated: 2025/03/20 19:41:26 by kcharbon         ###   ########.fr       */
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
		return (- 1);
	}
	while (str[index])
	{
		res = res * 10 + str[index] - '0';
		index++;
	}
	return (res * sign);
}
