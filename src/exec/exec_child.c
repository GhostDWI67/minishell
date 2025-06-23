/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwianni <dwianni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 10:35:37 by dwianni           #+#    #+#             */
/*   Updated: 2025/06/23 18:57:00 by dwianni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/******************************************************************************
Function manage the child execution of the command
******************************************************************************/
static void	child_prepare(t_cmd_line *cmd)
{
	if (cmd->tab_cmd[cmd->cmd_step].redir_test == 0)
	{
		close_all_fd(cmd);
		free_cmd_line_exit(cmd);
		exit (ERN_FILE);
	}
	if (is_exec_able(cmd, cmd->cmd_step) != 0)
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
	close(cmd->tab_cmd[cmd->cmd_step].hd_pipe[1]);
}

static void	child_exec(t_cmd_line *cmd, char **environ, char *path)
{
	if (execve(path, cmd->tab_cmd[cmd->cmd_step].tab_args, environ)
		== -1)
	{
		msg_write(cmd, cmd->cmd_step);
		free_cmd_line_exit(cmd);
		exit (ERN_NOTEXEC);
	}
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
		child_exec(cmd, environ, path);
	else
	{
		free(path);
		exec_builtin_c(is_built_in(cmd->tab_cmd[cmd->cmd_step].tab_args),
			cmd);
	}
	return (0);
}
