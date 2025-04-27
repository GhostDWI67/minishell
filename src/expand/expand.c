/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwianni <dwianni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 12:35:55 by dwianni           #+#    #+#             */
/*   Updated: 2025/04/27 18:35:37 by dwianni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/******************************************************************************
Case managed

echo $USER						dwianni					OK
echo "$USER"					dwianni					OK
echo '$USER'					$USER					OK
echo $USER"$USER"'$USER'		dwiannidwianni$USER		OK
echo $USER$/"$USER"'$USER'		dwianni$/dwianni$USER	OK
echo "$USER$'$USER'"			dwianni$'dwianni'		OK
echo "$USER$"					dwianni$				OK
echo $"salut"					salut					OK
echo $+salut					$+salut					OK
echo $123						23						OK
echo $USER$/"$USER"'$USER' "$USER$'$USER''$USER'" $"salut" $+salut $123
			dwianni$/dwianni$USER dwianni$'dwianni''dwianni' salut $+salut 23
echo $$							give the actual PID, not managed

export TEST="      XXX        "			=> reste a traiter
ECHO $TEST		- XXX -				on trime
ECHO "$TEST"	-      XXX    -		on trime pas

RULES FOR ENV VAR
var start with an alpha (low or upper case) or underscore(_)
after you can use alphanum and underscore(_)
******************************************************************************/
/******************************************************************************
Free a expand structure
******************************************************************************/
static void	free_expand(t_expand *s)
{
	s->input = NULL;
	if (s->output != NULL)
	{
		free(s->output);
		s->output = NULL;
	}
	if (s->env_name != NULL)
	{
		free(s->env_name);
		s->env_name = NULL;
	}
	free(s);
	s = NULL;
}

/******************************************************************************
Generate the expand into the structure expand
output parameter is fully modified by the function
******************************************************************************/
static void	expand(t_expand *s, t_list *env)
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
		if (s->input[s->i] == '\'')
			mode_squote(s);
		else if (s->input[s->i] == '"')
			mode_dquote(s, env);
		else if (s->input[s->i] == '$')
			mod_dollar(s, env, 0);
	}
}

/******************************************************************************
Expand the string
Return : expended string
******************************************************************************/
char	*s_expand(char *str, t_list *env)
{
	char		*res;
	t_expand	*s;

	s = malloc(sizeof(t_expand) * 1);
	s->input = str;
	s->output = NULL;
	s->env_name = NULL;
	expand(s, env);
	res = ft_strdup(s->output);
	free_expand(s);
	return (res);
}
