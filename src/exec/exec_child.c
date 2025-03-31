/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwianni <dwianni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 10:35:37 by dwianni           #+#    #+#             */
/*   Updated: 2025/03/31 17:40:10 by dwianni          ###   ########.fr       */
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
static void	child_redir_mgt_in(t_cmd_line *cmd, int i)
{
	if (cmd->tab_cmd[i].hd_bool != 1)
	{
		if (i == 0)
		{
			if (dup2(cmd->tab_cmd[i].fd_infile, STDIN_FILENO) == -1)
				msg_error(ERM_DUP2, ERN_DUP2);
		}
		else if (i > 0 && cmd->tab_cmd[i].fd_infile > 0)
		{
			if (dup2(cmd->tab_cmd[i].fd_infile, STDIN_FILENO) == -1)
				msg_error(ERM_DUP2, ERN_DUP2);
			close(cmd->tab_cmd[i].fd_infile);
		}
		else if (i > 0)
		{
			if (dup2(cmd->tab_fd[2 * i - 2], STDIN_FILENO) == -1)
				msg_error(ERM_DUP2, ERN_DUP2);
		}
	}
}

static void	child_redir_mgt_out(t_cmd_line *cmd, int i)
{
	if (cmd->tab_cmd[i].fd_outfile > 1)
	{
		if (dup2(cmd->tab_cmd[i].fd_outfile, STDOUT_FILENO) == -1)
			msg_error(ERM_DUP2, ERN_DUP2);
		close(cmd->tab_cmd[i].fd_outfile);
	}
	else if (i < cmd->nb_simple_cmd - 1)
	{
		if (dup2(cmd->tab_fd[2 * i + 1], STDOUT_FILENO) == -1)
		{
			msg_error(ERM_DUP2, ERN_DUP2);
		}
	}
}

int	child(t_cmd_line *cmd, char **environ, int i)
{
	char	*path;

	if (cmd->tab_cmd[i].redir_test == 1)
	{
		//ft_putstr_fd("toto IN CHILD ------***************\n",2);
		//ft_putnbr_fd(getpid(), 2);
		//ft_putstr_fd("\n",2);
		child_redir_mgt_in(cmd, i);
		child_redir_mgt_out(cmd, i);
		close_tab_pipe(cmd);
		if (cmd->tab_cmd[i].tab_args[0] != NULL)
		{
			path = get_path(cmd->tab_path, cmd->tab_cmd[i].tab_args[0]);
			if (execve(path, cmd->tab_cmd[i].tab_args, environ) == -1)
				msg_error(ERM_EXECVE, ERN_EXECVE);
		}
	}
	return (0);
}
