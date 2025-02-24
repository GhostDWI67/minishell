/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwianni <dwianni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 13:13:56 by dwianni           #+#    #+#             */
/*   Updated: 2024/10/28 22:27:56 by dwianni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*res;
	int		i;

	if (s == NULL || f == NULL)
		return (NULL);
	res = (char *) malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (res == NULL)
		return (NULL);
	i = 0;
	while (s[i] != '\0')
	{
		res[i] = (*f)(i, s[i]);
		i++;
	}
	res[i] = '\0';
	return (res);
}
/*
static char	ft_test_toupper(unsigned int index, char c)
{
	index = index * 1;
	if (c >= 'a' && c <= 'z')
		return (c - 32);
	return (c);
}

int	main(void)
{
	printf("%s\n", ft_strmapi("qwert", ft_test_toupper));
	return (0);
}

int	main(int argc, char **argv)
{
	if (argc == 2)
		printf("%s\n", ft_strmapi(argv[1], ft_test_toupper));
	else
		printf("Pas le bon nombre d'arguments !!");
	return (0);
}
*/