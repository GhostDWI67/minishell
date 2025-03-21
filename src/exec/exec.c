/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwianni <dwianni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 22:39:34 by admin             #+#    #+#             */
/*   Updated: 2025/03/21 11:52:20 by dwianni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/******************************************************************************
Function closing fd
******************************************************************************/
static void close_fd(int *fd, int nb_fd)
{
	int	i;

	i = 0;
	while(i < nb_fd)
	{
		close(fd[i]);
		i++;
	}
}

/******************************************************************************
Function manage the child redirection + execution of the command
******************************************************************************/
/* a optimiser : creer une fonction de manage;emt des erreurs
On met un message et on sort un numero de defaut
Mettre des constantes en place dans le .h 
Il faut prevoir de la place pour la suite*/
static int	child(t_cmd_line *cmd, char **environ)
{
	char	*path;

	if (cmd->cmd_step != 0)
	{
		if (dup2(cmd->old_fd[0], STDIN_FILENO) == -1)
			msg_error(ERM_DUP2, ERN_DUP2);
		close_fd(cmd->old_fd, 2);
	}
	if (cmd->cmd_step != cmd->nb_simple_cmd - 1)
	{
		close(cmd->new_fd[0]);
		if (dup2(cmd->new_fd[1], STDOUT_FILENO) == -1)
			msg_error(ERM_DUP2, ERN_DUP2);
		close(cmd->new_fd[1]);
	}
	path = get_path(cmd->tab_path, cmd->tab_cmd[cmd->cmd_step].tab_args[0]);
	if (execve(path, cmd->tab_cmd[cmd->cmd_step].tab_args, environ) == -1)
		msg_error(ERM_EXECVE, ERN_EXECVE);
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

/******************************************************************************
Function manage the mutiple pipe command
Return : 0 if OK other vlue mean NOK
******************************************************************************/
int	f_pipe(t_cmd_line *cmd, char **environ)
{
	pid_t	pid;

	cmd->fd_in = 0;
	cmd->fd_out = 1;
	cmd->old_fd[0] = STDIN_FILENO;
	cmd->old_fd[1] = STDOUT_FILENO;
	cmd->cmd_step = 0;
	while (cmd->cmd_step < cmd->nb_simple_cmd)
	{
		if (cmd->cmd_step < cmd->nb_simple_cmd - 1)
		{
			if (pipe(cmd->new_fd) == -1)
				msg_error(ERM_PIPE, ERN_PIPE);
		}
		pid = fork();
		if (pid == -1)
			msg_error(ERM_FORK, ERN_FORK);
		else if (pid == 0)
			child(cmd, environ);
		else
			parent(cmd);
		cmd->cmd_step++;
	}
	if (cmd->cmd_step != 0)
		close_fd(cmd->old_fd, 2);
	cmd->cmd_step = 0;
	while (cmd->cmd_step < cmd->nb_simple_cmd)
	{
		waitpid(pid, NULL, 0);
		cmd->cmd_step++;
	}
	printf("Le processus parent a temine.\n");
	return (0);
}
