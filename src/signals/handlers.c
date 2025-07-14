/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwianni <dwianni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 11:53:53 by mpalisse          #+#    #+#             */
/*   Updated: 2025/07/14 13:40:25 by dwianni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	sigint_handler(int sig)
{
	if (sig == SIGINT)
	{
		ft_putstr_fd("\n", 2);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		g_signal = SIGINT;
	}
}

void	sig_exec(int sig)
{
	if (sig == SIGINT)
	{
		g_signal = SIGINT;
	}
	else if (sig == SIGQUIT)
	{
		g_signal = SIGQUIT;
	}
}

void	sig_heredoc(int sig)
{
	if (sig == SIGINT)
	{
		close(STDIN_FILENO);
		g_signal = SIGINT;
	}
}

void	signal_msg(void)
{
	if (g_signal == SIGINT)
	{
		ft_putstr_fd("\n", 2);
		rl_replace_line("", 0);
		rl_on_new_line();
	}
	else if (g_signal == SIGQUIT)
	{
		ft_putstr_fd("Quit\n", 2);
		rl_replace_line("", 0);
		rl_on_new_line();
	}
}
