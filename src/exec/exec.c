/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwianni <dwianni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 22:39:34 by admin             #+#    #+#             */
/*   Updated: 2025/03/30 18:53:18 by dwianni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/******************************************************************************
Function manage the parent + execution of the command
******************************************************************************/
/*
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
*/

/******************************************************************************
Function init the pipes
******************************************************************************/
static void	f_pipe_init(t_cmd_line *cmd)
{
	cmd->cmd_step = 0;
	cmd->fd_in = 0;
	cmd->fd_out = 1;
}

/******************************************************************************
Function wait all the child process to finish
******************************************************************************/
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
	build_pipe(cmd);
	while (cmd->cmd_step < cmd->nb_simple_cmd)
	{
		pid = fork();
		if (pid == -1)
			msg_error(ERM_FORK, ERN_FORK);
		else if (pid == 0)
		{
			child(cmd, environ);
		}
		cmd->cmd_step++;
	}
	close_tab_pipe(cmd);
	f_pipe_wait(cmd);
	return (0);
}
