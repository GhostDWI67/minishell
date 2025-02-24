/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwianni <dwianni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 12:12:12 by dwianni           #+#    #+#             */
/*   Updated: 2024/10/28 17:10:47 by dwianni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_bzero(void *s, size_t n)
{
	size_t			i;
	unsigned char	*result;

	i = 0;
	result = s;
	while (i < n)
	{
		result[i] = '\0';
		i++;
	}
	return (s);
}
/*
int	main(int argc, char **argv)
{
	if (argc == 3)
	{
		ft_bzero(argv[1], atoi(argv[2]));
		printf("ft_bzero %s\n", argv[1]);
	}
	else
		printf("Pas le bon nombre d'arguments !!");
	return (0);
}
*/