/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwianni <dwianni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 16:03:39 by dwianni           #+#    #+#             */
/*   Updated: 2024/10/25 16:17:36 by dwianni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	if (n == 0)
		ft_putchar_fd('0', fd);
	if (n == -2147483648)
		write(fd, "-2147483648", 11);
	else
	{
		while (n != 0)
		{
			if (n < 0)
			{
				n = -n;
				ft_putchar_fd('-', fd);
			}
			if (n > 9)
			{
				ft_putnbr_fd(n / 10, fd);
				n = n % 10;
			}
			if (n < 10)
			{
				ft_putchar_fd(n + '0', fd);
				n = 0;
			}
		}
	}
}
/*
int	main(int argc, char **argv)
{
	if (argc == 3)
	{
		ft_putnbr_fd(ft_atoi(argv[1]), ft_atoi(argv[2]));
	}
	else
		printf("Pas le bon nombre d'arguments !!");
	return (0);
}
*/