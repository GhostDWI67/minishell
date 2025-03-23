/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwianni <dwianni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 23:15:15 by admin             #+#    #+#             */
/*   Updated: 2025/03/23 11:52:40 by dwianni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/******************************************************************************
Skip "" and ''
Return the value of the position + 1 of the end of quote
******************************************************************************/
int	skip_quote(int i, char *s)
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
