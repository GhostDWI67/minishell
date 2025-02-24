/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwianni <dwianni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 08:57:11 by dwianni           #+#    #+#             */
/*   Updated: 2024/10/28 22:16:06 by dwianni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*test_start_to_high(void)
{
	char	*res;

	res = (char *)malloc(sizeof(char) * (1));
	if (res == NULL)
		return (NULL);
	res[0] = '\0';
	return (res);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*res;
	size_t	i;

	if (s == NULL)
		return (NULL);
	if (start > (unsigned int)ft_strlen(s))
		return (test_start_to_high());
	if (len <= ft_strlen(s) - start)
		res = (char *)malloc(sizeof(char) * (len + 1));
	else
		res = (char *)malloc(sizeof(char) * (ft_strlen(s) - start + 1));
	if (res == NULL)
		return (NULL);
	i = 0;
	while (s[i] != '\0' && i < len)
	{
		res[i] = s [i + start];
		i++;
	}
	res[i] = '\0';
	return (res);
}
/*
int	main(void)
{
	//printf("%s\n", ft_substr("hola", 4294967295, 18446744073709551615));
	printf("%s\n", ft_substr(NULL, 1, 5));
	return (0);
}
*/