/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwianni <dwianni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 22:39:34 by admin             #+#    #+#             */
/*   Updated: 2025/03/16 11:59:09 by dwianni          ###   ########.fr       */
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
/*static int	sub_pipe(int *fd, char *path, char **exec, char **environ)
{
	int pid;
	
	pid = fork();
	if (pid <0)
		return (2);
	if (pid ==0)
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
		if (execve(path, exec, environ) == -1)
		{
			perror("execve failed");
			return (3);
		}
	}
	return (0);
}
*/
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
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
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
		dup2(fd[0], STDIN_FILENO);
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
