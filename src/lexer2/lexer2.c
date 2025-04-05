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
static int	parse_token_quote(char *s, int i)
{
	while (ft_is_white_space(s[i]) == 0 && s[i] != '\0' && s[i] != '|')
	{
		if (s[i] == 39 || s[i] == '"')
			i = skip_quote(i, s) - 1;
		i++;
	}
	return (i);
}

static t_token	*sub_parse_token2(t_token *res, char *s, int start, int end)
{
	char	*tmp;

	tmp = ft_strndup(s, start, end);
	printf("strndup : %s\n", tmp);
	if (tmp == NULL)
		return (NULL);
	if (tmp[0] != 0)
		token_add_back(&res, token_new(tmp, ARG));
	return (res);
}

t_token	*parse_token2(char *s)
{
	t_token	*res;
	int		i;
	int		start;
	int		end;
	int		add;

	i = 0;
	res = NULL;
	start = 0;
	end = 0;
	printf("input a lexer : %s\n", s);
	while (s[i] != 0)
	{
		add = 0;
		//while (ft_is_white_space(s[i]) == 1 && s[i] != '\0')
		//	i++;
		printf("i %d \n", i);
		if (ft_strncmp(s + i, "|", 1) == 0)
		{
			token_add_back(&res, token_new("|", PIPE));
			end = i - 1;
			add++;
		}
		else if (ft_strncmp(s + i, "<<", 2) == 0)
		{
			token_add_back(&res, token_new("<<", HEREDOC));
			end = i - 1;
			add = add + 2;
		}
		else if (ft_strncmp(s + i, ">>", 1) == 0)
		{
			token_add_back(&res, token_new(">>", APPEND));
			end = i - 1;
			add = add + 2;
		}
		else if (ft_strncmp(s + i, "<", 1) == 0)
		{
			token_add_back(&res, token_new("<", INPUT));
			end = i - 1;
			add++;;
		}
		else if (ft_strncmp(s + i, ">", 1) == 0)
		{
			token_add_back(&res, token_new(">", OUTPUT));
			end = i - 1;
			add++;
		}
		else
		{
			printf("i else %d \n", i);
			if (start == 0)
				start = i;
			if (ft_is_white_space(s[i + 1]) == 1 || s[i + 1] == 0)
				end = i;
			i = parse_token_quote(s, i);
		}
		printf("i %d \n", i);
		if (ft_is_white_space(s[i + 1]) == 1 || s[i + 1] == 0)
		{
			res = sub_parse_token2(res, s, start, end);
			start = 0;
			end = 0;
		}
		printf("i %d start %d end %d add %d\n", i, start, end, add);
		i = i + add;
		
		if (s[i] == '\0')
			break ;
		i++;
	}
	return (res);
}
