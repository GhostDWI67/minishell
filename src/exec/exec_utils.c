/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwianni <dwianni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 11:47:14 by dwianni           #+#    #+#             */
/*   Updated: 2025/03/30 19:36:05 by dwianni          ###   ########.fr       */
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

	if (access(fexec, X_OK) == 0)
		return (fexec);
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
Function closing fd
******************************************************************************/
void	close_fd(int *fd, int nb_fd)
{
	int	i;

	i = 0;
	while (i < nb_fd)
	{
		close(fd[i]);
		i++;
	}
}

/******************************************************************************
Function generating pipes
******************************************************************************/
void	build_pipe(t_cmd_line *cmd)
{
	cmd->tab_fd = malloc(sizeof(int) * (cmd->nb_simple_cmd - 1) * 2);
	if (cmd->tab_fd == NULL)
		msg_error(ERM_MALLOC, ERN_MALLOC);
	cmd->cmd_step = 0;
	while (cmd->cmd_step < cmd->nb_simple_cmd - 1)
	{
		if (pipe(cmd->tab_fd + 2 * cmd->cmd_step) == -1)
			msg_error(ERM_PIPE, ERN_PIPE);
		cmd->cmd_step++;
	}
	cmd->cmd_step = 0;
}

/******************************************************************************
Function generating pipes
******************************************************************************/
void	close_tab_pipe(t_cmd_line *cmd)
{
	int	i;

	i = 0;
	while (i < (cmd->nb_simple_cmd - 1) * 2)
	{
		close(cmd->tab_fd[i]);
		i++;
	}
}
