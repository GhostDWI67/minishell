/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwianni <dwianni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 15:17:44 by dwianni           #+#    #+#             */
/*   Updated: 2025/05/04 14:23:48 by dwianni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/******************************************************************************
Improve the output parameter with the contains inside double quote
******************************************************************************/
static void	mode_quote_dolcase(t_expand *s, t_list *env, t_cmd_line *cmd)
{
	char	*tmp;
	char	*tmp_env;

	if (s->input[s->i - 1] == '"' && s->input[s->i] == '$'
		&& s->input[s->i + 1] == '"')
	{
		tmp = s->output;
		s->output = ft_strjoin(tmp, "$");
		free(tmp);
		s->i++;
		s->start = s->i;
		return ;
	}
	else
	{
		tmp = s->output;
		tmp_env = ft_strndup(s->input, s->start, s->i - 1);
		if (tmp_env == NULL)
			return ;
		s->output = ft_strjoin(tmp, tmp_env);
		free(tmp);
		free(tmp_env);
		mod_dollar(s, env, cmd);
		s->start = s->i;
	}
}

static void	mode_quote_dquotecase(t_expand *s)
{
	char	*tmp;
	char	*tmp_env;

	tmp = s->output;
	tmp_env = ft_strndup(s->input, s->start, s->i - 1);
	if (tmp_env == NULL)
		return ;
	s->output = ft_strjoin(tmp, tmp_env);
	free(tmp);
	free(tmp_env);
	s->i++;
}

void	mode_dquote(t_expand *s, t_list *env, t_cmd_line *cmd)
{
	s->i++;
	s->start = s->i;
	while (1)
	{
		while (s->input[s->i] != '"' && s->input[s->i] != '$')
			s->i++;
		if (s->input[s->i] == '$')
		{
			mode_quote_dolcase(s, env, cmd);
		}
		else if (s->input[s->i] == '"' && s->start != s->i)
		{
			mode_quote_dquotecase(s);
			break ;
		}
		else if (s->input[s->i] == '"' && s->start == s->i)
		{
			s->i++;
			break ;
		}
	}
}
