/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcharbon <kcharbon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 17:35:54 by kcharbon          #+#    #+#             */
/*   Updated: 2024/10/14 14:41:44 by kcharbon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_convert_base_10(int num);
int	ft_convert_base_10_u(unsigned int num);

int	ft_printf(const char *s, ...)
{
	int		count;
	va_list	args;

	va_start(args, s);
	count = 0;
	if (!s)
		return (-1);
	while (*s)
	{
		if (*s == '%')
		{
			s++;
			if (*s)
				count += ft_type_print(*s, args);
		}
		else
		{
			ft_putchar(*s);
			count++;
		}
		s++;
	}
	va_end(args);
	return (count);
}
