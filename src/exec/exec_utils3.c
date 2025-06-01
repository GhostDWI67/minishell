/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwianni <dwianni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 11:47:14 by dwianni           #+#    #+#             */
/*   Updated: 2025/06/01 14:09:22 by dwianni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/******************************************************************************
Function closing all the fd : redirection, pipe, heredoc for all the cmd line
and for each simple command line
******************************************************************************/
void	close_all_fd(t_cmd_line *cmd)
{
	int	i;

	close(cmd->fd_saved_stdin);
	close(cmd->fd_saved_stdout);
	close_tab_pipe(cmd);
	i = 0;
	while (i < cmd->nb_simple_cmd)
	{
		close(cmd->tab_cmd[i].hd_pipe[0]);
		close(cmd->tab_cmd[i].hd_pipe[1]);
		if (cmd->tab_cmd[i].fd_infile > 2)
			close(cmd->tab_cmd[i].fd_infile);
		if (cmd->tab_cmd[i].fd_outfile > 2)
			close(cmd->tab_cmd[i].fd_outfile);
		i++;
	}
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
