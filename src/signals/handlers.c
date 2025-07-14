/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwianni <dwianni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 11:53:53 by mpalisse          #+#    #+#             */
/*   Updated: 2025/07/14 12:51:35 by dwianni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	sigint_handler(int sig)
//void	sigint_handler(int sig, siginfo_t *info, void *context)
{
	//(void)context;
	//(void)info;
	//printf("\nSignal HANDLER %d reçu depuis PID %d\n", sig, info->si_pid);
	if (sig == SIGINT)
	{
		ft_putstr_fd("HANDLER\n", 2);//
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		g_signal = SIGINT;
	}
}

void	sig_exec(int sig)
//void	sig_exec(int sig, siginfo_t *info, void *context)
{
	//(void)context;
	//(void)info;
	//printf("\nSignal EXEC %d reçu depuis PID %d\n", sig, info->si_pid);
	if (sig == SIGINT)
	{
		//ft_putstr_fd("SIGINT\n", 2);
		//rl_replace_line("", 0);
		//rl_on_new_line();
		g_signal = SIGINT;
	}
	else if (sig == SIGQUIT)
	{
		//ft_putstr_fd("SIGQUITQuit\n", 2);
		//rl_replace_line("", 0);
		//rl_on_new_line();
		g_signal = SIGQUIT;
	}
}

void	sig_heredoc(int sig)
{
	if (sig == SIGINT)
	{
		close(STDIN_FILENO);
		ft_putstr_fd("\n", 2);
		rl_replace_line("", 0);
		rl_on_new_line();
		g_signal = SIGINT;
	}
}
