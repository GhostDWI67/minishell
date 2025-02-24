/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwianni <dwianni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 14:40:05 by dwianni           #+#    #+#             */
/*   Updated: 2024/10/28 17:24:04 by dwianni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned int	i;

	if (dest == NULL && src == NULL)
		return (NULL);
	if (dest > src)
	{
		i = (unsigned int)n;
		while (i > 0)
		{
			((char *) dest)[i - 1] = ((char *) src)[i - 1];
			i--;
		}
	}
	else
	{
		i = 0;
		while (i < (unsigned int)n)
		{
			((char *) dest)[i] = ((char *) src)[i];
			i++;
		}
	}
	return (dest);
}
/*
int	main(void)
{
	//char	src[100];
	//char	dest[100];
	
	printf ("%s\n", (char *)ft_memmove(NULL, NULL, 5));
	return (0);
}
*/
/*
int	main(void)
{
	char	mem[21];

	ft_memcpy(mem, "01234567890123456789", 20);
	printf ("Avant : %s\n", mem);
	ft_memmove((mem + 0), (mem + 3), 5);
	printf ("Apres : %s\n", mem);
}
*/
/*
int	main(int argc, char **argv)
{
	if (argc == 4)
	{
		printf("Source avant : %s\n", argv[2]);
		printf("Dest avant : %s\n", argv[1]);
		ft_memmove(argv[1], argv[2], atoi(argv[3]));
		printf("-------------------------------------\n");
		printf("Source apres ft_memmove : %s\n", argv[2]);
		printf("Dest apres ft_memmove : %s\n", argv[1]);
	}
	else
		printf("Pas le bon nombre d'arguments !!");
	return (0);
}
*/