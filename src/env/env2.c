/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwianni <dwianni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 14:10:07 by mpalisse          #+#    #+#             */
/*   Updated: 2025/05/29 15:29:09 by dwianni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/******************************************************************************
init_env prend l'env de base et le copie en t_list dans t_cmd_line 
Return 0 si ok sinon 1;
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
		if (!tmp)
		{
			ft_lstclear(&list, free);
			return (1);
		}
		ft_lstaddback_content(&list, tmp);
		i++;
	}
	cmd->env = list;
	increase_shlvl(cmd->env);
	return (0);
}

/******************************************************************************
cherche dans l'env le nom de la variable donné et elle doit etre exact pour
etre trouvé:
ft_getenv("HOME", env) renvoi /home/USER
ft_getenv("HOM", env) renvoi NULL
Return la valeur de la variable sinon NULL;
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
