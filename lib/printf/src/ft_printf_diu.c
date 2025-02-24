/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_diu.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwianni <dwianni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 10:31:48 by dwianni           #+#    #+#             */
/*   Updated: 2024/12/02 10:31:50 by dwianni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_size_itoa_d(int n)
{
	int	count;

	count = 0;
	if (n == 0)
		count++;
	if (n < 0)
		count++;
	while (n != 0)
	{
		n = n / 10;
		count++;
	}
	return (count);
}

int	ft_printf_d(int n)
{
	ft_putnbr(n);
	return (ft_size_itoa_d(n));
}

static int	ft_size_itoa_u(unsigned int n)
{
	int	count;

	count = 0;
	if (n == 0)
		count++;
	while (n != 0)
	{
		n = n / 10;
		count++;
	}
	return (count);
}

void	ft_putnbr_u(unsigned int n)
{
	if (n == 0)
		ft_putchar('0');
	while (n != 0)
	{
		if (n > 9)
		{
			ft_putnbr_u(n / 10);
			n = n % 10;
		}
		if (n < 10)
		{
			ft_putchar(n + '0');
			n = 0;
		}
	}
}

int	ft_printf_u(unsigned int n)
{
	ft_putnbr_u(n);
	return (ft_size_itoa_u(n));
}
