/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwianni <dwianni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 16:49:16 by dwianni           #+#    #+#             */
/*   Updated: 2024/10/28 22:40:38 by dwianni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_char_comp(char c1, char c2)
{
	if ((unsigned char)c1 != (unsigned char)c2)
		return ((unsigned char)c1 - (unsigned char)c2);
	return (0);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	if (n == 0)
		return (0);
	i = 0;
	while (ft_char_comp(s1[i], s2[i]) == 0 && s1[i] != '\0'
		&& s2[i] != '\0' && i < (n - 1))
		i++;
	return (ft_char_comp(s1[i], s2[i]));
}
/*
int	main(int argc, char **argv)
{
	if (argc == 4)
		printf("ft_strncmp : %d\n",
			ft_strncmp(argv[1], argv[2], ft_atoi(argv[3])));
	else
		printf("Pas le bon nombre d'arguments !!");
	return (0);
}
*/