/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwianni <dwianni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 10:35:37 by dwianni           #+#    #+#             */
/*   Updated: 2025/03/30 19:29:45 by dwianni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/******************************************************************************
Function manage the child redirection + execution of the command
******************************************************************************/
static void	child_redir_mgt_in(t_cmd_line *cmd)
{
	if (cmd->cmd_step == 0)
	{
		if (dup2(cmd->tab_cmd[cmd->cmd_step].fd_infile, STDIN_FILENO) == -1)
			msg_error(ERM_DUP2, ERN_DUP2);
	}
	else if (cmd->cmd_step > 0 && cmd->tab_cmd[cmd->cmd_step].fd_infile > 0)
	{
		if (dup2(cmd->tab_cmd[cmd->cmd_step].fd_infile, STDIN_FILENO) == -1)
			msg_error(ERM_DUP2, ERN_DUP2);
	}
	else if (cmd->cmd_step > 0)
	{
		if (dup2(cmd->tab_fd[2 * cmd->cmd_step - 2], STDIN_FILENO) == -1)
			msg_error(ERM_DUP2, ERN_DUP2);
	}
}

static void	child_redir_mgt_out(t_cmd_line *cmd)
{
	if (cmd->tab_cmd[cmd->cmd_step].fd_outfile > 1)
	{
		if (dup2(cmd->tab_cmd[cmd->cmd_step].fd_outfile, STDOUT_FILENO) == -1)
		{
			close(cmd->tab_cmd[cmd->cmd_step].fd_outfile);
			msg_error(ERM_DUP2, ERN_DUP2);
		}
	}
	else if (cmd->cmd_step < cmd->nb_simple_cmd - 1)
	{
		if (dup2(cmd->tab_fd[2 * cmd->cmd_step + 1], STDOUT_FILENO) == -1)
		{
			msg_error(ERM_DUP2, ERN_DUP2);
		}
	}
}

static int	child_infile_name(t_cmd_line *cmd)
{
	char	*msg;

	if (cmd->tab_cmd[cmd->cmd_step].fd_infile == -1)
	{
		msg = ft_strjoin(ERM_FILE, cmd->tab_cmd[cmd->cmd_step].infile);
		msg_error(msg, ERN_FILE);
		free(msg);
		return (1);
	}
	return (0);
}

int	child(t_cmd_line *cmd, char **environ)
{
	char	*path;
	char	*msg;

	child_infile_name(cmd);
	if (cmd->tab_cmd[cmd->cmd_step].fd_outfile == -1)
	{
		msg = ft_strjoin(ERM_FILE, cmd->tab_cmd[cmd->cmd_step].outfile);
		msg_error(msg, ERN_FILE);
		free(msg);
		return (1);
	}
	else
	{
		child_redir_mgt_in(cmd);
		child_redir_mgt_out(cmd);
		close_tab_pipe(cmd);
		path = get_path(cmd->tab_path, cmd->tab_cmd[cmd->cmd_step].tab_args[0]);
		if (execve(path, cmd->tab_cmd[cmd->cmd_step].tab_args, environ) == -1)
			msg_error(ERM_EXECVE, ERN_EXECVE);
	}
	return (0);
}
