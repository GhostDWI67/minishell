/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwianni <dwianni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 11:02:37 by dwianni           #+#    #+#             */
/*   Updated: 2024/10/28 15:06:50 by dwianni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = ft_strlen(s);
	while (i >= 0)
	{
		if (s[i] == (char)c)
			return ((char *)&s[i]);
		i--;
	}
	return (NULL);
}
/*
int	main(int argc, char **argv)
{
	if (argc == 3)
		printf("ft_strrchr : %s\n", ft_strrchr(argv[1], ft_atoi(argv[2])));
	else
		printf("Pas le bon nombre d'arguments !!");
	return (0);
}
*/