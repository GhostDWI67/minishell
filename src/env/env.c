/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpalisse <mpalisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 14:10:07 by mpalisse          #+#    #+#             */
/*   Updated: 2025/04/25 14:13:34 by mpalisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/******************************************************************************
init_env prend l'env de base et le copie en t_list dans t_cmd_line 
Return 0 si ok sinon 1;
******************************************************************************/
int	init_env(t_cmd_line *cmd, char **env)
{
	int		i;
	char	*tmp;
	t_list	*list;

	if (!(*env))
		return (1);
	i = 0;
	list = NULL;
	while (env[i])
	{
		tmp = ft_strdup(env[i]);
		if (!tmp)
		{
			ft_lstclear(&list, free);
			return (1);
		}
		ft_lstaddback_content(&list, tmp);
		i++;
	}
	cmd->env = list;
	return (0);
}