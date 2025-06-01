/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwianni <dwianni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 15:58:08 by dwianni           #+#    #+#             */
/*   Updated: 2025/06/01 14:03:17 by dwianni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/******************************************************************************
Create a new token
******************************************************************************/
t_token	*token_new(char *content, int type)
{
	t_token	*res;

	res = (t_token *)malloc(sizeof(t_token));
	if (res == NULL)
		return (msg_inf(ERM_MALLOC, ERN_MALLOC), NULL);
	res->content = content;
	res->type = type;
	res->next = NULL;
	return (res);
}

/******************************************************************************
Point on the last element of the token list
******************************************************************************/
t_token	*token_last(t_token *lst)
{
	while (lst != NULL && lst->next != NULL)
		lst = lst->next;
	return (lst);
}

/******************************************************************************
Add back in the token list 
******************************************************************************/
void	token_add_back(t_token **lst, t_token *new)
{
	if (lst == NULL || new == NULL)
		return ;
	if (*lst != NULL)
		token_last(*lst)->next = new;
	else
		*lst = new;
}

/******************************************************************************
Free a token list
******************************************************************************/
void	token_clear(t_token **lst)
{
	t_token	*next;

	if (*lst == NULL)
		return ;
	while (*lst != NULL)
	{
		next = (*lst)->next;
		free((*lst)->content);
		free(*lst);
		*lst = next;
	}
	*lst = NULL;
}
