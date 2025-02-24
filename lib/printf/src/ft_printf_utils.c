/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwianni <dwianni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 10:32:43 by dwianni           #+#    #+#             */
/*   Updated: 2025/01/11 14:59:40 by dwianni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t	ft_strlenpf(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putnbr(int n)
{
	if (n == 0)
		ft_putchar('0');
	if (n == -2147483648)
		write(1, "-2147483648", 11);
	else
	{
		while (n != 0)
		{
			if (n < 0)
			{
				n = -n;
				ft_putchar('-');
			}
			if (n > 9)
			{
				ft_putnbr(n / 10);
				n = n % 10;
			}
			if (n < 10)
			{
				ft_putchar(n + '0');
				n = 0;
			}
		}
	}
}
