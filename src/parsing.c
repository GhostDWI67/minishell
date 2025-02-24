/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwianni <dwianni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 16:19:40 by dwianni           #+#    #+#             */
/*   Updated: 2025/02/24 18:58:01 by dwianni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/******************************************************************************

******************************************************************************/
t_list	*parse_cmd(char *s)
{
	t_list	*res;
	int		i;
	int		start;
	char 	*tmp;

	i = 0;
	res = NULL;
	while (s[i] != 0)
	{
		start = i;
		while(s[i] != '|' && s[i] != 0)
		{
			if (s[i] == '"')
			{
				i++;
			while (s[i] != '"' && s[i] != 0)
				i++;
			}
			i++;
			if (s[i] == 39)
			{
				i++;
			while (s[i] != 39 && s[i] != 0)
				i++;
			}
			i++;
		}
		tmp = ft_strndup(s, start, i);
		printf("start %d end %d parse : %s\n", start, i, tmp);
		ft_lstadd_back(&res, ft_lstnew(tmp));
		i++;
	}
	return (res);
}

/*
t_list	*parse_cmd(char *s)
{
	t_list	*res;
	int		i;
	int		start;
	char 	*tmp;

	i = 0;
	res = NULL;
	while (s[i] != 0)
	{
		while((s[i] > 8 && s[i] < 13) || s[i] == ' ')
			i++;
		start = i;
		while(s[i] != ' ' && s[i] != 0)
		{
			if (s[i] == '"')
			{
				i++;
			while (s[i] != '"' && s[i] != 0)
				i++;
			}
			i++;
		}
		tmp = ft_strndup(s, start, i);
		printf("start %d end %d parse : %s\n", start, i, tmp);
		ft_lstadd_back(&res, ft_lstnew(tmp));
		i++;
	}
	return (res);
}
*/