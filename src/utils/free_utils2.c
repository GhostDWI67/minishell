/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpalisse <mpalisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 11:35:21 by mpalisse          #+#    #+#             */
/*   Updated: 2025/05/17 12:27:34 by mpalisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	free_cmd(t_cmd_line *cmd)
{
	if (cmd->input != NULL)
		free(cmd->input);
	if (cmd->env)
	{
		ft_lstclear(&cmd->env, free);
		free(cmd->env);
	}
	free(cmd->tab_env);
	if (cmd)
		free(cmd);
	rl_clear_history();
	return (0);
}

void	free_exit_ctrld(t_cmd_line *cmd, bool err, int exit_status)
{
	if (err == false)
		ft_putstr_fd("exit\n", 1);
	free_cmd(cmd);
	exit(exit_status);
}
