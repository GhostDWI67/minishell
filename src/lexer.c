/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 23:25:48 by admin             #+#    #+#             */
/*   Updated: 2025/03/11 22:48:24 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/******************************************************************************
Sort the token list into a command structure
******************************************************************************/
t_command	lexer(t_list *token)
{
	t_command	res;

	res.args = NULL;
	res.redirection = NULL;
	res.pipe = 0;
	while(token != NULL)
	{
		if (((char *)token->content)[0] == '>' || ((char *)token->content)[0] == '>'
			|| (((char *)token->content)[0] == '>' &&
			((char *)token->content)[1] == '>') || (((char *)token->content)[0] == '<'
			&& ((char *)token->content)[1] == '<'))
			ft_lstadd_back(&res.redirection, ft_lstnew(token->content));
		else if (((char *)token->content)[0] == '|')
			res.pipe = 1;
		else
			ft_lstadd_back(&res.args, ft_lstnew(token->content));
		token = token->next;
	}
	return(res);
}

char	**tab_args(t_list args)
{
	char	**res;
	t_list	temp;

	temp = args;
		
}