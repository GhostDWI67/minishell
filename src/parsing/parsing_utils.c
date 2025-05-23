/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpalisse <mpalisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 23:15:15 by admin             #+#    #+#             */
/*   Updated: 2025/05/07 11:25:03 by mpalisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
