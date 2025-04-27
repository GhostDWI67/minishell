/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwianni <dwianni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 15:12:29 by dwianni           #+#    #+#             */
/*   Updated: 2025/04/27 18:38:05 by dwianni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/******************************************************************************
Improve the output parameter with the contains when out of quote
******************************************************************************/
void	mod_no_case(t_expand *s)
{
	int		start;
	char	*tmp;
	char	*tmp_env;

	start = s->i;
	while (s->input[s->i] != '\'' && s->input[s->i] != '"'
		&& s->input[s->i] != '$' && s->input[s->i] != '\0')
		s->i++;
	if (s->i != start)
	{
		tmp = s->output;
		tmp_env = ft_strndup(s->input, start, s->i - 1);
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
Modify the env_name ($env_name) in the structure expand
Manage the particular case linked with $
******************************************************************************/
void	get_env_var_name(t_expand *s)
{
	char	*tmp;

	s->i++;
	s->start = s->i;
	if (ft_isdigit(s->input[s->i]) != 0)
	{
		s->env_name = ft_strndup(s->input, s->start, s->i);
		s->i++;
		return ;
	}
	if (ft_isalnum(s->input[s->i]) == 0 && s->input[s->i] != '_'
		&& s->input[s->i] != ' ' && s->input[s->i] != ' ')
	{
		tmp = s->output;
		s->output = ft_strjoin(tmp, "$");
		free(tmp);
		return ;
	}
	while (ft_isalnum(s->input[s->i]) != 0 || s->input[s->i] == '_')
		s->i++;
	s->env_name = ft_strndup(s->input, s->start, s->i - 1);
}

/******************************************************************************
Improve the output parameter with the contains of the env parameter
******************************************************************************/
void	mod_dollar(t_expand *s, t_list *env, int in_quote)
{
	char	*tmp;

	get_env_var_name(s);
	if (s->env_name == NULL)
		return ;
	tmp = s->output;
	s->tmp_env_var = ft_getenv(s->env_name, env);
	if (in_quote == 0)
		shorten_envvar_outq(s);
	if (s->tmp_env_var != NULL)
	{
		s->output = ft_strjoin(tmp, s->tmp_env_var);
		free_null(&tmp);
		if (s->output == NULL)
			return ;
	}
	free_null(&s->env_name);
	//free_null(&s->tmp_env_var);
}

/******************************************************************************
Improve the output parameter with the contains inside simple quote
******************************************************************************/
void	mode_squote(t_expand *s)
{
	int		start;
	char	*tmp;
	char	*tmp_env;

	s->i++;
	start = s->i;
	while (s->input[s->i] != '\'')
		s->i++;
	tmp = s->output;
	tmp_env = ft_strndup(s->input, start, s->i - 1);
	if (tmp_env == NULL)
		return ;
	s->output = ft_strjoin(tmp, tmp_env);
	free_null(&tmp);
	free_null(&tmp_env);
	s->i++;
}

/******************************************************************************
Manage the specific case of env var inside or outside dquote
TEST="      XX      XX      " 
echo $TEST		=> XX XX---
echo "$TEST"	=>      XX      XX      ---
******************************************************************************/
void	shorten_envvar_outq(t_expand *s)
{
	char	*tmp;
	int		i;
	int		j;

	tmp = s->tmp_env_var;
	s->tmp_env_var = ft_strtrim(tmp, " ");
	if (s->tmp_env_var != NULL)
	{
		i = 0;
		j = 0;
		while (s->tmp_env_var[i] != '\0')
		{
			while (ft_is_white_space(s->tmp_env_var[i]) == 0
				&& s->tmp_env_var[i] != '\0')
			{
				s->tmp_env_var[j] = s->tmp_env_var[i];
				i++;
				j++;
			}
			if (ft_is_white_space(s->tmp_env_var[i]) == 1
				&& s->tmp_env_var[i] != '\0')
			{
				s->tmp_env_var[j] = s->tmp_env_var[i];
				i++;
				j++;
			}
			while (ft_is_white_space(s->tmp_env_var[i]) == 1
				&& s->tmp_env_var[i] != '\0')
				i++;
		}
		s->tmp_env_var[j] = '\0';
	}
	//free_null(&tmp);
}
