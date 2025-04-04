/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwianni <dwianni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 10:35:37 by dwianni           #+#    #+#             */
/*   Updated: 2025/04/04 14:55:30 by dwianni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
ft_putstr_fd("toto REDIR IN-------\n",2);
ft_putstr_fd("toto INFILE\n",2);
ft_putnbr_fd(cmd->tab_cmd[cmd->cmd_step].fd_infile, 2);
ft_putstr_fd("\n",2);
ft_putstr_fd("toto OUTFILE\n",2);
ft_putnbr_fd(cmd->tab_cmd[cmd->cmd_step].fd_outfile, 2);
ft_putstr_fd("\n",2);
*/

/******************************************************************************
Function manage the child redirection + execution of the command
******************************************************************************/
static void	child_redir_mgt_in(t_cmd_line *cmd)
{
	if (cmd->tab_cmd[cmd->cmd_step].hd_bool != 1)
	{
		if (cmd->cmd_step == 0)
		{
			if (dup2(cmd->tab_cmd[cmd->cmd_step].fd_infile, STDIN_FILENO) == -1)
				msg_error(ERM_DUP2, ERN_DUP2);
		}
		else if (cmd->cmd_step > 0 && cmd->tab_cmd[cmd->cmd_step].fd_infile > 0)
		{
			if (dup2(cmd->tab_cmd[cmd->cmd_step].fd_infile, STDIN_FILENO) == -1)
				msg_error(ERM_DUP2, ERN_DUP2);
			close(cmd->tab_cmd[cmd->cmd_step].fd_infile);
		}
		else if (cmd->cmd_step > 0)
		{
			if (dup2(cmd->tab_fd[2 * cmd->cmd_step - 2], STDIN_FILENO) == -1)
				msg_error(ERM_DUP2, ERN_DUP2);
		}
	}
}

static void	child_redir_mgt_out(t_cmd_line *cmd)
{
	if (cmd->tab_cmd[cmd->cmd_step].fd_outfile > 1)
	{
		if (dup2(cmd->tab_cmd[cmd->cmd_step].fd_outfile, STDOUT_FILENO) == -1)
			msg_error(ERM_DUP2, ERN_DUP2);
		close(cmd->tab_cmd[cmd->cmd_step].fd_outfile);
	}
	else if (cmd->cmd_step < cmd->nb_simple_cmd - 1)
	{
		if (dup2(cmd->tab_fd[2 * cmd->cmd_step + 1], STDOUT_FILENO) == -1)
		{
			msg_error(ERM_DUP2, ERN_DUP2);
		}
	}
}

int	child(t_cmd_line *cmd, char **environ)
{
	char	*path;

	if (cmd->tab_cmd[cmd->cmd_step].redir_test == 1)
	{
		child_redir_mgt_in(cmd);
		child_redir_mgt_out(cmd);
		close_tab_pipe(cmd);
		if (cmd->tab_cmd[cmd->cmd_step].tab_args[0] != NULL)
		{
			path = get_path(cmd->tab_path, cmd->tab_cmd[cmd->cmd_step].tab_args[0]);
			if (execve(path, cmd->tab_cmd[cmd->cmd_step].tab_args, environ) == -1)
				msg_error(ERM_EXECVE, ERN_EXECVE);
		}
		else
			exit(-1);
	}
	return (0);
}
