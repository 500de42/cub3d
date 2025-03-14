/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_type_print.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcharbon <kcharbon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 18:28:07 by kcharbon          #+#    #+#             */
/*   Updated: 2025/01/17 18:29:29 by kcharbon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_convert_base_10(int num);
int	ft_convert_base_10_u(unsigned int num);

int	ft_type_print(const char s, va_list args)
{
	int	n;

	n = 0;
	if (s == 's')
		n += ft_putstr(va_arg(args, char *));
	else if (s == 'd' || s == 'i')
		n += ft_convert_base_10(va_arg(args, int));
	else if (s == 'p')
		n += ft_convert_ptr(va_arg(args, void *));
	else if (s == 'c')
		n += ft_putchar((char)va_arg(args, int));
	else if (s == 'u')
		n += ft_convert_base_10_u(va_arg(args, int));
	else if (s == 'x' || s == 'X')
		n += ft_print_hex(va_arg(args, unsigned int), s);
	else if (s == '%')
		n += ft_putchar('%');
	return (n);
}
