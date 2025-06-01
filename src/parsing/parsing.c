/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwianni <dwianni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 23:25:48 by admin             #+#    #+#             */
/*   Updated: 2025/06/01 15:17:14 by dwianni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/******************************************************************************
Init all the parameter of the parsing function
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

/******************************************************************************
Parsing sort manage the HEREDOC and redirection
******************************************************************************/
static void	parsing_sort_redir(t_cmd_line *cmd, int i, char *tmp)
{
	char	*tmp_exp;

	if ((cmd->token->content)[0] == '<' && (cmd->token->content)[1] == '<')
		tmp = ft_strjoin(cmd->token->content, cmd->token->next->content);
	else
	{
		tmp_exp = s_expand(cmd->token->next->content, cmd->env, cmd);
		tmp = ft_strjoin(cmd->token->content, tmp_exp);
		free(tmp_exp);
	}
	if (tmp != NULL)
	{
		ft_lstadd_back(&cmd->tab_cmd[i].redirection, ft_lstnew(tmp));
		cmd->token = cmd->token->next;
	}
	else
		cmd->exit_code = msg_inf(ERM_MALLOC, ERN_MALLOC);
}

/******************************************************************************
Additionnal function of parsing
Sort the token in the ARG list and redirection list
******************************************************************************/
static void	parsing_sort(t_cmd_line *cmd, int i, char *tmp)
{
	t_token	*temp;

	temp = cmd->token;
	while (cmd->token != NULL)
	{
		if ((cmd->token->content)[0] == '>' ||
			(cmd->token->content)[0] == '<')
		{
			parsing_sort_redir(cmd, i, tmp);
		}
		else if ((cmd->token->content)[0] == '|')
			i++;
		else if ((cmd->token->content)[0] != '>' &&
			(cmd->token->content)[0] != '<')
			ft_lstadd_back(&cmd->tab_cmd[i].args,
				ft_lstnew(ft_strdup(cmd->token->content)));
		cmd->token = cmd->token->next;
	}
	cmd->token = temp;
}

/******************************************************************************
Sort the token list into a command structure
Fill the redirection list of a simple command
fill the ARG list of a simple command
******************************************************************************/
void	parsing(t_cmd_line *cmd)
{
	char	*tmp;
	int		i;

	parsing_init(cmd);
	i = 0;
	tmp = NULL;
	parsing_sort(cmd, i, tmp);
}
