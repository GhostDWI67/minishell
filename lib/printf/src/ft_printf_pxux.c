/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_pxux.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwianni <dwianni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 10:32:13 by dwianni           #+#    #+#             */
/*   Updated: 2024/12/02 10:52:25 by dwianni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_size_itoa_h(unsigned long n)
{
	int	size_itoa_h;

	size_itoa_h = 0;
	if (n == 0)
		size_itoa_h++;
	while (n != 0)
	{
		n = n / 16;
		size_itoa_h++;
	}
	return (size_itoa_h);
}

int	ft_printf_x(unsigned int n)
{
	unsigned long	tmp;

	tmp = n;
	if (n == 0)
		return (write (1, &"0", 1));
	while (n != 0)
	{
		if (n > 15)
		{
			ft_printf_x(n / 16);
			n = n % 16;
		}
		if (n <= 15)
		{
			write(1, &"0123456789abcdef"[n], 1);
			n = 0;
		}
	}
	return (ft_size_itoa_h(tmp));
}

int	ft_printf_ux(unsigned int n)
{
	unsigned long	tmp;

	tmp = n;
	if (n == 0)
		return (write (1, &"0", 1));
	while (n != 0)
	{
		if (n > 15)
		{
			ft_printf_ux(n / 16);
			n = n % 16;
		}
		if (n <= 15)
		{
			write(1, &"0123456789ABCDEF"[n], 1);
			n = 0;
		}
	}
	return (ft_size_itoa_h(tmp));
}

static void	ft_printf_xp(unsigned long n)
{
	if (n == 0)
		write (1, &"0", 1);
	while (n != 0)
	{
		if (n > 15)
		{
			ft_printf_xp(n / 16);
			n = n % 16;
		}
		if (n <= 15)
		{
			write(1, &"0123456789abcdef"[n], 1);
			n = 0;
		}
	}
}

int	ft_printf_p(unsigned long ad)
{
	if (ad == 0)
		return (write(1, "(nil)", 5));
	write(1, &"0x", 2);
	ft_printf_xp(ad);
	return (ft_size_itoa_h(ad)+2);
}
