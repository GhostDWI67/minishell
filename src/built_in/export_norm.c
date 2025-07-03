/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_norm.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpalisse <mpalisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 14:15:18 by mpalisse          #+#    #+#             */
/*   Updated: 2025/07/03 15:01:46 by mpalisse         ###   ########.fr       */
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
	j = 0;
	tmp = env;
	while (arg[i] && arg[i] != '=')
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
adds or updates in the env the variables passed to it
Return true if ok otherwise false;
******************************************************************************/
bool	export_core(char *arg, t_list **env)
{
	int		index;
	char	*var;
	t_list	*temp;

	if (!arg)
		return (false);
	temp = (*env);
	index = declared(arg, (*env));
	var = ft_strdup(arg);
	if (!var)
		return (false);
	if (index == -1)
	{
		if (!ft_lstaddback_content(env, var))
			return (true);
	}
	else if (index >= 0)
	{
		while (index-- > 0)
			(*env) = (*env)->next;
		free((*env)->content);
		(*env)->content = var;
	}
	(*env) = temp;
	return (true);
}
