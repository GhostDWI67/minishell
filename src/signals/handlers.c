/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpalisse <mpalisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 11:53:53 by mpalisse          #+#    #+#             */
/*   Updated: 2025/05/25 13:28:11 by mpalisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	sigint_handler(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
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
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		g_signal = SIGINT;
	}
	else if (sig == SIGQUIT)
	{
		printf("Quit\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		g_signal = SIGQUIT;
	}
}

void	sig_heredoc(int sig)
{
	if (sig == SIGINT)
	{
		close(STDIN_FILENO);
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		g_signal = SIGINT;
	}
}
