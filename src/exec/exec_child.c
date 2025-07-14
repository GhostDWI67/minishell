/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwianni <dwianni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 10:35:37 by dwianni           #+#    #+#             */
/*   Updated: 2025/07/13 18:00:47 by dwianni          ###   ########.fr       */
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
		if (cmd->nb_simple_cmd > 1)
		{
			close(cmd->pipe_fd[0]);
			close(cmd->pipe_fd[1]);
			if (cmd->prev_fd != -1)
				close(cmd->prev_fd);
		}
		close_all_fd(cmd);
		free_cmd_line_exit(cmd);
		exit (ERN_FILE);
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
	if (cmd->tab_cmd[cmd->cmd_step].hd_test != 0)
		close(cmd->tab_cmd[cmd->cmd_step].hd_pipe[1]);
}

static void	child_exec(t_cmd_line *cmd, char **environ, char *path)
{
	//setup_sigs_exec();//toto
	if (path == NULL || execve(path, \
		cmd->tab_cmd[cmd->cmd_step].tab_args, environ) == -1)
	{
		if (path == NULL && cmd->err_nb == ERN_ISDIR)
		{
			free_cmd_line_exit(cmd);
			exit (ERN_ISDIR);
		}
		else if (path == NULL && cmd->err_nb == ERN_NOTFD)
		{
			free_cmd_line_exit(cmd);
			exit (ERN_NOTFD);
		}
		else if (path == NULL && cmd->err_nb == ERN_PERM)
		{
			free_cmd_line_exit(cmd);
			exit (ERN_PERM);
		}
		msg_write(cmd, cmd->cmd_step);
		free_cmd_line_exit(cmd);
		exit (ERN_NOTEXEC);
	}
}

int	child(t_cmd_line *cmd, char **environ)
{
	char	*path;

	//setup_sigs_exec();//toto
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
