/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwianni <dwianni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 12:35:55 by dwianni           #+#    #+#             */
/*   Updated: 2025/04/11 17:42:34 by dwianni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/******************************************************************************
char *getenv(char *s)

toto'$USER   est ici!'$USER'toto est par la?'"titi et non!"EOF"efvseh $USER 123 $USER12  ;"
"toto $USER titi $USER"


echo $USER"$USER"'$USER'		dwiannidwianni$USER
echo $USER$/"$USER"'$USER'		dwianni$/dwianni$USER
echo "$USER$'$USER'"			dwianni$'dwianni'
echo $"salut"					salut
echo $+salut					echo $+salut
echo $$							donne le PID en cours
******************************************************************************/
void	expand(t_expand *s)
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
		if (s->output == NULL) //si le strjoin a pas marche
			return ;
		if (s->input[s->i] == '\'')
			mode_squote(s);
		else if (s->input[s->i] == '"')
			mode_dquote(s);
		else if (s->input[s->i] == '$')
			mod_dollar(s);
	}
}

/******************************************************************************
Improve the output parameter with the contains when out of quote
******************************************************************************/
void	mod_no_case(t_expand *s)
{
	int		start;
	char	*tmp;
	char	*tmp_env;
	
	start = s->i;
	while (s->input[s->i] != '\'' && s->input[s->i] != '"' &&
		s->input[s->i] != '$' && s->input[s->i] != '\0')
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
******************************************************************************/
void	get_env_var_name(t_expand *s)
{
	int	start;

	s->i++;
	start = s->i;
	if (ft_isdigit(s->input[s->i]) != 0)
	{
		s->env_name = ft_strndup(s->input, start, s->i);
		return ;
	}
	while (ft_isalnum(s->input[s->i]) != 0 || s->input[s->i] == '_')
		s->i++;
	s->env_name = ft_strndup(s->input, start, s->i - 1);
}

/******************************************************************************
Improve the output parameter with the contains of the env parameter
******************************************************************************/
void	mod_dollar(t_expand *s)
{
	char	*tmp;
	
	get_env_var_name(s);
	printf("ENV VAR :%s\n", s->env_name);
	if (s->env_name == NULL)
		return ;
	tmp = s->output;
	if (getenv(s->env_name) != NULL)
	{
		s->output = ft_strjoin(tmp, getenv(s->env_name));
		free(tmp);
		if (s->output == NULL)
			return ;
	}
	free(s->env_name);
	s->env_name = NULL;
}

/******************************************************************************
Improve the output parameter with the contains inside simple quote
******************************************************************************/
void	mode_squote(t_expand *s)
{
	int	start;
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
	free(tmp);
	free(tmp_env);
	s->i++;
}

/******************************************************************************
Improve the output parameter with the contains inside double quote
******************************************************************************/
void	mode_dquote(t_expand *s)
{
	int		start;
	char	*tmp;
	char	*tmp_env;

	s->i++;
	start = s->i;
	while (s->input[s->i] != '"' && s->input[s->i] != '$')
		s->i++;
	if (s->input[s->i] == '$')
	{
		tmp = s->output;
		tmp_env = ft_strndup(s->input, start, s->i - 1);
		if (tmp_env == NULL)
			return ;
		s->output = ft_strjoin(tmp, tmp_env);
		free(tmp);
		free(tmp_env);
		mod_dollar(s);
	}
	else
	{
		tmp = s->output;
		tmp_env = ft_strndup(s->input, start, s->i - 1);
		if (tmp_env == NULL)
			return ;
		s->output = ft_strjoin(tmp, tmp_env);
		free(tmp);
		free(tmp_env);
		s->i++;
	}
}