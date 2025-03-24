/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpalisse <mpalisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 12:33:34 by mpalisse          #+#    #+#             */
/*   Updated: 2025/03/24 16:27:06 by mpalisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/******************************************************************************
env traverse la variable d'env et affiche chaque node qui contien un "=" 
(normalement toute les variables d'env on un "=" donc je vois pas trop le but
de check mais la fonction est decrite comme ca)
Return 0;
******************************************************************************/
int	env(t_list *env)
{
	t_list	*tmp;

	tmp = env;
	while (tmp != NULL)
	{
		if (ft_strchr((char *)tmp->content, '='))
			printf("%s\n", (char *)tmp->content);
		tmp = tmp->next;
	}
	return (0);
}