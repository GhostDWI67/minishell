/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwianni <dwianni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 22:39:34 by admin             #+#    #+#             */
/*   Updated: 2025/03/17 19:29:18 by dwianni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/******************************************************************************
Get a tab of path
Check if the function is executable with the different path
Return a string : path/fexec
******************************************************************************/
char	*get_path(char **tab_path, char *fexec)
{
	char	*path;
	char	*p_to_test;
	int		i;

	if (tab_path != NULL)
	{
		i = 0;
		while (tab_path[i] != NULL)
		{
			path = ft_strjoin(tab_path[i], "/");
			p_to_test = ft_strjoin(path, fexec);
			if (access(p_to_test, X_OK) == 0)
				return (free(path), p_to_test);
			else
			{
				free(path);
				free(p_to_test);
			}
			i++;
		}
	}
	return (NULL);
}

/******************************************************************************
Function manage the child redirection + execution of the command
******************************************************************************/
/* a optimiser : creer une fonction de manage;emt des erreurs
On met un message et on sort un numero de defaut
Mettre des constantes en place dans le .h 
Il faut prevoir de la place pour la suite*/
static void	child(t_cmd_line *cmd, char **environ)
{
	char	*path;

	if (cmd->cmd_step != 0)
	{
		if (dup2(cmd->old_fd[0], STDIN_FILENO) == -1)
		{
			perror("dup2 failed");
			return ;
		}
		close(cmd->old_fd[0]);
		close(cmd->old_fd[1]);
	}
	if (cmd->cmd_step != cmd->nb_simple_cmd - 1)
	{
		close(cmd->new_fd[0]);
		if (dup2(cmd->new_fd[1], STDOUT_FILENO) == -1)
		{
			perror("dup2 failed");
			return ;
		}
		close(cmd->new_fd[1]);
	}
	path = get_path(cmd->tab_path, cmd->tab_cmd[cmd->cmd_step].tab_args[0]);
	if (execve(path, cmd->tab_cmd[cmd->cmd_step].tab_args, environ) == -1)
	{
		perror("execve failed");
		return ;
	}
}

/******************************************************************************
Function manage the parent + execution of the command
******************************************************************************/
static void	parent(t_cmd_line *cmd)
{
	if (cmd->cmd_step != 0)
	{
		close(cmd->old_fd[0]);
		close(cmd->old_fd[1]);
	}
	if (cmd->cmd_step != cmd->nb_simple_cmd - 1)
	{
		cmd->old_fd[0] = cmd->new_fd[0];
		cmd->old_fd[1] = cmd->new_fd[1];
	}
}

/******************************************************************************
Function manage the mutiple pipe command
Return : 
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
				return (1);
		}
		pid = fork();
		if (pid == -1)
		{
			perror("Fork failed");
			return (1);
		}
		else if (pid == 0)
			child(cmd, environ);
		else
			parent(cmd);
		cmd->cmd_step++;
	}
	if (cmd->cmd_step != 0)
	{
		close(cmd->old_fd[0]);
		close(cmd->old_fd[1]);
	}
	cmd->cmd_step = 0;
	while (cmd->cmd_step < cmd->nb_simple_cmd)
	{
		waitpid(pid, NULL, 0);
		cmd->cmd_step++;
	}
	printf("Le processus parent a temine.\n");
	return (0);
}
