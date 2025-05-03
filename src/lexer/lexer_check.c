/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwianni <dwianni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 11:21:11 by admin             #+#    #+#             */
/*   Updated: 2025/05/03 13:15:09 by dwianni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
			msg_error(ft_strjoin(ERM_TOKEN, tmp->content), ERN_TOKEN);//
			return (1);
		}
	while (tmp != NULL)
	{
		if (tmp->next != NULL)
		{
			if (tmp->type < 5 && tmp->next->type < 5)
			{
				msg_error(ft_strjoin(ERM_TOKEN, tmp->next->content), ERN_TOKEN);
				return (1);
			}
			if (tmp->type == 5 && tmp->next->type == 5)
			{
				msg_error(ft_strjoin(ERM_TOKEN, tmp->next->content), ERN_TOKEN);
				return (1);
			}
		}
		tmp = tmp->next;
	}
	return (0);
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
