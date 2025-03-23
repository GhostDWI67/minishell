/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwianni <dwianni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 22:39:34 by admin             #+#    #+#             */
/*   Updated: 2025/03/23 18:41:56 by dwianni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/******************************************************************************
Function manage the child redirection + execution of the command
******************************************************************************/
static int	child(t_cmd_line *cmd, char **environ)
{
	char	*path;
	char	*msg;

	//write(2, &"hello world33!\n", 15);
	if (cmd->tab_cmd[cmd->cmd_step].fd_infile == -1)
	{
		msg = ft_strjoin(ERM_FILE, cmd->tab_cmd[cmd->cmd_step].infile);
		msg_error(msg, ERN_FILE);
		free(msg);
		return (1);
	}
	if (cmd->tab_cmd[cmd->cmd_step].fd_outfile == -1)
	{
		msg = ft_strjoin(ERM_FILE, cmd->tab_cmd[cmd->cmd_step].outfile);
		msg_error(msg, ERN_FILE);
		free(msg);
		return (1);
	}
	else
	{
		//write(2, &"hello world34!\n", 15);
		if (cmd->cmd_step != 0)
		{
			if (dup2(cmd->old_fd[0], STDIN_FILENO) == -1)
				msg_error(ERM_DUP2, ERN_DUP2);
			close_fd(cmd->old_fd, 2);
		}
		if (cmd->tab_cmd[cmd->cmd_step].fd_infile != STDIN_FILENO)
		{
			if (dup2(cmd->tab_cmd[cmd->cmd_step].fd_infile, STDIN_FILENO) == -1)
				msg_error(ERM_DUP2, ERN_DUP2);
			close(cmd->tab_cmd[cmd->cmd_step].fd_infile);
		}
		if (cmd->cmd_step != cmd->nb_simple_cmd - 1)
		{
			close(cmd->new_fd[0]);
			if (dup2(cmd->new_fd[1], STDOUT_FILENO) == -1)
				msg_error(ERM_DUP2, ERN_DUP2);
			close(cmd->new_fd[1]);
		}
		//write(2, &"hello world35!\n", 15);
		if (cmd->tab_cmd[cmd->cmd_step].fd_outfile != STDOUT_FILENO)
		{
			//write(2, &"hello world36!\n", 15);
			if (dup2(cmd->tab_cmd[cmd->cmd_step].fd_outfile, STDOUT_FILENO) == -1)
				msg_error(ERM_DUP2, ERN_DUP2);
			close(cmd->tab_cmd[cmd->cmd_step].fd_outfile);
		}
		//write(2, &"hello world37!\n", 15);
		path = get_path(cmd->tab_path, cmd->tab_cmd[cmd->cmd_step].tab_args[0]);
		if (execve(path, cmd->tab_cmd[cmd->cmd_step].tab_args, environ) == -1)
			msg_error(ERM_EXECVE, ERN_EXECVE);
	}
	return (0);
}

/******************************************************************************
Function manage the parent + execution of the command
******************************************************************************/
static void	parent(t_cmd_line *cmd)
{
	if (cmd->cmd_step != 0)
		close_fd(cmd->old_fd, 2);
	if (cmd->cmd_step != cmd->nb_simple_cmd - 1)
	{
		cmd->old_fd[0] = cmd->new_fd[0];
		cmd->old_fd[1] = cmd->new_fd[1];
	}
}

static void	f_pipe_init(t_cmd_line *cmd)
{
	cmd->cmd_step = 0;
	cmd->fd_in = 0;
	cmd->fd_out = 1;
	cmd->old_fd[0] = STDIN_FILENO;
	cmd->old_fd[1] = STDOUT_FILENO;
}

static void	f_pipe_wait(t_cmd_line *cmd)
{
	int	status;

	cmd->cmd_step = 0;
	while (cmd->cmd_step < cmd->nb_simple_cmd)
	{
		wait(&status);
		cmd->cmd_step++;
	}
}

/******************************************************************************
Function manage the mutiple pipe command
Return : 0 if OK other vlue mean NOK
******************************************************************************/
int	f_pipe(t_cmd_line *cmd, char **environ)
{
	pid_t	pid;

	f_pipe_init(cmd);
	while (cmd->cmd_step < cmd->nb_simple_cmd)
	{
		//cmd->old_fd[0] = cmd->tab_cmd[cmd->cmd_step].fd_infile; //INFILE
		//ft_putstr_fd("cmd step dqns f_pipe",2);
		//ft_putnbr_fd(cmd->cmd_step,2);
		//ft_putstr_fd("---\n",2);
		//write(2, &"hello world31!\n", 15);
		if (cmd->cmd_step < cmd->nb_simple_cmd - 1)
		{
			if (pipe(cmd->new_fd) == -1)
				msg_error(ERM_PIPE, ERN_PIPE);
		}
		pid = fork();
		if (pid == -1)
			msg_error(ERM_FORK, ERN_FORK);
		else if (pid == 0)
		{
			//write(2, &"hello world32!\n", 15);
			child(cmd, environ);
		}
		else
			parent(cmd);
		cmd->cmd_step++;
	}
	if (cmd->cmd_step > 1)
		close_fd(cmd->old_fd, 2);
	f_pipe_wait(cmd);
	return (0);
}
