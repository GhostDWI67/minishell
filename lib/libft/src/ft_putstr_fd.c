/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwianni <dwianni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 15:48:04 by dwianni           #+#    #+#             */
/*   Updated: 2024/10/28 22:36:28 by dwianni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	if (s == NULL)
		return ;
	write(fd, s, (int)ft_strlen(s));
}
/*
int	main(void)
{
	ft_putstr_fd("qwerty", 1);
	return (0);
}
*/
/*
int	main(int argc, char **argv)
{
	if (argc == 3)
	{
		ft_putstr_fd(argv[1], ft_atoi(argv[2]));
	}
	else
		printf("Pas le bon nombre d'arguments !!");
	return (0);
}
*/
