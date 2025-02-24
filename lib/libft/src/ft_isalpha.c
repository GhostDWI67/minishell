/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwianni <dwianni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 12:47:57 by dwianni           #+#    #+#             */
/*   Updated: 2024/10/21 15:33:17 by dwianni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1024);
	return (0);
}
/*
int	main(int argc, char **argv)
{
	if (argc == 2)
	{
		printf("%c ft_isalpha %d\n", ft_atoi(argv[1]),
				ft_isalpha(ft_atoi(argv[1])));
		printf("%c isalpha %d\n", ft_atoi(argv[1]), isalpha(ft_atoi(argv[1])));
	}
	else
		printf("Pas le bon nombre d'arguments !!");
	return (0);
}
*/