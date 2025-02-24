/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwianni <dwianni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 08:56:14 by dwianni           #+#    #+#             */
/*   Updated: 2024/10/28 15:32:36 by dwianni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	retour;

	i = 0;
	j = ft_strlen(dst);
	if (size > j)
	{
		while (src[i] != '\0' && i < size - j -1)
		{
			dst[j + i] = src[i];
			i++;
		}
		dst[j + i] = '\0';
		retour = j + ft_strlen(src);
	}
	else
		retour = j + ft_strlen(src) - (j - size);
	return (retour);
}
/*
int	main(int argc, char **argv)
{
	char	destu[100];
	char	dest[100];

	ft_strlcpy(destu, "Azerty", 7);
	ft_strlcpy(dest, "Azerty", 7);
	if (argc == 3)
	{
		printf("ft_strlcat : %zu\n",
			ft_strlcat(destu, argv[1], ft_atoi(argv[2])));
		printf("%s\n", destu);
		printf("strlcat : %zu\n", strlcat(dest, argv[1], ft_atoi(argv[2])));
		printf("%s\n", dest);
	}
	else
		printf("Pas le bon nombre d'arguments !!");
	return (0);
}
*/