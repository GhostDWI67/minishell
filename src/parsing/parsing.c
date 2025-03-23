/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwianni <dwianni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 16:19:40 by dwianni           #+#    #+#             */
/*   Updated: 2025/03/22 11:11:17 by dwianni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/******************************************************************************
Generate a list of elemetary commamd
Return : pointer to the start of the list
******************************************************************************/
t_list	*parse_cmd(char *s)
{
	t_list	*res;
	int		i;
	int		start;
	char	*tmp;

	i = 0;
	res = NULL;
	while (s[i] != 0)
	{
		start = i;
		while (s[i] != '|' && s[i] != '\0')
		{
			i = skip_quote(i, s);
			i++;
		}
		tmp = ft_strndup(s, start, i);
		if (tmp == NULL)
			return (NULL);
		ft_lstadd_back(&res, ft_lstnew(tmp));
		if (s[i] == '\0')
			return (res);
		i++;
	}
	return (res);
}

/******************************************************************************
Generate a list of token
Return : pointer to the start of the list

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

static t_list	*sub_parse_token(t_list *res, char *s, int i, int start)
{
	char	*tmp;

	tmp = ft_strndup(s, start, i - 1);
	if (tmp == NULL)
		return (NULL);
	if (tmp[0] != 0)
		ft_lstadd_back(&res, ft_lstnew(tmp));
	if (s[i] == '|')
	{
		ft_lstadd_back(&res, ft_lstnew(ft_strndup(s, i, i)));
		free(tmp);
	}
	return (res);
}

t_list	*parse_token(char *s)
{
	t_list	*res;
	int		i;
	int		start;

	i = 0;
	res = NULL;
	while (s[i] != 0)
	{
		while (ft_is_white_space(s[i]) == 1 && s[i] != '\0')
			i++;
		start = i;
		i = parse_token_quote(s, i);
		res = sub_parse_token(res, s, i, start);
		if (s[i] == '\0')
			break ;
		i++;
	}
	return (res);
}

/*
t_list	*parse_token(char *s)
{
	t_list	*res;
	int		i;
	int		start;
		char	*tmp;

	i = 0;
	res = NULL;
	while (s[i] != 0)
	{
		while (ft_is_white_space(s[i]) == 1 && s[i] != '\0')
			i++;
		start = i;
		i = parse_token_quote(s, i);
		tmp = ft_strndup(s, start, i - 1);
		if (tmp == NULL)
			return (NULL);
		if (tmp[0] != 0)
			ft_lstadd_back(&res, ft_lstnew(tmp));
		if (s[i] == '|')
		{
			ft_lstadd_back(&res, ft_lstnew(ft_strndup(s, i, i)));
			free(tmp);
		}
		else if (s[i] == '\0')
			break ;
		i++;
	}
	return (res);
}
*/
