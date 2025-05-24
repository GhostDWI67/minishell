/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwianni <dwianni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 15:12:29 by dwianni           #+#    #+#             */
/*   Updated: 2025/05/24 17:24:18 by dwianni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
	if (ft_isalnum(s->input[s->i]) == 0 && s->input[s->i] != '_')
	{
		if (s->input[s->i] == '"' || s->input[s->i] == '\'')
			return;
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
void	mod_dollar(t_expand *s, t_list *env, t_cmd_line *cmd)
{
	char	*tmp;
	char	*tmp2;

	if (s->input[s->i + 1] == '?')
	{
		tmp = s->output;
		tmp2 = ft_itoa(cmd->exit_code);
		s->output = ft_strjoin(tmp, tmp2);
		s->i = s-> i + 2;
		free(tmp2);
		free(tmp);
	}
	else
	{
		get_env_var_name(s);
		if (s->env_name == NULL)
			return ;
		tmp = s->output;
		s->tmp_env_var = ft_getenv(s->env_name, env);
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
