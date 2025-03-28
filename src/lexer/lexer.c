/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwianni <dwianni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 23:25:48 by admin             #+#    #+#             */
/*   Updated: 2025/03/28 10:59:33 by dwianni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/******************************************************************************
Sort the token list into a command structure
******************************************************************************/
t_command	lexer(t_list *token)
{
	t_command	res;
	t_list		*tmp;

	res.args = NULL;
	res.redirection = NULL;
	res.pipe = 0;
	res.infile = NULL;
	res.outfile = NULL;
	res.fd_infile = STDIN_FILENO;
	res.fd_outfile = STDOUT_FILENO;
	tmp = token;
	while (tmp != NULL)
	{
		if (((char *)tmp->content)[0] == '>' ||
			((char *)tmp->content)[0] == '<')
			ft_lstadd_back(&res.redirection, ft_lstnew(tmp->content));
		else if (((char *)tmp->content)[0] == '|')
			res.pipe = 1;
		else
			ft_lstadd_back(&res.args, ft_lstnew(tmp->content));
		tmp = tmp->next;
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
