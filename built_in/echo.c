/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpalisse <mpalisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 11:55:23 by mpalisse          #+#    #+#             */
/*   Updated: 2025/04/20 15:14:52 by mpalisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/******************************************************************************
check l'option n et normalement toute les variations du type:
-n, ---n, -nn, -nnnnnnnn, - n, -, n 
Return 0 sans l'option et 1 avec l'option; 
******************************************************************************/
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

/******************************************************************************
la fonction qui ecrit dans le terminal
Aucun return 
******************************************************************************/
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
la fonction echo avec l'option -n ou non qui affiche le text passé en arg 
dans le terminal.
si -n alors il n'y a pas de "\n" a la fin, sans -n alors il y a un "\n" a la fin
Return 0; 
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
