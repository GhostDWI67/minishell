/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwianni <dwianni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 19:10:52 by dwianni           #+#    #+#             */
/*   Updated: 2024/10/21 15:35:42 by dwianni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_toupper(int c)
{
	if (c >= 'a' && c <= 'z')
		c = c - 32;
	return (c);
}
/*
int	main(int argc, char **argv)
{
	if (argc == 2)
	{
		printf("ft_toupper %c\n", ft_toupper(argv[1][0]));
		printf("toupper %c\n", toupper(argv[1][0]));
	}
	else
		printf("Pas le bon nombre d'arguments !!");
	return (0);
}
*/