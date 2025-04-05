/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwianni <dwianni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 15:05:48 by dwianni           #+#    #+#             */
/*   Updated: 2025/04/05 14:35:34 by dwianni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/******************************************************************************
Double and simple quote check
Return : 0 = OK, other value NOK
******************************************************************************/
static int	int_check_quote(char *s, int count)
{
	while (*s != 0)
	{
		if (*s == '"')
		{
			count = 1;
			s++;
			while (*s != '"' && *s != 0)
				s++;
			if (*s == '"')
				count = 0;
		}
		if (*s == 39)
		{
			count = 1;
			s++;
			while (*s != 39 && *s != 0)
				s++;
			if (*s == 39)
				count = 0;
		}
		if (*s != 0)
			s++;
	}
	return (count);
}

int	check_quote(char *s)
{
	int	count;

	count = 0;
	return (int_check_quote(s, count));
}

/******************************************************************************
Only white space check
Return : 0 = OK, other value NOK = number of non white space char
******************************************************************************/
int	ws_check(char *s)
{
	int	i;
	int	res;

	i = 0;
	res = 0;
	while (s[i] != '\0')
	{
		if (ft_is_white_space(s[i]) == 0)
			res++;
		i++;
	}
	return (res);
}
