/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwianni <dwianni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 23:25:48 by admin             #+#    #+#             */
/*   Updated: 2025/04/27 18:28:57 by dwianni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/******************************************************************************
Sort the token list into a command structure
******************************************************************************/
static void	parsing_init(t_cmd_line *cmd)
{
	int	i;

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
}

void	parsing(t_cmd_line *cmd)
{
	char	*tmp;
	int		i;

	parsing_init(cmd);
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
char	**args_to_tab(t_list *args, t_list *env)
{
	char	**res;
	t_list	*tmp;
	int		lst_size;
	int		i;

	tmp = args;
	lst_size = ft_lstsize(tmp);
	if (lst_size != 0)
		res = (char **)malloc(sizeof(char *) * (lst_size + 1));
	else
		res = (char **)malloc(sizeof(char *) * 3);
	if (res == NULL)
		return (NULL);
	tmp = args;
	if (lst_size != 0)
	{
		i = 0;
		while (tmp != NULL)
		{
			res[i] = s_expand((char *)tmp-> content, env);
			i++;
			tmp = tmp->next;
			res[i] = NULL;
		}
	}
	else
	{
		res[0] = ft_strdup("echo");
		res[1] = ft_strdup("-n");
		res[2] = NULL;
	}
	return (res);
}
