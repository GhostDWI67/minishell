/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwianni <dwianni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 08:57:49 by dwianni           #+#    #+#             */
/*   Updated: 2024/10/28 21:34:04 by dwianni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*result;

	if (nmemb != 0 && (nmemb * size) / nmemb != size)
		return (NULL);
	result = (void *)malloc(nmemb * size);
	if (result == NULL)
		return (NULL);
	ft_memset(result, 0, nmemb * size);
	return (result);
}
/*
int	main(void)
{
	char	*test;
	
	test = ft_calloc(1, 0);
	printf("%s\n", test);
	return (0);
}
*/
/*
int	main(int argc, char **argv)
{
	int	*test;
	int	i;

	if (argc == 3)
	{
		test = ft_calloc(ft_atoi(argv[1]), ft_atoi(argv[2]));
		i = 0;
		while (i < ft_atoi(argv[1]))
		{
			printf("calloc %d : %d\n",i , test[i]);
			i++;
		}
	}
	else
		printf("Pas le bon nombre d'arguments !!");
	return (0);
}
*/