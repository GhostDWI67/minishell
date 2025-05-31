/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwianni <dwianni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 10:18:41 by dwianni           #+#    #+#             */
/*   Updated: 2025/05/31 15:01:16 by dwianni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/******************************************************************************
Free element of a comd structure
******************************************************************************/
static void	free_cmd(t_cmd_line *cmd)
{
	int	i;

	if (cmd->input != NULL)
		free(cmd->input);
	if (cmd->tab_fd)
		free(cmd->tab_fd);
	if (cmd->tab_pid)
		free(cmd->tab_pid);
	i = 0;
	while (i < cmd->nb_simple_cmd)
	{
		if (cmd->tab_cmd != NULL)
			free_command(cmd->tab_cmd[i]);
		i++;
	}
	if (cmd->tab_cmd)
		free(cmd->tab_cmd);
	if (cmd->token)
		token_clear(&cmd->token);
	if (cmd->tab_path != NULL)
		free_tab_char(cmd->tab_path);
}

/******************************************************************************
Free a command line
Return ; 0 if OK, else 1
******************************************************************************/
int	free_cmd_line(t_cmd_line *cmd)
{
	free_cmd(cmd);
	if (cmd->tab_env)
		free(cmd->tab_env);
	return (0);
}

/******************************************************************************
Free a command line at the exit
Return ; 0 if OK, else 1
******************************************************************************/
int	free_cmd_line_exit(t_cmd_line *cmd)
{
	free_cmd(cmd);
	if (cmd->env)
	{
		ft_lstclear(&cmd->env, free);
		free(cmd->env);
	}
	if (cmd->tab_env)
		free(cmd->tab_env);
	close(cmd->fd_saved_stdout);
	close(cmd->fd_saved_stdin);
	if (cmd)
		free(cmd);
	rl_clear_history();
	return (0);
}
