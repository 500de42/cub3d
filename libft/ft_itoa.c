/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcharbon <kcharbon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 20:36:56 by kcharbon          #+#    #+#             */
/*   Updated: 2024/05/31 20:10:25 by kcharbon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	count_n(int n)
{
	int	nb;

	nb = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		n *= -1;
	while (n > 0)
	{
		n /= 10;
		nb++;
	}
	return (nb);
}

char	*cal(char *str, int nb, long int num)
{
	str[nb] = '\0';
	while (nb > 0)
	{
		str[nb - 1] = ((num % 10) + '0');
		num /= 10;
		nb--;
	}
	return (str);
}

char	*ft_itoa(int n)
{
	int			nb;
	char		*str;
	long int	num;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	num = n;
	nb = count_n(num);
	if (num < 0)
		nb++;
	str = malloc (sizeof (char) * (nb + 1));
	if (str == NULL)
		return (NULL);
	if (num < 0)
	{
		num = -num;
		str[0] = '-';
		cal (str + 1, nb - 1, num);
	}
	else
		cal (str, nb, num);
	return (str);
}
/*
#include <stdio.h>
int	main(void)
{
	int i = 0;
	int tab[5] = {-2147483648, -42, 0, 42, 2147483647};

	while (i < 5)
		printf("%s\n", ft_itoa(tab[i++]));

	return 0;
}*/
