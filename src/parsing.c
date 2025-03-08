/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwianni <dwianni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 16:19:40 by dwianni           #+#    #+#             */
/*   Updated: 2025/03/08 19:03:54 by dwianni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/******************************************************************************
Skip "" and ''
Return the value of the position of the end of quote
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
Check if inside quote
Return : cleaned string
******************************************************************************/


/******************************************************************************
Clean unnecessary space before redirection
Return : cleaned string
******************************************************************************/
char	*clean_space(char *s)
{
	char	*res;
	int		i;
	int		dec;

	res = (char *)malloc(sizeof(char) * (strlen(s) + 1));
	if (res == NULL)
		return (free(s), NULL);
	i = 0;
	dec = 0;
	while (s[i] != 0)
	{
		res[i - dec] = s[i];
		if (s[i] == '"')
		{
			printf("double quote\n");
			i++;
			res[i - dec] = s[i];
			while (s[i] != '"' && s[i] != 0)
			{
				i++;
				res[i - dec] = s[i];
			}
			i++;
			res[i - dec] = s[i];
		}
		else if (s[i] == 39)
		{
			printf("simple quote\n");
			i++;
			res[i - dec] = s[i];
			while (s[i] != 39 && s[i] != 0)
			{
				i++;
				res[i - dec] = s[i];
			}
			i++;
			res[i - dec] = s[i];
		}
		if ((s[i] == '<' && ft_is_white_space(s[i + 1]) == 1)
			|| (s[i] == '>' && ft_is_white_space(s[i + 1]) == 1))
		{
			printf("toto\n");
			res[i - dec] = s[i];
			i++;
			while (ft_is_white_space(s[i]) == 1 && s[i] != '\0')
			{
				i++;
				dec++;
				printf("titi dec %d\n", dec);
			}
		}
		else
			i++;
	}
	res[i - dec] = '\0';
	printf("end i %d dec %d\n", i, dec);
	free(s);
	return (res);
}

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
		while (s[i] != '|' && s[i] != 0)
		{
			i = skip_quote(i, s);
			i++;
		}
		tmp = ft_strndup(s, start, i);
		printf("tmp %s***\n", tmp);
		ft_lstadd_back(&res, ft_lstnew(tmp));
		i++;
	}
	return (res);
}

/******************************************************************************
Generate a list of token
Return : pointer to the start of the list
******************************************************************************/
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
		while (ft_is_white_space(s[i]) == 1 && s[i] != 0)
			i++;
		start = i;
		while (ft_is_white_space(s[i]) == 0 && s[i] != 0 && s[i]!='|')
		{
			i = skip_quote(i, s);
			i++;
		}
		tmp = ft_strndup(s, start, i - 1);
		ft_lstadd_back(&res, ft_lstnew(tmp));
		i++;
	}
	return (res);
}
