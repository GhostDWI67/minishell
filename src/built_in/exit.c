/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpalisse <mpalisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 10:28:23 by mpalisse          #+#    #+#             */
/*   Updated: 2025/05/10 17:24:17 by mpalisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/******************************************************************************
check si les args sont bons
Return l'exit status;
******************************************************************************/
static int	check_arg(char *s, bool *error)
{
	int					i;
	int					neg;
	unsigned long long	exit;

	i = 0;
	neg = 1;
	exit = 0;
	while ((9 <= s[i] && s[i] <= 13) || s[i] == 32)
		i++;
	if (s[i] == '+' || s[i] == '-')
		if (s[i++] == '-')
			neg *= -1;
	while ('0' <= s[i] && s[i] <= '9')
		exit = exit * 10 + (s[i++] - '0');
	while ((9 <= s[i] && s[i] <= 13) || s[i] == 32)
		i++;
	if (s[i] || ((neg == -1 && (exit - 1) > LONG_MAX) || \
		(neg == 1 && (exit > LONG_MAX))))
		*error = true;
	return ((int)((exit * neg) % 256));
}

/******************************************************************************
lance la fonction pour clear la memoire puis exit avec le bon status
Return void;
******************************************************************************/
void	free_exit(t_cmd_line *cmd, bool err, int exit_status)
{
	if (err == false)
		ft_putstr_fd("exit\n", 1);
	free_cmd_line_exit(cmd);
	//cmd->exit_code = exit_status;
	exit(exit_status);
}

/******************************************************************************
lance exit avec le bon retour en fonction des args
Return void;
******************************************************************************/
int	ft_exit(t_cmd_line *cmd, char **args)
{
	int		exit_status;
	bool	error;

	error = false;
	exit_status = 0;
	if (!args[1])
		free_exit(cmd, error, exit_status);
	if (args[1])
	{
		exit_status = check_arg(args[1], &error);
		if (error)
		{
			ft_perror("exit: ");
			ft_perror(args[1]);
			ft_perror(": numeric argument required\n");
			free_exit(cmd, error, 2);
		}
	}
	if (args[1] && args[2])
	{
		exit_status = msg_inf(ERM_EXIT, ERN_EXIT);
		cmd->exit_code = exit_status;
		return (exit_status);
	}
	free_exit(cmd, error, exit_status);
	return (0);
}
