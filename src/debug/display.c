/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpalisse <mpalisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 19:52:05 by admin             #+#    #+#             */
/*   Updated: 2025/05/07 11:26:20 by mpalisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/******************************************************************************
Display the content of simple command ARGS and REDIRECTION
******************************************************************************/
void	display_simple_cmd(t_cmd_line *cmd)
{
	int		i;
	t_list	*tmp;

	i = 0;
	while (i < cmd->nb_simple_cmd)
	{
		tmp = cmd->tab_cmd[i].args;
		printf("Commande %d ARGUMENTS ----\n", i);
		while (tmp != NULL)
		{
			printf("arg : %s\n", (char *)tmp->content);
			tmp = tmp->next;
		}
		tmp = cmd->tab_cmd[i].redirection;
		printf("Commande %d REDIRECTIONS ----\n", i);
		while (tmp != NULL)
		{
			printf("redir : %s\n", (char *)tmp->content);
			tmp = tmp->next;
		}
		i++;
	}
	printf("FIN***********************************\n");
}

/******************************************************************************
Display token
******************************************************************************/
void	display_token(t_cmd_line *cmd)
{
	t_token	*tmp_token;

	tmp_token = cmd->token;
	while (tmp_token != NULL)
	{
		printf("Token : %s // %d\n", tmp_token->content, tmp_token->type);
		tmp_token = tmp_token->next;
	}
}
