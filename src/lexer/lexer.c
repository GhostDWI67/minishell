/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpalisse <mpalisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 15:44:26 by dwianni           #+#    #+#             */
/*   Updated: 2025/06/01 13:00:16 by mpalisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/******************************************************************************
Generate a list of token
Return : pointer to the start of the token list
******************************************************************************/
static t_token	*parse_token_add_arg(t_token *res, char *s, int start, int end)
{
	char	*tmp;
	t_token	*tmp_node;

	tmp = ft_strndup(s, start, end);
	if (tmp == NULL)
		return (NULL);
	if (tmp[0] != 0)
	{
		tmp_node = token_new(tmp, ARG);
		if (tmp_node != NULL)
			token_add_back(&res, tmp_node);
		else
			free (tmp);
	}
	return (res);
}

static int	parse_token_skip(char *s, int i)
{
	while (ft_is_white_space(s[i]) == 0 && s[i] != '|' && s[i] != '>'
		&& s[i] != '<' && s[i] != '\0')
	{
		if (s[i] == '"' || s[i] == 39)
			i = skip_quote(i, s);
		else
			i++;
	}
	return (i);
}

static int	parse_token_add(t_token **res, char *sep, int i, int type)
{
	char	*tmp;
	t_token	*tmp_node;

	tmp = ft_strdup(sep);
	tmp_node = token_new(tmp, type);
	if (tmp_node != NULL)
		token_add_back(res, tmp_node);
	else
		free (tmp);
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
			i = parse_token_add(&res, "|", i, PIPE);
		else if (ft_strncmp(s + i, "<<", 2) == 0)
			i = parse_token_add(&res, "<<", i, HEREDOC);
		else if (ft_strncmp(s + i, ">>", 2) == 0)
			i = parse_token_add(&res, ">>", i, APPEND);
		else if (s[i] == '<' && s[i + 1] != '<')
			i = parse_token_add(&res, "<", i, INPUT);
		else if (s[i] == '>' && s[i + 1] != '>')
			i = parse_token_add(&res, ">", i, OUTPUT);
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
