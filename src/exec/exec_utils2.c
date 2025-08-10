/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwianni <dwianni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 11:47:14 by dwianni           #+#    #+#             */
/*   Updated: 2025/08/10 17:37:11 by dwianni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*get_path_mf(char *fexec, t_cmd_line *cmd, DIR *stream)
{
	if (stream != NULL)
	{
		closedir(stream);
		cmd->exit_code = msg_inf(ERM_ISDIR, ERN_ISDIR);
		cmd->err_nb = ERN_ISDIR;
		return (NULL);
	}
	else if (access(fexec, F_OK) == 0 && access(fexec, X_OK) != 0)
	{
		cmd->exit_code = msg_inf(ERM_PERM, ERN_PERM);
		cmd->err_nb = ERN_PERM;
		return (NULL);
	}
	else if (opendir(fexec) == NULL && access(fexec, F_OK) != 0)
	{
		cmd->exit_code = msg_inf(ERM_NOTFD, ERN_NOTFD);
		cmd->err_nb = ERN_NOTFD;
		return (NULL);
	}
	return (NULL);
}

static char	*get_path_test(char **tab_path, char *fexec, DIR *stream)
{
	char	*path;
	char	*p_to_test;
	int		i;

	i = 0;
	if (ft_strncmp(fexec, "", 2) == 0)
		return (NULL);
	if (stream != NULL)
		return (closedir(stream), NULL);
	while (tab_path[i] != NULL)
	{
		path = ft_strjoin(tab_path[i], "/");
		p_to_test = ft_strjoin(path, fexec);
		if (access(p_to_test, X_OK) == 0)
		{
			return (free(path), p_to_test);
		}
		else
		{
			free(path);
			free(p_to_test);
		}
		i++;
	}
	return (NULL);
}

/******************************************************************************
Get a tab of path
Check if the function is executable with the different path
Return a string : path/fexec
******************************************************************************/
char	*get_path(char **tab_path, char *fexec, t_cmd_line *cmd)
{
	DIR		*stream;

	stream = opendir(fexec);
	if (ft_strncmp(cmd->tab_cmd[cmd->cmd_step].tab_args[0], "./", 2) == 0 || \
		ft_strncmp(cmd->tab_cmd[cmd->cmd_step].tab_args[0], "../", 3) == 0 || \
		ft_strncmp(cmd->tab_cmd[cmd->cmd_step].tab_args[0], "/", 1) == 0)
	{
		if (stream == NULL && access(fexec, X_OK) == 0)
		{
			return (fexec);
		}
		return (get_path_mf(fexec, cmd, stream));
	}
	else if (tab_path != NULL)
	{
		return (get_path_test(tab_path, fexec, stream));
	}
	if (stream == NULL && access(fexec, X_OK) == 0)
	{
		return (fexec);
	}
	return (NULL);
}
