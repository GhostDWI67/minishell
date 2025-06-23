/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwianni <dwianni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 22:39:34 by admin             #+#    #+#             */
/*   Updated: 2025/06/23 13:44:44 by dwianni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/******************************************************************************
Function init the pipes and other parameters
******************************************************************************/
static void	f_exec_init(t_cmd_line *cmd)
{
	cmd->cmd_step = 0;
	cmd->tab_pid = malloc(sizeof(int) * cmd->nb_simple_cmd);
	cmd->cmd_step = 0;
}

/******************************************************************************
Function wait all the child process to finish
Catch the exit code status of each child
******************************************************************************/
static void	f_exec_wait(t_cmd_line *cmd)
{
	int	status;
	int	i;

	i = 0;
	while (i < cmd->nb_simple_cmd)
	{
		if (waitpid(cmd->tab_pid[i], &status, WUNTRACED) == -1)
			cmd->exit_code = msg_error(ERM_WAITPID, ERN_WAITPID);
		if (WIFEXITED(status))
			cmd->exit_code = WEXITSTATUS(status);
		i++;
	}
}

/******************************************************************************
Function parent
******************************************************************************/
static void	parent(t_cmd_line *cmd)
{
	if (cmd->cmd_step > 0)
		close (cmd->prev_fd);
	if (cmd->cmd_step < cmd->nb_simple_cmd - 1)
	{
		close(cmd->pipe_fd[1]);
		cmd->prev_fd = cmd->pipe_fd[0];
	}
}

/******************************************************************************
Function manage the mutiple pipe command
******************************************************************************/
static void	f_exec_bi_parent(t_cmd_line *cmd)
{
	parent_redir_mgt_in_out(cmd);
	if (cmd->tab_cmd[0].redir_test == 1)
		cmd->exit_code = exec_builtin_p(is_built_in
				(cmd->tab_cmd[cmd->cmd_step].tab_args), cmd);
	else
		cmd->exit_code = ERN_FILE;
}

void	f_exec(t_cmd_line *cmd, char **environ)
{
	cmd->prev_fd = -1;
	f_exec_init(cmd);
	if (cmd->tab_pid != NULL)
	{
		if (cmd->nb_simple_cmd == 1
			&& is_built_in(cmd->tab_cmd[cmd->cmd_step].tab_args) != 0)
			f_exec_bi_parent(cmd);
		else
		{
			while (cmd->cmd_step < cmd->nb_simple_cmd)
			{
				if (cmd->cmd_step < cmd->nb_simple_cmd - 1)
					pipe(cmd->pipe_fd);
				cmd->tab_pid[cmd->cmd_step] = fork();
				if (cmd->tab_pid[cmd->cmd_step] == -1)
					cmd->exit_code = msg_error(ERM_FORK, ERN_FORK);
				else if (cmd->tab_pid[cmd->cmd_step] == 0)
					child(cmd, environ);
				else
					parent(cmd);
				cmd->cmd_step++;
			}
			f_exec_wait(cmd);
		}
	}
}
