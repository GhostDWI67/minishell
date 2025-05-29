/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwianni <dwianni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 11:47:14 by dwianni           #+#    #+#             */
/*   Updated: 2025/05/29 18:01:15 by dwianni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
