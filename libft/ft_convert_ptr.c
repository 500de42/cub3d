/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_ptr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcharbon <kcharbon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 18:08:37 by kcharbon          #+#    #+#             */
/*   Updated: 2024/10/14 14:41:12 by kcharbon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putchar(char c);

int	ft_convert_ptr(void *pt)
{
	unsigned long	ptr;
	int				count;

	count = 0;
	if (!pt)
	{
		count += write(1, "(nil)", 5);
		return (count);
	}
	else
	{
		ptr = (unsigned long long)pt;
		count += write(1, "0x", 2);
		count += ft_putnbr_base(ptr, "0123456789abcdef");
	}
	return (count);
}
