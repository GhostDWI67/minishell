/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwianni <dwianni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 09:20:27 by dwianni           #+#    #+#             */
/*   Updated: 2024/10/28 21:22:32 by dwianni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*result;

	i = 0;
	result = s;
	while (i < n)
	{
		result[i] = c;
		i++;
	}
	return (s);
}
/*
int	main(int argc, char **argv)
{
	if (argc == 4)
	{
		ft_memset(argv[1], ft_atoi(argv[2]), ft_atoi(argv[3]));
		printf("ft_memset %s\n", argv[1]);
	}
	else
		printf("Pas le bon nombre d'arguments !!");
	return (0);
}
*/