/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcharbon <kcharbon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 17:36:07 by kcharbon          #+#    #+#             */
/*   Updated: 2024/10/14 14:41:37 by kcharbon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	len_hex(unsigned int num)
{
	int	len;

	len = 0;
	while (num != 0)
	{
		len++;
		num = num / 16;
	}
	return (len);
}

void	put_hex(unsigned int num, const char s)
{
	if (num >= 16)
	{
		put_hex(num / 16, s);
		put_hex(num % 16, s);
	}
	else
	{
		if (num <= 9)
		{
			ft_putchar(num + '0');
		}
		else
		{
			if (s == 'x')
				ft_putchar(num - 10 + 'a');
			if (s == 'X')
				ft_putchar(num - 10 + 'A');
		}
	}
}

int	ft_print_hex(unsigned int num, const char s)
{
	int	t;

	t = 0;
	if (num == 0)
		t += write(1, "0", 1);
	else
	{
		put_hex(num, s);
		t += len_hex(num);
	}
	return (t);
}
