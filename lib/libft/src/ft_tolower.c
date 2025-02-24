/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwianni <dwianni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 19:36:27 by dwianni           #+#    #+#             */
/*   Updated: 2024/10/21 15:35:34 by dwianni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
		c = c + 32;
	return (c);
}
/*
int	main(int argc, char **argv)
{
	if (argc == 2)
	{
		printf("ft_tolower %c\n", ft_tolower(argv[1][0]));
		printf("tolower %c\n", tolower(argv[1][0]));
	}
	else
		printf("Pas le bon nombre d'arguments !!");
	return (0);
}
*/