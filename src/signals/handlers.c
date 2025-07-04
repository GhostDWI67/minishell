/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwianni <dwianni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 11:53:53 by mpalisse          #+#    #+#             */
/*   Updated: 2025/07/04 18:15:56 by dwianni          ###   ########.fr       */
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
