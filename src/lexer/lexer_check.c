/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwianni <dwianni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 11:21:11 by admin             #+#    #+#             */
/*   Updated: 2025/05/24 15:46:42 by dwianni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/******************************************************************************
manage the message of the check_token function
Return : 0 if no pb/OK, other if not OK
******************************************************************************/
static int	check_token_msg(t_token *tmp)
{
	char	*msg;

	while (tmp != NULL)
	{
		
		if (tmp->next != NULL)
		{
			if (tmp->type < 5 && tmp->next->type < 6)
			{
				msg = ft_strjoin(ERM_TOKEN, tmp->next->content);
				msg_inf(msg, ERN_TOKEN);
				free(msg);
				return (ERN_TOKEN);
			}
			if (tmp->type == 5 && tmp->next->type == 5)
			{
				msg = ft_strjoin(ERM_TOKEN, tmp->next->content);
				msg_inf(msg, ERN_TOKEN);
				free(msg);
				return (ERN_TOKEN);
			}
		}
		if (tmp->type < 5 && tmp->next == NULL)
		{
			ft_putstr_fd("CASE 2\n",2);
			return (msg_inf("unexpected token : newline", ERN_TOKEN));
		}
		tmp = tmp->next;
	}
	return (0);
}

/******************************************************************************
Check if no problem with token
Return : 0 if no pb/OK, other if not OK
******************************************************************************/
int	check_token(t_token *token)
{
	t_token	*tmp;

	tmp = token;
	if (tmp->type == 5)
	{
		return (msg_inf("unexpected token : |", ERN_TOKEN)); //ft_strjoin(ERM_TOKEN, tmp->content)
	}
	return (check_token_msg(tmp));
}

/******************************************************************************
Check last token
Return : 0 if last token is not | , 1 if the last is |
******************************************************************************/
int	check_token_last_pipe(t_token *token)
{
	t_token	*tmp;
	int		last;

	last = 0;
	tmp = token;
	while (tmp != NULL)
	{
		last = tmp->type;
		tmp = tmp->next;
	}
	if (last == 5)
		return (1);
	return (0);
}

/******************************************************************************
Return : number of simple command
******************************************************************************/
int	check_token_nb_cmd(t_token *token)
{
	t_token	*tmp;
	int		nb;

	nb = 0;
	tmp = token;
	while (tmp != NULL)
	{
		if (tmp->type == 5)
			nb++;
		tmp = tmp->next;
	}
	nb ++;
	return (nb);
}
