/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwianni <dwianni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 08:55:57 by dwianni           #+#    #+#             */
/*   Updated: 2024/10/28 15:27:18 by dwianni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, char *src, size_t size)
{
	size_t	i;
	size_t	result;

	result = ft_strlen(src);
	if (size == 0)
	{
		dst = NULL;
		return (result);
	}
	i = 0;
	while (src[i] != '\0' && i < (size - 1))
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (result);
}
/*
int	main(int argc, char **argv)
{
	char	destu[100];
	char	dest[100];

	if (argc == 3)
	{
		printf("ft_strlcpy : %zu\n",
			ft_strlcpy(destu, argv[1], ft_atoi(argv[2])));
		printf("%s\n", destu);
		printf("strlcpy : %zu\n", strlcpy(dest, argv[1], ft_atoi(argv[2])));
		printf("%s\n", dest);
	}
	else
		printf("Pas le bon nombre d'arguments !!");
	return (0);
}
*/