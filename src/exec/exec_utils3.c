/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwianni <dwianni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 11:47:14 by dwianni           #+#    #+#             */
/*   Updated: 2025/06/23 13:35:48 by dwianni          ###   ########.fr       */
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
	i = 0;
	while (i < cmd->nb_simple_cmd)
	{
		if (cmd->tab_cmd[i].hd_test != 0)
		{
			close(cmd->tab_cmd[i].hd_pipe[0]);
			close(cmd->tab_cmd[i].hd_pipe[1]);
		}
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
