/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwianni <dwianni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 13:00:02 by mpalisse          #+#    #+#             */
/*   Updated: 2025/07/04 18:32:11 by dwianni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	setup_sigs_handler(void)
{
	signal(SIGINT, &sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	setup_sigs_exec(void)
{
	//signal(SIGINT, &sig_exec);
	//signal(SIGQUIT, &sig_exec);
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	setup_sigs_hd(void)
{
	signal(SIGINT, &sig_heredoc);
	signal(SIGQUIT, SIG_IGN);
}

void	sig_exit_status(t_cmd_line *cmd)
{
	if (g_signal == SIGINT)
	{
		cmd->exit_code = 130;
		g_signal = 0;
	}
	if (g_signal == SIGQUIT)
	{
		cmd->exit_code = 131;
		g_signal = 0;
	}
}
