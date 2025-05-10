/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rebuilt_arg.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpalisse <mpalisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 13:08:52 by dwianni           #+#    #+#             */
/*   Updated: 2025/05/10 17:01:13 by mpalisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/******************************************************************************
dup_inquote
make duplication part of exp_inquote
******************************************************************************/
static void	dup_inquote(t_expand *s, int start, char *tmp, char *tmp_env)
{
	if (s->i != start)
	{
		tmp = s->output;
		tmp_env = ft_strndup(s->input, start, s->i);
		if (tmp_env == NULL)
			return ;
		s->output = ft_strjoin(tmp, tmp_env);
		free(tmp);
		tmp = NULL;
		free(tmp_env);
		tmp_env = NULL;
	}
}

/******************************************************************************
exp_inquote
Generate the expand into the structure expand inside the quote
******************************************************************************/
static void	exp_inquote(t_expand *s)
{
	int		start;
	char	*tmp;
	char	*tmp_env;

	tmp = NULL;
	tmp_env = NULL;
	start = s->i;
	if (s->input[s->i] == '\'')
	{
		s->i++;
		while (s->input[s->i] != '\'')
			s->i++;
	}
	else if (s->input[s->i] == '"')
	{
		s->i++;
		while (s->input[s->i] != '"')
			s->i++;
	}
	dup_inquote(s, start, tmp, tmp_env);
	s->i++;
}

/******************************************************************************
Generate the expand into the structure expand
output parameter is fully modified by the function
******************************************************************************/
static void	expand(t_expand *s, t_list *env, t_cmd_line *cmd)
{
	s->output = NULL;
	s->env_name = NULL;
	s->output = ft_strdup("");
	if (s->output == NULL)
		return ;
	s->i = 0;
	while (s->input[s->i] != '\0')
	{
		mod_no_case(s);
		if (s->output == NULL)
			return ;
		if (s->input[s->i] == '\'' || s->input[s->i] == '"')
			exp_inquote(s);
		else if (s->input[s->i] == '$')
			mod_dollar(s, env, cmd);
	}
}

/******************************************************************************
Expand the string
Return : expended string
******************************************************************************/
static char	*d_expand(char *str, t_list *env, t_cmd_line *cmd)
{
	char		*res;
	t_expand	*s;

	s = malloc(sizeof(t_expand) * 1);
	s->input = str;
	s->output = NULL;
	s->env_name = NULL;
	expand(s, env, cmd);
	res = ft_strdup(s->output);
	free_expand(s);
	return (res);
}

/******************************************************************************
Rebuild ARGS
from the list ARGS of a simple command
Return : a string with all the ARGS of the list with only expension of $VAR
******************************************************************************/
char	*rebuilt_args(t_cmd_line *cmd, int i)
{
	t_list	*tmp;
	char	*tmp_res;
	char	*res;
	char	*ret;

	res = ft_strdup("");
	tmp = cmd->tab_cmd[i].args;
	while (tmp != NULL)
	{
		tmp_res = res;
		ret = d_expand((char *)tmp->content, cmd->env, cmd);
		res = ft_strjoin(tmp_res, ret);
		free(ret);
		free(tmp_res);
		tmp_res = res;
		res = ft_strjoin(tmp_res, " ");
		free(tmp_res);
		tmp = tmp->next;
	}
	return (res);
}
