/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwianni <dwianni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 12:23:20 by dwianni           #+#    #+#             */
/*   Updated: 2024/10/28 17:13:10 by dwianni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;

	if (dest == NULL && src == NULL)
		return (NULL);
	i = 0;
	while (i < n)
	{
		((char *) dest)[i] = ((char *) src)[i];
		i++;
	}
	return (dest);
}
/*
int	main(int argc, char **argv)
{
	if (argc == 4)
	{
		printf("Source avant : %s\n", argv[2]);
		printf("Dest avant : %s\n", argv[1]);
		ft_memcpy(argv[1], argv[2], ft_atoi(argv[3]));
		printf("-------------------------------------\n");
		printf("Source apres ft_memcpy : %s\n", argv[2]);
		printf("Dest apres ft_memcpy : %s\n", argv[1]);
	}
	else
		printf("Pas le bon nombre d'arguments !!");
	return (0);
}
*/