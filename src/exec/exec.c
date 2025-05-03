/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwianni <dwianni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 22:39:34 by admin             #+#    #+#             */
/*   Updated: 2025/05/02 17:40:13 by dwianni          ###   ########.fr       */
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
	cmd->tab_pid = malloc(sizeof(int) * cmd->nb_simple_cmd);
}

/******************************************************************************
Function wait all the child process to finish
Catch the exit code status

******************************************************************************/
static void	f_pipe_wait(t_cmd_line *cmd)
{
	int	status;
	int	i;

	i = 0;
	while (i < cmd->nb_simple_cmd)
	{
		if(waitpid(cmd->tab_pid[i], &status, WUNTRACED) == -1)
			msg_error(ERM_WAITPID, ERN_WAITPID);
		if (WIFEXITED(status))
			cmd->exit_code = WEXITSTATUS(status);
		i++;
	}
}

/******************************************************************************
Function manage the mutiple pipe command
Return : 0 if OK other vlue mean NOK
******************************************************************************/
int	f_pipe(t_cmd_line *cmd, char **environ)
{
	f_pipe_init(cmd);
	build_pipe(cmd);
	cmd->cmd_step = 0;
	if (cmd->tab_pid != NULL)
	{
		if (cmd->nb_simple_cmd == 1
			&& is_built_in(cmd->tab_cmd[cmd->cmd_step].tab_args[0]) != 0)
		{
			parent_redir_mgt_in_out(cmd);
			cmd->exit_code = exec_builtin_p(is_built_in
				(cmd->tab_cmd[cmd->cmd_step].tab_args[0]),cmd);
		}
		else
		{
			while (cmd->cmd_step < cmd->nb_simple_cmd)
			{
				cmd->tab_pid[cmd->cmd_step] = fork();
				if (cmd->tab_pid[cmd->cmd_step] == -1)
					msg_error(ERM_FORK, ERN_FORK);
				else if (cmd->tab_pid[cmd->cmd_step] == 0)
				{
					child(cmd, environ);
				}
				else
				{
				}
				cmd->cmd_step++;
			}
			close_tab_pipe(cmd);
			f_pipe_wait(cmd);
		}
	}
	return (0);
}
