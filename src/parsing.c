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
Skip "" and ''
Return the value of the position + 1 of the end of quote
******************************************************************************/
static int	skip_quote(int i, char *s)
{
	if (s[i] == '"')
	{
		i++;
		while (s[i] != '"' && s[i] != 0)
		{
			i++;
		}
		i++;
	}
	else if (s[i] == 39)
	{
		i++;
		while (s[i] != 39 && s[i] != 0)
		{
			i++;
		}
		i++;
	}
	return (i);
}

/******************************************************************************
Clean unnecessary space before redirection
Return : cleaned string
******************************************************************************/
static void	sub_clean_space(char *s, int i, int skip, int dec)
{
	while (s[i] != 0)
	{
		if (s[i] == '"' || s[i] == 39)
		{
			skip = skip_quote(i, s);
			while (i < skip)
			{
				s[i - dec] = s[i];
				i++;
			}
		}
		if (s[i] == '<' || s[i] == '>')
		{
			i++;
			while (ft_is_white_space(s[i]) == 1 && s[i] != '\0')
			{
				i++;
				dec++;
			}
		}
		else
			i++;
		s[i - dec] = s[i];
	}
	s[i - dec] = s[i];
}

void	clean_space(char *s)
{
	int		i;
	int		skip;
	int		dec;

	i = 0;
	dec = 0;
	skip = 0;
	sub_clean_space(s, i, skip, dec);
}

/*
void	clean_space(char *s)
{
	int		i;
	int		skip;
	int		dec;

	i = 0;
	dec = 0;
	skip = 0;
	while (s[i] != 0)
	{
		if (s[i] == '"' || s[i] == 39)
		{
			skip = skip_quote(i, s);
			while (i < skip)
			{
				s[i - dec] = s[i];
				i++;
			}
		}
		if (s[i] == '<' || s[i] == '>')
		{
			i++;
			while (ft_is_white_space(s[i]) == 1 && s[i] != '\0')
			{
				i++;
				dec++;
			}
		}
		else
			i++;
		s[i - dec] = s[i];
	}
	s[i - dec] = s[i];
}
*/

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
******************************************************************************/
static t_list	*sub_parse_token(char *s, int i, int start, char *tmp)
{
	t_list	*res;
	
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

t_list	*parse_token(char *s)
{
	int		i;
	int		start;
	char	*tmp;

	i = 0;
	start = 0;
	tmp = NULL;
	return (sub_parse_token(s, i, start, tmp));
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