/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpalisse <mpalisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 11:55:23 by mpalisse          #+#    #+#             */
/*   Updated: 2025/07/03 14:59:04 by mpalisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/******************************************************************************
checks for the -n option
Return 0 without the option and 1 with the option; 
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
		if (i != 1 && i == (int)ft_strlen(str))
			return (1);
	}
	return (0);
}

/******************************************************************************
writes the args in the STDOUT
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
does the echo built-in, writing the args passed to it with the option -n or
not
Return 0; 
******************************************************************************/
int	echo(char **args, t_cmd_line *cmd, int in_child)
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
	if (in_child == 1)
		free_cmd_line_exit(cmd);
	return (0);
}
