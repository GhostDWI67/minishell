/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwianni <dwianni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 11:52:13 by dwianni           #+#    #+#             */
/*   Updated: 2024/10/25 13:12:35 by dwianni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_size_itoa(int n)
{
	int	size_itoa;

	size_itoa = 0;
	if (n < 0)
		size_itoa++;
	if (n == 0)
		size_itoa++;
	while (n != 0)
	{
		n = n / 10;
		size_itoa++;
	}
	return (size_itoa);
}

char	*ft_itoa(int n)
{
	char	*res;
	int		i;

	res = (char *) malloc(sizeof(char) * (ft_size_itoa(n) + 1));
	if (res == NULL)
		return (NULL);
	res[ft_size_itoa(n)] = '\0';
	if (n == -2147483648)
		return (ft_memcpy(res, "-2147483648", 11));
	if (n == 0)
		return (ft_memcpy(res, "0", 1));
	i = ft_size_itoa(n) - 1;
	if (n < 0)
	{
		res[0] = '-';
		n = -n;
	}
	while (n != 0)
	{
		res[i] = n % 10 + '0';
		n = n / 10;
		i--;
	}
	return (res);
}
/*
int	main(void)
{
	char	*test;

	test = ft_itoa(-2147483648);
	printf("%s\n", test);
	free (test);
	printf("%s \n", ft_itoa(0));
	printf("%s \n", ft_itoa(-2147483648));
	printf("%s \n", ft_itoa(2147483647));
	printf("%s \n", ft_itoa(-123456789));
	return (0);
}
*/
/*
int	main(int argc, char **argv)
{
	char	*test;

	test = ft_itoa(ft_atoi(argv[1]));
	if (argc == 2)
	{
		printf("%s\n", test);
		free (test);
	}
	else
		printf("Pas le bon nombre d'arguments !!");
	return (0);
}
*/
