/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwianni <dwianni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 12:23:00 by dwianni           #+#    #+#             */
/*   Updated: 2024/10/28 17:29:45 by dwianni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (((unsigned char *)s)[i] == (unsigned char)c)
			return ((unsigned char *)(s + i));
		i++;
	}
	return (NULL);
}
/*
int	main(int argc, char **argv)
{
	if (argc == 4)
		printf("ft_ memchr : %s\n",
			(char *)ft_memchr(argv[1], atoi(argv[2]), ft_atoi(argv[3])));
	else
		printf("Pas le bon nombre d'arguments !!");
	return (0);
}
*/