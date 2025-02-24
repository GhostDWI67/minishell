/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwianni <dwianni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 17:43:45 by dwianni           #+#    #+#             */
/*   Updated: 2024/10/21 10:37:48 by dwianni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isprint(int c)
{
	if (c >= 32 && c <= 126)
		return (16384);
	return (0);
}
/*
int	main(int argc, char **argv)
{
	if (argc == 2)
	{
		printf("%c ft_isprint %d\n", atoi(argv[1]), ft_isprint(atoi(argv[1])));
		printf("%c isprint %d\n", atoi(argv[1]), isprint(atoi(argv[1])));
	}
	else
		printf("Pas le bon nombre d'arguments !!");
	return (0);
}
*/