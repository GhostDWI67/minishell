/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwianni <dwianni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 17:51:08 by dwianni           #+#    #+#             */
/*   Updated: 2024/10/21 12:16:07 by dwianni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}
/*
int	main(int argc, char **argv)
{
	if (argc == 2)
	{
		printf("ft_strlen %zu\n", ft_strlen(argv[1]));
		printf("strlen %zu\n", strlen(argv[1]));
	}
	else
		printf("Pas le bon nombre d'arguments !!");
	return (0);
}
*/