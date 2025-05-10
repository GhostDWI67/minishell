/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpalisse <mpalisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 12:33:34 by mpalisse          #+#    #+#             */
/*   Updated: 2025/05/10 18:16:25 by mpalisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/******************************************************************************
env traverse la variable d'env et affiche chaque node qui contient un "=" 
Return 0;
******************************************************************************/
int	env(t_list *env, t_cmd_line *cmd, int in_child)
{
	t_list	*tmp;

	tmp = env;
	while (tmp != NULL)
	{
		if (ft_strchr((char *)tmp->content, '='))
			printf("%s\n", (char *)tmp->content);
		tmp = tmp->next;
	}
	if (in_child == 1)
		free_cmd_line_exit(cmd);
	return (0);
}
