/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwianni <dwianni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 23:15:15 by admin             #+#    #+#             */
/*   Updated: 2025/06/01 15:16:09 by dwianni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/******************************************************************************
Skip "" and ''
Return the value of the position + 1 of the end of quote
******************************************************************************/
int	skip_quote(int i, char *s)
{
	if (s[i] == '"')
	{
		i++;
		while (s[i] != '"' && s[i] != 0)
		{
			i++;
		}
		if (s[i] != '\0')
			i++;
	}
	else if (s[i] == 39)
	{
		i++;
		while (s[i] != 39 && s[i] != 0)
		{
			i++;
		}
		if (s[i] != '\0')
			i++;
	}
	return (i);
}

/******************************************************************************
Transform a list into a tab of string
Return : pointer to a tab
******************************************************************************/
static char	**args_to_tab_nullmgt(t_cmd_line *cmd, char **res, int lst_size)
{
	if (lst_size == 0)
		free(res);
	else
		cmd->exit_code = msg_inf(ERM_MALLOC, ERN_MALLOC);
	return (NULL);
}

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
		return (args_to_tab_nullmgt(cmd, res, lst_size));
	tmp = args;
	i = 0;
	while (tmp != NULL)
	{
		res[i] = s_expand((char *)tmp-> content, env, cmd);
		if (res[i] == NULL)
			cmd->exit_code = msg_inf (ERM_MALLOC, ERN_MALLOC);
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
