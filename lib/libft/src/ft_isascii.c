/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwianni <dwianni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 17:34:06 by dwianni           #+#    #+#             */
/*   Updated: 2024/10/21 10:37:09 by dwianni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isascii(int c)
{
	if (c >= 0 && c <= 127)
		return (1);
	return (0);
}
/*
int	main(int argc, char **argv)
{
	if (argc == 2)
	{
		printf("%c ft_isascii %d\n", ft_atoi(argv[1]),
			ft_isascii(ft_atoi(argv[1])));
		printf("%c isascii %d\n", ft_atoi(argv[1]), isascii(ft_atoi(argv[1])));
	}
	else
		printf("Pas le bon nombre d'arguments !!");
	return (0);
}
*/