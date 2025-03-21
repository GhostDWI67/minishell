/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwianni <dwianni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 23:25:48 by admin             #+#    #+#             */
/*   Updated: 2025/03/16 17:13:19 by dwianni          ###   ########.fr       */
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
	while (token != NULL)
	{
		if (((char *)token->content)[0] == '>' ||
			((char *)token->content)[0] == '>' ||
			(((char *)token->content)[0] == '>' &&
			((char *)token->content)[1] == '>')
			|| (((char *)token->content)[0] == '<'
			&& ((char *)token->content)[1] == '<'))
			ft_lstadd_back(&res.redirection, ft_lstnew(token->content));
		else if (((char *)token->content)[0] == '|')
			res.pipe = 1;
		else
			ft_lstadd_back(&res.args, ft_lstnew(token->content));
		token = token->next;
	}
	return (res);
}

/******************************************************************************
Transform a list into a tab of string
Return : pointer to a tab
******************************************************************************/
char	**args_to_tab(t_list *args)
{
	char	**res;
	t_list	*tmp;
	int		i;

	tmp = args;
	res = (char **)malloc(sizeof(char *) * (ft_lstsize(tmp)+ 1));
	if (res == NULL)
		return (NULL);
	tmp = args;
	i = 0;
	while (tmp != NULL)
	{
		res[i] = tmp-> content;
		i++;
		tmp = tmp->next;
	}
	res[i] = NULL;
	return (res);
}
