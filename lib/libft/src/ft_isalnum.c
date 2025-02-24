/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwianni <dwianni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 17:28:19 by dwianni           #+#    #+#             */
/*   Updated: 2024/10/21 15:33:04 by dwianni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int c)
{
	if ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z')
		|| (c >= 'A' && c <= 'Z'))
		return (8);
	return (0);
}
/*
int	main(int argc, char **argv)
{
	if (argc == 2)
	{
		printf("%c ft_isalnum %d\n", ft_atoi(argv[1]),
			ft_isalnum(ft_atoi(argv[1])));
		printf("%c isalnum %d\n", ft_atoi(argv[1]), isalnum(ft_atoi(argv[1])));
	}
	else
		printf("Pas le bon nombre d'arguments !!");
	return (0);
}
*/