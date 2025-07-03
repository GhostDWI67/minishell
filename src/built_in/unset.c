/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpalisse <mpalisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 12:28:24 by mpalisse          #+#    #+#             */
/*   Updated: 2025/07/03 15:05:12 by mpalisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/******************************************************************************
goes through the env to check if the var already exists
Return -1 if not declared otherwise returns the index
******************************************************************************/
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

/******************************************************************************
check if var name is correct
Return true if ok otherwise false;
******************************************************************************/
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

/******************************************************************************
check if the var is the head of the env and unsets it
Return true if head otherwise false;
******************************************************************************/
static bool	unset_head(t_list **env, t_list *tmp, int pos)
{
	if (pos != 1)
		return (false);
	(*env) = tmp->next;
	ft_lstdelone(tmp, free);
	return (true);
}

/******************************************************************************
checks var name and unsets it if it exists
Return true if ok otherwise false;
******************************************************************************/
static bool	unset_core(char *arg, t_list **env)
{
	t_list	*tmp;
	t_list	*tmp2;
	int		pos;

	if (!arg || !(*arg))
		return (true);
	if (!check_name(arg))
	{
		mod_error("unset: `", arg, "': not a valid identifier");
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

/******************************************************************************
launches unset for all args passed to it
Return 0;
******************************************************************************/
int	unset(char **args, t_list **env, t_cmd_line *cmd, int in_child)
{
	int	i;
	int	exit_status;

	i = 1;
	exit_status = 0;
	while (args[i])
	{
		if (!unset_core(args[i], env))
			exit_status = 1;
		i++;
	}
	if (in_child == 1)
		free_cmd_line_exit(cmd);
	return (exit_status);
}
