/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwianni <dwianni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 11:47:14 by dwianni           #+#    #+#             */
/*   Updated: 2025/06/23 13:49:00 by dwianni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/******************************************************************************
Function test if all the simple command are executable
Return : 0 if OK else NOK (nb functions doesn't exist)
******************************************************************************/
void	msg_write(t_cmd_line *cmd, int i)
{
	ft_putstr_fd("Command '", 2);
	ft_putstr_fd(cmd->tab_cmd[i].tab_args[0], 2);
	ft_putstr_fd("' not found\n", 2);
}

static int	is_exec_able_int(t_cmd_line *cmd, int i, char *path)
{
	if (cmd->tab_cmd[i].tab_args == NULL)
	{
		token_clear(&cmd->token);
		return (cmd->exit_code = 0, cmd->exit_code);
	}
	if (cmd->tab_cmd[i].tab_args[0] == NULL)
		return (cmd->exit_code = ERN_NOTEXEC, cmd->exit_code);
	if (cmd->tab_cmd[i].tab_args[0] != NULL
		&& is_built_in(cmd->tab_cmd[i].tab_args) == 0)
		path = get_path(cmd->tab_path, cmd->tab_cmd[i].tab_args[0], cmd);
	if (path == NULL && cmd->err_nb == ERN_ISDIR)
		return (ERN_ISDIR);
	if (path == NULL && cmd->err_nb == ERN_NOTFD)
		return (ERN_NOTFD);
	if ((path == NULL && cmd->tab_cmd[i].tab_args[0] != NULL \
		&& is_built_in(cmd->tab_cmd[i].tab_args) == 0) \
		|| cmd->tab_cmd[i].tab_args[0][0] == 0)
	{
		if (path != NULL)
			free(path);
		msg_write(cmd, i);
		return (cmd->exit_code = ERN_NOTEXEC, cmd->exit_code);
	}
	return (0);
}

int	is_exec_able(t_cmd_line *cmd, int i)
{
	char	*path;

	path = NULL;
	return (is_exec_able_int(cmd, i, path));
}
