/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwianni <dwianni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 16:19:40 by dwianni           #+#    #+#             */
/*   Updated: 2025/03/09 19:21:48 by dwianni          ###   ########.fr       */
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
static int	sub_parse_token(char *s, int i)
{
	while (ft_is_white_space(s[i]) == 0 && s[i] != '\0' && s[i] != '|')
	{
		if (s[i] == 39 || s[i] == '"')
			i = skip_quote(i, s) - 1;
		i++;
	}
	return (i);
}

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
		i = sub_parse_token(s, i);
		tmp = ft_strndup(s, start, i - 1);
		if (tmp == NULL)
			return (NULL);
		if (tmp[0] != 0)
			ft_lstadd_back(&res, ft_lstnew(tmp));
		if (s[i] == '|')
			ft_lstadd_back(&res, ft_lstnew(ft_strndup(s, i, i)));
		else if (s[i] == '\0')
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
		while (ft_is_white_space(s[i]) == 0 && s[i] != '\0' && s[i] != '|')
		{
			if (s[i] == 39 || s[i] == '"')
				i = skip_quote(i, s) - 1;
			i++;
		}
		tmp = ft_strndup(s, start, i - 1);
		if (tmp == NULL)
			return (NULL);
		if (tmp[0] != 0)
			ft_lstadd_back(&res, ft_lstnew(tmp));
		if (s[i] == '|')
		{
			tmp = ft_strndup(s, i, i);
			if (tmp == NULL)
				return (NULL);
			ft_lstadd_back(&res, ft_lstnew(tmp));
		}
		else if (s[i] == '\0')
			break ;
		i++;
	}
	return (res);
}
*/