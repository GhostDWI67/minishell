/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwianni <dwianni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 15:44:26 by dwianni           #+#    #+#             */
/*   Updated: 2025/04/05 18:22:21 by dwianni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/******************************************************************************
Generate a list of token
Return : pointer to the start of the token list

To do : en cas de strdup, free la liste ?? // protection malloc strdup ??
******************************************************************************/
static t_token	*parse_token_add_arg(t_token *res, char *s, int start, int end)
{
	char	*tmp;

	tmp = ft_strndup(s, start, end);
	if (tmp == NULL)
		return (NULL);
	if (tmp[0] != 0)
		token_add_back(&res, token_new(tmp, ARG));
	return (res);
}

static int	parse_token_skip(char *s, int i)
{
	while (ft_is_white_space(s[i]) == 0 && s[i] != '|' && s[i] != '>'
		&& s[i] != '<' && s[i] != '\0')
	{
		if (s[i] == '"' || s[i] == 39)
			i = skip_quote(i, s);
		i++;
	}
	return (i);
}

static int	parse_token_add(t_token *res, char *sep, int i, int type)
{
	token_add_back(&res, token_new(ft_strdup(sep), type));
	i = i + ft_strlen(sep);
	return (i);
}

t_token	*sub_parse_token(char *s, t_token *res, int i, int start)
{
	while (s[i] != 0)
	{
		while (ft_is_white_space(s[i]) == 1 && s[i] != '\0')
			i++;
		if (ft_is_white_space(s[i]) == 0 && s[i] != '|' && s[i] != '>'
			&& s[i] != '<' && s[i] != '\0')
		{
			start = i;
			i = parse_token_skip(s, i);
			res = parse_token_add_arg(res, s, start, i - 1);
		}
		else if (ft_strncmp(s + i, "|", 1) == 0)
			i = parse_token_add(res, "|", i, PIPE);
		else if (ft_strncmp(s + i, "<<", 2) == 0)
			i = parse_token_add(res, "<<", i, HEREDOC);
		else if (ft_strncmp(s + i, ">>", 2) == 0)
			i = parse_token_add(res, ">>", i, APPEND);
		else if (s[i] == '<' && s[i + 1] != '<')
			i = parse_token_add(res, "<", i, INPUT);
		else if (s[i] == '>' && s[i + 1] != '>')
			i = parse_token_add(res, ">", i, OUTPUT);
	}
	return (res);
}

t_token	*parse_token(char *s)
{
	t_token	*res;
	int		i;
	int		start;

	i = 0;
	res = NULL;
	start = 0;
	return (sub_parse_token(s, res, i, start));
}

/*
t_token	*parse_token(char *s)
{
	t_token	*res;
	int		i;
	int		start;

	i = 0;
	res = NULL;
	while (s[i] != 0)
	{
		while (ft_is_white_space(s[i]) == 1 && s[i] != '\0')
			i++;
		if (ft_is_white_space(s[i]) == 0 && s[i] != '|' && s[i] != '>'
			&& s[i] != '<' && s[i] != '\0')
		{
			start = i;
			while (ft_is_white_space(s[i]) == 0 && s[i] != '|' && s[i] != '>'
				&& s[i] != '<' && s[i] != '\0')
			{
				if (s[i] == '"' || s[i] == 39)
					i = skip_quote(i, s);
				i++;
			}
			res = sub_parse_token2(res, s, start, i - 1);
		}
		else if (ft_strncmp(s + i, "|", 1) == 0)
		{
			token_add_back(&res, token_new(ft_strdup("|"), PIPE));
			i++;
		}
		else if (ft_strncmp(s + i, "<<", 2) == 0)
		{
			token_add_back(&res, token_new(ft_strdup("<<"), HEREDOC));
			i = i + 2;
		}
		else if (ft_strncmp(s + i, ">>", 2) == 0)
		{
			token_add_back(&res, token_new(ft_strdup(">>"), APPEND));
			i = i + 2;
		}
		else if (s[i] == '<' && s[i + 1] != '<')
		{
			token_add_back(&res, token_new(ft_strdup("<"), INPUT));
			i++;
		}
		else if (s[i] == '>' && s[i + 1] != '>')
		{
			token_add_back(&res, token_new(ft_strdup(">"), OUTPUT));
			i++;
		}
	}
	return (res);
}
*/