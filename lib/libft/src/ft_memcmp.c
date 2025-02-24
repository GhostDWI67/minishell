/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwianni <dwianni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 12:58:22 by dwianni           #+#    #+#             */
/*   Updated: 2024/10/28 15:17:12 by dwianni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (((unsigned char *)s1)[i] != ((unsigned char *)s2)[i])
			return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
		i++;
	}
	return (0);
}
/*
int	main(int argc, char **argv)
{
	if (argc == 4)
		printf("ft_memcmp : %d\n",
			(int)ft_memcmp(argv[1], argv[2], ft_atoi(argv[3])));
	else
		printf("Pas le bon nombre d'arguments !!");
	return (0);
}
*/