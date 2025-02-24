/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwianni <dwianni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 08:20:09 by dwianni           #+#    #+#             */
/*   Updated: 2024/10/28 15:20:11 by dwianni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (little[0] == '\0')
		return ((char *)big);
	while (i < len && big[i] != '\0')
	{
		j = 0;
		while (little[j] != '\0' && big[i + j] != '\0' && i + j < len
			&& big[i + j] == little[j])
		{
			j++;
		}
		if (little[j] == '\0')
			return ((char *)(big + i));
		i++;
	}
	return (NULL);
}
/*
int	main(int argc, char **argv)
{
	if (argc == 4)
		printf("ft_strnstr : %s\n",
			ft_strnstr(argv[1], argv[2], ft_atoi(argv[3])));
	else
		printf("Pas le bon nombre d'arguments !!");
	return (0);
}
*/