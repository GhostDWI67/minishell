/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwianni <dwianni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 13:00:02 by mpalisse          #+#    #+#             */
/*   Updated: 2025/07/14 12:36:53 by dwianni          ###   ########.fr       */
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
	//signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, &sig_exec);
	//signal(SIGQUIT, SIG_IGN);
	//printf("\nACTIVATION SIG EXEC\n");
}

/*
void	setup_sigs_handler(void)
{
	struct sigaction sa;

	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_sigaction = sigint_handler;
	sa.sa_flags = SA_SIGINFO;
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
}

void	setup_sigs_exec(void)
{
	struct sigaction sa;

	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_sigaction = sig_exec;
	sa.sa_flags = SA_SIGINFO;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
	//signal(SIGQUIT,SIG_IGN);
}
*/

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

void	setup_sigs_dfl(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	setup_sigs_ign(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}
