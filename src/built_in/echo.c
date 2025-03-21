/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwianni <dwianni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 11:55:23 by mpalisse          #+#    #+#             */
/*   Updated: 2025/03/21 16:00:05 by dwianni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

static int	check_n(char *str)
{
	int	i;

	i = 0;
	if (str[i] && str[i] == '-')
	{
		i++;
		while (str[i] && str[i] == 'n')
			i++;
		if (i == (int)ft_strlen(str))
			return (1);
	}
	return (0);
}

static void	echo_core(char **args, bool n, int i, int count)
{
	while (args[i] && check_n(args[i]))
	{
		i++;
		n = false;
	}
	while (i < count)
	{
		write(1, args[i], ft_strlen(args[i]));
		if (i != count - 1)
			write(1, " ", 1);
		i++;
	}
	if (n)
		write(1, "\n", 1);
}

/******************************************************************************

Return ; 
******************************************************************************/

int	echo(char **args)
{
	bool	n;
	int		i;
	int		count;

	count = 0;
	while (args[count])
		count++;
	i = 1;
	n = true;
	echo_core(args, n, i, count);
	return (0);
}
/*
int	main(int argc, char **argv)
{
	(void)argc;
	echo(argv);
	return (0);
}
*/