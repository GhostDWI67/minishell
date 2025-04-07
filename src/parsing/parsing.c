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
void	parsing(t_cmd_line *cmd)
{
	char		*tmp;
	int			i;

	i = 0;
	while (i < cmd->nb_simple_cmd)
	{
		cmd->tab_cmd[i].args = NULL;
		cmd->tab_cmd[i].redirection = NULL;
		cmd->tab_cmd[i].infile = NULL;
		cmd->tab_cmd[i].outfile = NULL;
		cmd->tab_cmd[i].fd_infile = STDIN_FILENO;
		cmd->tab_cmd[i].fd_outfile = STDOUT_FILENO;
		i++;
	}
	i = 0;
	while (cmd->token != NULL)
	{
		if ((cmd->token->content)[0] == '>' ||
			(cmd->token->content)[0] == '<')
		{
			tmp = ft_strjoin(cmd->token->content, cmd->token->next->content);
			if (tmp != NULL)
			{
				ft_lstadd_back(&cmd->tab_cmd[i].redirection, ft_lstnew(tmp));
				cmd->token = cmd->token->next;
			}
		}
		else if ((cmd->token->content)[0] == '|')
			i++;
		else if ((cmd->token->content)[0] != '>' &&
			(cmd->token->content)[0] != '<')
			ft_lstadd_back(&cmd->tab_cmd[i].args,
				ft_lstnew(cmd->token->content));
		cmd->token = cmd->token->next;
	}
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
