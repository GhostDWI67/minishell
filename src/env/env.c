/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwianni <dwianni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 14:10:07 by mpalisse          #+#    #+#             */
/*   Updated: 2025/05/29 15:35:00 by dwianni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	add_env(t_list **list, char *content, char *path)
{
	char	*temp;

	if (path != NULL)
		temp = ft_strjoin("PWD=", path);
	else
		temp = ft_strdup(content);
	if (!temp)
	{
		ft_lstclear(list, free);
		return (1);
	}
	if (ft_lstaddback_content(list, temp) == 1)
	{
		ft_lstclear(list, free);
		return (1);
	}
	return (0);
}

static int	make_underscore(t_list **list, char *path, char *arg)
{
	char	*temp;
	char	*buff;

	buff = ft_strjoin("_=", path);
	if (!buff)
		return (1);
	temp = ft_strjoin(buff, " ");
	free(buff);
	if (!temp)
		return (1);
	buff = ft_strjoin(temp, arg);
	free(temp);
	if (!buff)
		return (1);
	if (ft_lstaddback_content(list, buff) == 1)
		return (1);
	return (0);
}

/******************************************************************************
creer l'env s'il n'existe pas
Return 0 si ok sinon 1;
******************************************************************************/
int	make_env(t_cmd_line *cmd, char **argv)
{
	t_list	*list;
	char	path[PATH_MAX];

	list = NULL;
	if (getcwd(path, PATH_MAX) == NULL)
		return (1);
	if (add_env(&list, "PWD=", path) == 1)
		return (1);
	if (add_env(&list, "OLDPWD", NULL) == 1)
		return (1);
	if (add_env(&list, "SHLVL=1", NULL) == 1)
		return (1);
	if (make_underscore(&list, path, argv[0]) == 1)
		return (1);
	cmd->env = list;
	return (0);
}

static char	*check_shlvl(int lvl)
{
	char	*lvl_char;

	lvl++;
	if (lvl < 0)
		lvl = 0;
	else if (lvl > 999)
	{
		lvl_char = ft_itoa(lvl);
		mod_error("bash: warning: shell level (", lvl_char, \
			") too high, resetting to 1");
		free(lvl_char);
		lvl = 1;
		return (ft_itoa(lvl));
	}
	else
		return (ft_itoa(lvl));
	return (ft_itoa(lvl));
}

/******************************************************************************
augmente la variable SHLVL apres l'init de l'env
Return void;
******************************************************************************/
void	increase_shlvl(t_list *env)
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
			lvl_char = check_shlvl(lvl);
			temp = ft_strjoin("SHLVL=", lvl_char);
			export_core(temp, &env);
			free(temp);
		}
		tmp = tmp->next;
	}
	if (lvl_char)
		free(lvl_char);
	else
		export_core(ft_strdup("SHLVL=1"), &env);
}
