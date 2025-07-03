/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpalisse <mpalisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 13:00:02 by mpalisse          #+#    #+#             */
/*   Updated: 2025/07/03 15:07:31 by mpalisse         ###   ########.fr       */
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
	signal(SIGINT, &sig_exec);
	signal(SIGQUIT, &sig_exec);
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
