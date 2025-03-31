/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwianni <dwianni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 22:39:34 by admin             #+#    #+#             */
/*   Updated: 2025/03/31 17:49:37 by dwianni          ###   ########.fr       */
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
	//cmd->cmd_step = 0;
	cmd->fd_in = 0;
	cmd->fd_out = 1;
	cmd->tab_pid = malloc(sizeof(int) * cmd->nb_simple_cmd);
}

/******************************************************************************
Function wait all the child process to finish
******************************************************************************/
static void	f_pipe_wait(t_cmd_line *cmd)
{
	int	status;
	int	i;

	i = 0;
	while (i < cmd->nb_simple_cmd)
	{
		wait(&status);
		i++;
	}
}

/******************************************************************************
Function manage the mutiple pipe command
Return : 0 if OK other vlue mean NOK
******************************************************************************/
int	f_pipe(t_cmd_line *cmd, char **environ)
{
	int		j;

	f_pipe_init(cmd);
	build_pipe(cmd);
	j = 0;
	if(cmd->tab_pid != NULL)
	{
		while (j < cmd->nb_simple_cmd)
		{
			//ft_putstr_fd("toto IN WHILE PIPE !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n",2);
			//ft_putnbr_fd(j, 2);
			//ft_putstr_fd("\n",2);
			cmd->tab_pid[j] = fork();
			if (cmd->tab_pid[j] == -1)
				msg_error(ERM_FORK, ERN_FORK);
			else if (cmd->tab_pid[j] == 0)
			{
				ft_putstr_fd("toto AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\n",2);
				child(cmd, environ, j);
			}
			//ft_putstr_fd("toto IN WHILE PIPE OUUUUTTTTT !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n",2);
			//ft_putnbr_fd(j, 2);
			//ft_putstr_fd("\n",2);
			//cmd->cmd_step++;
			j++;
		}
	}
	//ft_putstr_fd("toto FINAL OUTPUT --------------------------------------------\n",2);
	close_tab_pipe(cmd);
	f_pipe_wait(cmd);
	return (0);
}
