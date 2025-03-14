/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcharbon <kcharbon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 13:32:10 by kcharbon          #+#    #+#             */
/*   Updated: 2025/01/17 18:30:02 by kcharbon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putstr(char *str)
{
	int	l;

	l = 0;
	if (str == NULL)
	{
		write(1, "(null)", 6);
		l = 6;
		return (l);
	}
	if (!str)
		return (0);
	while (*str)
	{
		l += write(1, str, 1);
		str++;
	}
	return (l);
}
