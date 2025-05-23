/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwianni <dwianni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 10:35:37 by dwianni           #+#    #+#             */
/*   Updated: 2025/05/24 19:23:46 by dwianni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/******************************************************************************
Function test if all the simple command are executable
Return : 0 if OK else NOK (nb functions doesn't exist)
******************************************************************************/
static int	is_exec_able(t_cmd_line *cmd, int i)
{
	char	*path;

	path = NULL;
	if (cmd->tab_cmd[i].tab_args == NULL)
		return (cmd->exit_code = 0, cmd->exit_code);
	
	if (cmd->tab_cmd[i].tab_args[0] != NULL
		&& is_built_in(cmd->tab_cmd[i].tab_args) == 0)
		path = get_path(cmd->tab_path, cmd->tab_cmd[i].tab_args[0], cmd);
	
	if (path == NULL && cmd->err_nb == ERN_ISDIR) //reglage pb / double message
		return (ERN_ISDIR);
	if (path == NULL && cmd->err_nb == ERN_NOTFD) //
		return (ERN_NOTFD);
	// if (path == NULL && cmd->tab_cmd[i].tab_args[0] != NULL
	// 		&& is_built_in(cmd->tab_cmd[i].tab_args) == 0
	// 		&& cmd->exit_code != 0)
	// 	{
	// 		free(path);
	// 		return (cmd->exit_code);
	// 	}
	if (path == NULL && cmd->tab_cmd[i].tab_args[0] != NULL
		&& is_built_in(cmd->tab_cmd[i].tab_args) == 0)
	{
		ft_putstr_fd("Command '", 2);
		ft_putstr_fd(cmd->tab_cmd[i].tab_args[0], 2);
		ft_putstr_fd("' not found\n", 2);
		cmd->exit_code = ERN_NOTEXEC;
		return (ERN_NOTEXEC);
	}
	return (0);
}

/******************************************************************************
Function manage the child redirection + execution of the command
******************************************************************************/
static void	child_redir_mgt_in(t_cmd_line *cmd)
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

static void	child_redir_mgt_out(t_cmd_line *cmd)
{
	if (cmd->tab_cmd[cmd->cmd_step].fd_outfile > 1)
	{
		if (dup2(cmd->tab_cmd[cmd->cmd_step].fd_outfile, STDOUT_FILENO) == -1)
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

static void	child_prepare(t_cmd_line *cmd)
{
	if (cmd->tab_cmd[cmd->cmd_step].redir_test == 0)
		exit (ERN_FILE);
	if (is_exec_able(cmd, cmd->cmd_step) != 0)
		free_exit(cmd, true, cmd->exit_code);
		//exit (ERN_NOTEXEC);
	child_redir_mgt_in(cmd);
	child_redir_mgt_out(cmd);
	close_tab_pipe(cmd);
	close(cmd->tab_cmd[cmd->cmd_step].hd_pipe[0]);
	close(cmd->tab_cmd[cmd->cmd_step].hd_pipe[1]);
}

int	child(t_cmd_line *cmd, char **environ)
{
	char	*path;

	path = NULL;
	//ft_putstr_fd("CHILD Point 1\n", 2);//
	child_prepare(cmd);
	//ft_putstr_fd("CHILD Point 2\n", 2);//
	if (cmd->tab_cmd[cmd->cmd_step].tab_args == NULL)
	{
		ft_putstr_fd("CHILD Point 2-BIS\n", 2);//
		free(cmd->tab_cmd[cmd->cmd_step].tab_args);
		if (cmd->env)
		{	
			ft_lstclear(&cmd->env, free);
			free(cmd->env);
		}
		free_cmd_line(cmd);
		free(cmd);
		exit(0);
	}
	//ft_putstr_fd("CHILD Point 3\n", 2);//
	path = get_path(cmd->tab_path, cmd->tab_cmd[cmd->cmd_step].tab_args[0], cmd);
	if (cmd->tab_cmd[cmd->cmd_step].fd_infile > 0)
		close(cmd->tab_cmd[cmd->cmd_step].fd_infile);
	if (cmd->tab_cmd[cmd->cmd_step].fd_outfile > 2)
		close(cmd->tab_cmd[cmd->cmd_step].fd_outfile);
	close(cmd->fd_saved_stdin);
	close(cmd->fd_saved_stdout);
	signalquit();
	//ft_putstr_fd("CHILD Point 4\n", 2);//
	//ft_putstr_fd(cmd->tab_cmd[cmd->cmd_step].tab_args[0], 2);//
	if (cmd->tab_cmd[cmd->cmd_step].tab_args[0] != NULL
		&& is_built_in(cmd->tab_cmd[cmd->cmd_step].tab_args) == 0)
	{
		//ft_putstr_fd("CHILD Point 5\n", 2);//
		if (execve(path, cmd->tab_cmd[cmd->cmd_step].tab_args, environ)
			== -1)
			cmd->exit_code = msg_error(ERM_EXECVE, ERN_EXECVE);
	}
	else
	{
		//ft_putstr_fd("CHILD Point 6\n", 2);//
		free(path);
		exec_builtin_c(is_built_in(cmd->tab_cmd[cmd->cmd_step].tab_args),
			cmd);
	}
	return (0);
}
