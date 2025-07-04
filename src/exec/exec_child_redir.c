/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_child_redir.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwianni <dwianni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 13:58:12 by dwianni           #+#    #+#             */
/*   Updated: 2025/07/04 16:27:55 by dwianni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/******************************************************************************
Function manage the child redirection
******************************************************************************/
void	child_redir_mgt_in(t_cmd_line *cmd)
{
	if (cmd->tab_cmd != NULL)
	{
		if (cmd->cmd_step == 0)
		{
			if (dup2(cmd->tab_cmd[cmd->cmd_step].fd_infile, STDIN_FILENO) == -1)
				cmd->exit_code = msg_error(ERM_DUP2, ERN_DUP2);
		}
		else if (cmd->cmd_step > 0 && cmd->tab_cmd[cmd->cmd_step].fd_infile > 0)
		{
			if (cmd->prev_fd != -1)
				close(cmd->prev_fd);
			if (dup2(cmd->tab_cmd[cmd->cmd_step].fd_infile, STDIN_FILENO) == -1)
				cmd->exit_code = msg_error(ERM_DUP2, ERN_DUP2);
			close(cmd->tab_cmd[cmd->cmd_step].fd_infile);
		}
		else if (cmd->cmd_step > 0)
		{
			if (dup2(cmd->prev_fd, STDIN_FILENO) == -1)
				cmd->exit_code = msg_error(ERM_DUP2, ERN_DUP2);
			if (cmd->prev_fd != -1)
				close(cmd->prev_fd);
		}
	}
}

void	child_redir_mgt_out(t_cmd_line *cmd)
{
	if (cmd->tab_cmd != NULL)
	{
		if (cmd->tab_cmd[cmd->cmd_step].fd_outfile > 1)
		{
			if (dup2(cmd->tab_cmd[cmd->cmd_step].fd_outfile, \
				STDOUT_FILENO) == -1)
				cmd->exit_code = msg_error(ERM_DUP2, ERN_DUP2);
			close(cmd->tab_cmd[cmd->cmd_step].fd_outfile);
		}
		else if (cmd->cmd_step < cmd->nb_simple_cmd - 1)
		{
			if (dup2(cmd->pipe_fd[1], STDOUT_FILENO) == -1)
			{
				cmd->exit_code = msg_error(ERM_DUP2, ERN_DUP2);
			}
			close(cmd->pipe_fd[0]);
			close(cmd->pipe_fd[1]);
		}
	}
}
