/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwianni <dwianni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 15:57:06 by dwianni           #+#    #+#             */
/*   Updated: 2024/10/28 22:37:07 by dwianni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	if (s == NULL)
		return ;
	write(fd, s, (int)ft_strlen(s));
	write(fd, &"\n", 1);
}
/*
int	main(int argc, char **argv)
{
	if (argc == 3)
	{
		ft_putendl_fd(argv[1], ft_atoi(argv[2]));
	}
	else
		printf("Pas le bon nombre d'arguments !!");
	return (0);
}
*/