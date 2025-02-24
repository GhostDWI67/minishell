/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwianni <dwianni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 14:22:30 by dwianni           #+#    #+#             */
/*   Updated: 2024/10/28 22:34:07 by dwianni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	int	i;

	if (s == NULL || f == NULL)
		return ;
	i = 0;
	while (s[i] != '\0')
	{
		(*f)(i, s + i);
		i++;
	}
}
/*
static void	ft_test_toupper(unsigned int index, char *str)
{
	index = index * 1;
	if (*str >= 'a' && *str <= 'z')
		*str = *str - 32;
}

int	main(void)
{
	ft_striteri(NULL, ft_test_toupper);
	return (0);
}

int	main(int argc, char **argv)
{
	if (argc == 2)
	{
		printf("%s\n", argv[1]);
		ft_striteri(argv[1], ft_test_toupper);
		printf("%s\n", argv[1]);
	}
	else
		printf("Pas le bon nombre d'arguments !!");
	return (0);
}
*/