/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwianni <dwianni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 17:22:15 by dwianni           #+#    #+#             */
/*   Updated: 2024/10/21 10:37:30 by dwianni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (2048);
	return (0);
}
/*
int	main(int argc, char **argv)
{
	if (argc == 2)
	{
		printf("%c ft_isdigit %d\n", ft_atoi(argv[1]),
			ft_isdigit(ft_atoi(argv[1])));
		printf("%c isdigit %d\n", ft_atoi(argv[1]), isdigit(ft_atoi(argv[1])));
	}
	else
		printf("Pas le bon nombre d'arguments !!");
	return (0);
}
*/