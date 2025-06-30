/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwianni <dwianni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 11:15:12 by mpalisse          #+#    #+#             */
/*   Updated: 2025/06/30 14:09:12 by dwianni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/******************************************************************************
Init the cmd structure
******************************************************************************/
void	init_cmd(t_cmd_line *cmd)
{
	cmd->input = NULL;
	cmd->token = NULL;
	cmd->tab_env = NULL;
	cmd->env = NULL;
	cmd->nb_simple_cmd = 0;
	cmd->tab_cmd = NULL;
	cmd->tab_path = NULL;
	cmd->tab_pid = NULL;
	cmd->cmd_step = 0;
	cmd->fd_saved_stdin = 0;
	cmd->fd_saved_stdout = 0;
	cmd->err_nb = 0;
	cmd->exit_code = 0;
	g_signal = 0;
	setup_sigs_handler();
}

/******************************************************************************
Init the command structure
******************************************************************************/
void	init_tab_cmd(t_command *tab_cmd)
{
	tab_cmd->args = NULL;
	tab_cmd->redirection = NULL;
	tab_cmd->tab_args = NULL;
	tab_cmd->fd_infile = 0;
	tab_cmd->fd_outfile = 0;
	tab_cmd->infile = NULL;
	tab_cmd->outfile = NULL;
	tab_cmd->hd_pipe[0] = 0;
	tab_cmd->hd_pipe[1] = 0;
	tab_cmd->hd_input = NULL;
	tab_cmd->redir_test = 0;
}
	