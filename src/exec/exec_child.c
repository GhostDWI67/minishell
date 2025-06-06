/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwianni <dwianni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 10:35:37 by dwianni           #+#    #+#             */
/*   Updated: 2025/05/31 17:25:13 by dwianni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/******************************************************************************
Function manage the child redirection + execution of the command
******************************************************************************/
static void	child_redir_mgt_in(t_cmd_line *cmd)
{
	if (cmd->tab_cmd != NULL && cmd->tab_fd != NULL)
	{
		if (cmd->cmd_step == 0)
		{
			if (dup2(cmd->tab_cmd[cmd->cmd_step].fd_infile, STDIN_FILENO) == -1)
				cmd->exit_code = msg_error(ERM_DUP2, ERN_DUP2);
		}
		else if (cmd->cmd_step > 0 && cmd->tab_cmd[cmd->cmd_step].fd_infile > 0)
		{
			if (dup2(cmd->tab_cmd[cmd->cmd_step].fd_infile, STDIN_FILENO) == -1)
				cmd->exit_code = msg_error(ERM_DUP2, ERN_DUP2);
			close(cmd->tab_cmd[cmd->cmd_step].fd_infile);
		}
		else if (cmd->cmd_step > 0)
		{
			if (dup2(cmd->tab_fd[2 * cmd->cmd_step - 2], STDIN_FILENO) == -1)
				cmd->exit_code = msg_error(ERM_DUP2, ERN_DUP2);
		}
	}
}

static void	child_redir_mgt_out(t_cmd_line *cmd)
{
	if (cmd->tab_cmd != NULL && cmd->tab_fd != NULL)
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
			if (dup2(cmd->tab_fd[2 * cmd->cmd_step + 1], STDOUT_FILENO) == -1)
			{
				cmd->exit_code = msg_error(ERM_DUP2, ERN_DUP2);
			}
		}
	}
}

static void	child_prepare(t_cmd_line *cmd)
{
	if (cmd->tab_cmd[cmd->cmd_step].redir_test == 0)
	{
		close_all_fd(cmd);
		free_cmd_line_exit(cmd);
		exit (ERN_FILE);
	}
	if (cmd->tab_fd == NULL || is_exec_able(cmd, cmd->cmd_step) != 0)
	{
		close_all_fd(cmd);
		free_exit(cmd, true, cmd->exit_code);
	}
	child_redir_mgt_in(cmd);
	child_redir_mgt_out(cmd);
	close_all_fd(cmd);
}

static void	child_closefd(t_cmd_line *cmd)
{
	if (cmd->tab_cmd[cmd->cmd_step].fd_infile > 0)
		close(cmd->tab_cmd[cmd->cmd_step].fd_infile);
	if (cmd->tab_cmd[cmd->cmd_step].fd_outfile > 2)
		close(cmd->tab_cmd[cmd->cmd_step].fd_outfile);
	close(cmd->fd_saved_stdin);
	close(cmd->fd_saved_stdout);
}

int	child(t_cmd_line *cmd, char **environ)
{
	char	*path;

	child_prepare(cmd);
	if (cmd->tab_cmd[cmd->cmd_step].tab_args == NULL)
	{
		free_cmd_line_exit(cmd);
		exit(0);
	}
	path = get_path(cmd->tab_path, \
		cmd->tab_cmd[cmd->cmd_step].tab_args[0], cmd);
	child_closefd(cmd);
	if (cmd->tab_cmd[cmd->cmd_step].tab_args[0] != NULL
		&& is_built_in(cmd->tab_cmd[cmd->cmd_step].tab_args) == 0)
	{
		if (execve(path, cmd->tab_cmd[cmd->cmd_step].tab_args, environ)
			== -1)
			cmd->exit_code = msg_error(ERM_EXECVE, ERN_EXECVE);
	}
	else
	{
		free(path);
		exec_builtin_c(is_built_in(cmd->tab_cmd[cmd->cmd_step].tab_args),
			cmd);
	}
	return (0);
}
