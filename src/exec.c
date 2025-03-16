/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwianni <dwianni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 22:39:34 by admin             #+#    #+#             */
/*   Updated: 2025/03/16 15:27:14 by dwianni          ###   ########.fr       */
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

******************************************************************************/
int	f_pipe(t_cmd_line *cmd, char **environ)
{
	int		fd[2];
	int		i;
	pid_t	pid;

	if (pipe(fd) == -1)
		return (1);
	i = 0;
	while(i < cmd->nb_simple_cmd)
	{
		pid = fork();
		if (pid == -1)
		{
			perror("Fork failed");
			return (1);
		}
		else if (pid == 0)
		{
			printf("Processus fils %d cree\n", i);
			if (i != 0)
			{
				if (dup2(fd[0], STDIN_FILENO) == -1)
				{
					perror("dup2 failed");
					return(2);
				}	
			}
			if (i != cmd->nb_simple_cmd - 1)
			{
				if (dup2(fd[1], STDOUT_FILENO) == -1)
				{
					perror("dup2 failed");
					return(2);
				}
			}
			close(fd[0]);
			close(fd[1]);
			if (execve(get_path(cmd->tab_path, cmd->tab_cmd[i].tab_args[0]),
				cmd->tab_cmd[i].tab_args, environ) == -1)
			{
				perror("execve failed");
				return (3);
			}	
			exit(0);
		}
		else
		{
		}
		i++;
	}
	i = 0;
	while (i < cmd->nb_simple_cmd)
	{
		waitpid(pid, NULL, 0);
		i++;
	}
	printf("Le processus parent a temine.\n");
	return 0;
}

/*
int	f_pipe(char *path1, char **exec1, char *path2, char **exec2, char **environ)
{
	int	fd[2];
	int	pid1;
	int	pid2;

	if (pipe(fd) == -1)
		return (1);
	pid1 = fork();
	if (pid1 < 0)
		return (2);
	if (pid1 == 0)
	{
		//printf("dans PID1\n");
		if (dup2(fd[1], STDOUT_FILENO) == -1)
		{
			perror("dup2 failed");
			return(3);
		}
		close(fd[0]);
		close(fd[1]);
		printf("dans PID1 %d\n", STDOUT_FILENO);
		if (execve(path1, exec1, environ) == -1)
		{
			perror("execve failed");
			return (3);
		}
	}
	pid2 = fork();
	if (pid2 < 0)
		return (2);
	if (pid2 == 0)
	{
		//printf("dans PID2 toto\n");
		if (dup2(fd[0], STDIN_FILENO) == -1)
		{
			perror("dup2 failed");
			return(3);
		}
		close(fd[0]);
		close(fd[1]);
		if (execve(path2, exec2, environ) == -1)
		{
			perror("execve failed");
			return (3);
		}
	}
	close(fd[0]);
	close(fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	return (0);
}
*/