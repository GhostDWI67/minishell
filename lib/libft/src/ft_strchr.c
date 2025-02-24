/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwianni <dwianni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 09:41:20 by dwianni           #+#    #+#             */
/*   Updated: 2024/10/28 17:26:56 by dwianni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
			return ((char *)&s[i]);
		i++;
	}
	if (s[i] == (char) c)
		return ((char *)&s[i]);
	return (NULL);
}
/*
int	main(int argc, char **argv)
{
	if (argc == 3)
		printf("ft_strchr : %s\n", ft_strchr(argv[1], ft_atoi(argv[2])));
	else
		printf("Pas le bon nombre d'arguments !!");
	return (0);
}
*/