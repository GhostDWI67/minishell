/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpalisse <mpalisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 14:10:07 by mpalisse          #+#    #+#             */
/*   Updated: 2025/07/03 15:07:05 by mpalisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/******************************************************************************
copies the char **env into a t_list env for later use
Return 0 if ok otherwise 1;
******************************************************************************/
int	init_env(t_cmd_line *cmd, char **env, char **argv)
{
	int		i;
	char	*tmp;
	t_list	*list;

	if (!(*env))
		return (make_env(cmd, argv));
	i = 0;
	list = NULL;
	while (env[i])
	{
		tmp = ft_strdup(env[i]);
		if (tmp)
			ft_lstaddback_content(&list, tmp);
		i++;
	}
	cmd->env = list;
	increase_shlvl(cmd->env);
	return (0);
}

/******************************************************************************
gets the value of the variable given to it in the env
Return var value or NULL if it doesnt exist;
******************************************************************************/
char	*ft_getenv(const char *var, t_list *env)
{
	t_list	*tmp;
	int		i;

	if (!env || !var)
		return (NULL);
	i = 0;
	tmp = env;
	while (var[i])
		i++;
	while (tmp != NULL)
	{
		if (!ft_strncmp((char *)tmp->content, var, i) && \
		((char *)tmp->content)[i] == '=')
			return ((char *)tmp->content + (i + 1));
		tmp = tmp->next;
	}
	return (NULL);
}
