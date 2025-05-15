/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpalisse <mpalisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 13:00:02 by mpalisse          #+#    #+#             */
/*   Updated: 2025/05/13 12:37:54 by mpalisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/******************************************************************************
redisplay une ligne quand le signal SIGINT (ctrl + c) est recu 
Return void;
******************************************************************************/
static void	sigint_handler(int sig)
{
	(void)sig;
	printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	if (g_signal == 0)
		rl_redisplay();
}

/******************************************************************************
init les signaux et les fonctions a lancer en fonction du signal recu
Return void;
******************************************************************************/
void	signals_handler(void)
{
	signal(SIGINT, &sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}