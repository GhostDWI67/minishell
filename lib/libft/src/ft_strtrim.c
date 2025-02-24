/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwianni <dwianni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 10:10:53 by dwianni           #+#    #+#             */
/*   Updated: 2024/10/28 22:03:01 by dwianni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_c_in_str(char c, const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*res;
	int		start;
	int		end;
	int		i;

	if (s1 == NULL || set == NULL)
		return (NULL);
	start = 0;
	while (s1[start] != '\0' && ft_c_in_str(s1[start], set) == 1)
		start++;
	end = ft_strlen(s1) - 1;
	while (end > start && ft_c_in_str(s1[end], set) == 1)
		end--;
	res = (char *) malloc(sizeof(char) * (end - start + 2));
	if (res == NULL)
		return (NULL);
	i = 0;
	while (i < end - start + 1)
	{
		res[i] = s1[start + i];
		i++;
	}
	res[i] = '\0';
	return (res);
}
/*
int	main(void)
{
	printf("%s\n", ft_strtrim("       qwerty      ", " "));

}
*/