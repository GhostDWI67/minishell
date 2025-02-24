/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwianni <dwianni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 15:35:23 by dwianni           #+#    #+#             */
/*   Updated: 2024/10/25 15:46:50 by dwianni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}
/*
int	main(int argc, char **argv)
{
	if (argc == 3)
	{
		ft_putchar_fd(argv[1][0], ft_atoi(argv[2]));
	}
	else
		printf("Pas le bon nombre d'arguments !!");
	return (0);
}
*/