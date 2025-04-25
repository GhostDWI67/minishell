/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpalisse <mpalisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 10:29:49 by mpalisse          #+#    #+#             */
/*   Updated: 2025/04/16 12:10:58 by mpalisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	declared(char *arg, t_list *env)
{
	t_list	*tmp;
	int		i;
	int		j;

	if (!env)
		return (-1);
	i = 0;
	j = 1;
	tmp = env;
	while (arg[i])
		i++;
	while (tmp != NULL)
	{
		if (!ft_strncmp((char *)tmp->content, arg, i) && \
		(((char *)tmp->content)[i] == '\0' || \
		((char *)tmp->content)[i] == '='))
			return (j);
		tmp = tmp->next;
		j++;
	}
	return (-1);
}

static bool	check_name(char *arg)
{
	int	i;

	i = 0;
	if (arg[i] != '_' && !ft_isalpha(arg[i]))
		return (false);
	while (arg[i])
	{
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
			return (false);
		i++;
	}
	return (true);
}

static bool	unset_head(t_list **env, t_list *tmp, int pos)
{
	if (pos != 1)
		return (false);
	(*env) = tmp->next;
	ft_lstdelone(tmp, free);
	return (true);
}

static bool	unset_core(char *arg, t_list **env)
{
	t_list	*tmp;
	t_list	*tmp2;
	int		pos;

	if (!arg || !(*arg))
		return (true);
	if (!check_name(arg))
	{
		write(2, "unset: invalid identifier\n", 26);
		return (false);
	}
	pos = declared(arg, (*env));
	if (pos == -1)
		return (true);
	tmp = (*env);
	if (unset_head(env, tmp, pos) == true)
		return (true);
	pos--;
	while (pos-- > 1)
		tmp = tmp->next;
	tmp2 = tmp->next;
	tmp->next = tmp->next->next;
	ft_lstdelone(tmp2, free);
	return (true);
}

int	unset(char **args, t_list **env)
{
	int	i;

	i = 1;
	while (args[i])
	{
		if (!unset_core(args[i], env))
			write(2, "unset failed\n", 13);
		i++;
	}
	return (0);
}
