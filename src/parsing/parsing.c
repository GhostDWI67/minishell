/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpalisse <mpalisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 23:25:48 by admin             #+#    #+#             */
/*   Updated: 2025/05/10 18:09:21 by mpalisse         ###   ########.fr       */
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
Additionnal function of parsing
Sort the token in the ARG list and redirection list
******************************************************************************/
static void	parsing_sort(t_cmd_line *cmd, int i, char *tmp)
{
	t_token *temp;

	temp = cmd->token;
	while (cmd->token != NULL)
	{
		if ((cmd->token->content)[0] == '>' ||
			(cmd->token->content)[0] == '<')
		{
			tmp = ft_strjoin(cmd->token->content,
					s_expand(cmd->token->next->content, cmd->env, cmd));
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

/******************************************************************************
Transform a list into a tab of string
Return : pointer to a tab
******************************************************************************/
static char	**args_to_tab(t_list *args, t_list *env, t_cmd_line *cmd)
{
	char	**res;
	t_list	*tmp;
	int		lst_size;
	int		i;

	tmp = args;
	lst_size = ft_lstsize(tmp);
	res = (char **)malloc(sizeof(char *) * (lst_size + 1));
	if (res == NULL || lst_size == 0)
	{
		return (NULL);
	}
	tmp = args;
	i = 0;
	while (tmp != NULL)
	{
		res[i] = s_expand((char *)tmp-> content, env, cmd);
		i++;
		tmp = tmp->next;
		res[i] = NULL;
	}
	return (res);
}

/******************************************************************************
Transform the list ARG into a tab of string for ALL the simple command
******************************************************************************/
void	cmd_arg_to_tab(t_cmd_line *cmd)
{
	int	i;

	i = 0;
	while (i < cmd->nb_simple_cmd)
	{
		cmd->tab_cmd[i].tab_args = args_to_tab(cmd->tab_cmd[i].args,
				cmd->env, cmd);
		i++;
	}
}
