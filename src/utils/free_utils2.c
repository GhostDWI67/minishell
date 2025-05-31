/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwianni <dwianni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 11:35:21 by mpalisse          #+#    #+#             */
/*   Updated: 2025/05/31 17:10:45 by dwianni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/******************************************************************************
Free the cmd structure and clear history
Return 0
******************************************************************************/
static int	free_cmd(t_cmd_line *cmd)
{
	if (cmd->input != NULL)
		free(cmd->input);
	if (cmd->env)
	{
		ft_lstclear(&cmd->env, free);
		free(cmd->env);
	}
	free(cmd->tab_env);
	if (cmd)
		free(cmd);
	rl_clear_history();
	return (0);
}

/******************************************************************************
Free the cmd structure and clear history
In "ctrl + d" case
******************************************************************************/
void	free_exit_ctrld(t_cmd_line *cmd, bool err, int exit_status)
{
	if (err == false)
		ft_putstr_fd("exit\n", 1);
	free_cmd(cmd);
	exit(exit_status);
}

/******************************************************************************
Free the cmd structure and manage fd's
In the main programme after each loop
******************************************************************************/
static void	close_fds(t_cmd_line *cmd, int i)
{
	ft_close(cmd->tab_cmd[i].fd_infile);
	ft_close(cmd->tab_cmd[i].fd_outfile);
	ft_close(cmd->tab_cmd[i].hd_pipe[0]);
	ft_close(cmd->tab_cmd[i].hd_pipe[1]);
}

void	main_free_mgt(t_cmd_line *cmd)
{
	int	i;

	i = 0;
	while (i < cmd->nb_simple_cmd)
	{
		if (cmd->tab_cmd != NULL)
			close_fds(cmd, i);
		i++;
	}
	if (dup2(cmd->fd_saved_stdout, STDOUT_FILENO) == -1)
		cmd->exit_code = msg_error(ERM_STD, ERN_STD);
	else
		close(cmd->fd_saved_stdout);
	if (dup2(cmd->fd_saved_stdin, STDIN_FILENO) == -1)
		cmd->exit_code = msg_error(ERM_STD, ERN_STD);
	else
		close(cmd->fd_saved_stdin);
	if (cmd->input != NULL)
	{
		free_cmd_line(cmd);
		cmd = NULL;
	}
}
