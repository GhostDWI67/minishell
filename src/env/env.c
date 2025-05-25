/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwianni <dwianni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 14:10:07 by mpalisse          #+#    #+#             */
/*   Updated: 2025/05/25 17:23:29 by dwianni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/******************************************************************************
clear l'env s'il y a eu un probleme
Return 1;
******************************************************************************/
static int	clear_and_return(t_list **list)
{
	ft_lstclear(list, free);
	return (1);
}

/******************************************************************************
creer l'env s'il n'existe pas
Return 0 si ok sinon 1;
******************************************************************************/
static int	make_env(t_cmd_line *cmd)
{
	t_list	*list;
	char	path[PATH_MAX];
	char	*temp;

	list = NULL;
	if (getcwd(path, PATH_MAX) == NULL)
		return (1);
	temp = ft_strjoin("PWD=", path);
	if (!temp)
		return (clear_and_return(&list));
	ft_lstaddback_content(&list, temp);
	temp = ft_strdup("SHLVL=1");
	if (!temp)
		return (clear_and_return(&list));
	ft_lstaddback_content(&list, temp);
	temp = ft_strdup("_=/usr/bin/env");
	if (!temp)
		return (clear_and_return(&list));
	ft_lstaddback_content(&list, temp);
	free(temp);
	cmd->env = list;
	return (0);
}

/******************************************************************************
augmente la variable SHLVL apres l'init de l'env
Return void;
******************************************************************************/
static void	increase_shlvl(t_list *env)
{
	t_list	*tmp;
	int		lvl;
	char	*lvl_char;
	char	*temp;

	tmp = env;
	lvl_char = NULL;
	while (tmp != NULL)
	{
		if (!ft_strncmp((char *)tmp->content, "SHLVL", 5) && \
		((char *)tmp->content)[5] == '=')
		{
			lvl = ft_atoi((char *)tmp->content + 6);
			if (lvl < INT_MAX)
				lvl++;
			lvl_char = ft_itoa(lvl);
			temp = ft_strjoin("SHLVL=", lvl_char);
			export_core(temp, &env);
			free(temp);
		}
		tmp = tmp->next;
	}
	if (lvl_char)
		free(lvl_char);
}

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
		return (make_env(cmd));
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
