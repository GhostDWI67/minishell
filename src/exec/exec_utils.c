/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwianni <dwianni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 11:47:14 by dwianni           #+#    #+#             */
/*   Updated: 2025/05/31 18:45:29 by dwianni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
	int	i;

	cmd->tab_fd = malloc(sizeof(int) * (cmd->nb_simple_cmd - 1) * 2);
	if (cmd->tab_fd == NULL)
		cmd->exit_code = msg_inf(ERM_MALLOC, ERN_MALLOC);
	i = 0;
	while (i < cmd->nb_simple_cmd - 1)
	{
		if (cmd->tab_fd != NULL)
			if (pipe(cmd->tab_fd + 2 * i) == -1)
				cmd->exit_code = msg_error(ERM_PIPE, ERN_PIPE);
		i++;
	}
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
		if (cmd->tab_fd != NULL)
			close(cmd->tab_fd[i]);
		i++;
	}
}

/******************************************************************************
Function test if all the simple command are executable
Return : 0 if OK else NOK (nb functions doesn't exist)
******************************************************************************/
static void	msg_write(t_cmd_line *cmd, int i)
{
	ft_putstr_fd("Command '", 2);
	ft_putstr_fd(cmd->tab_cmd[i].tab_args[0], 2);
	ft_putstr_fd("' not found\n", 2);
}

int	is_exec_able(t_cmd_line *cmd, int i)
{
	char	*path;

	path = NULL;
	// if (cmd->tab_cmd[i].tab_args[0] == NULL)
	// 	return (cmd->exit_code = ERN_NOTEXEC, cmd->exit_code);
	if (cmd->tab_cmd[i].tab_args == NULL)
	{
		ft_putstr_fd("POINT TOTO\n", 2);//
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
