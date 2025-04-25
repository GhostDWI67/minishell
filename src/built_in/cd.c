/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwianni <dwianni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 12:22:39 by mpalisse          #+#    #+#             */
/*   Updated: 2025/04/25 14:02:41 by dwianni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
static void	oldpwd(t_list **env)
{
	t_list	*temp;
	char	*copy;
	int		size;
	
	temp = (*env);
	size = ft_lstsize(temp);
	while (size--)
	{
		if (ft_strncmp(temp->content, "PWD=", 3) == 0)
			copy = temp->content;
		temp = temp->next;
	}
}

static void	cd_core(char *arg, t_list **env)
{
	

	oldpwd(env);
}

int	cd(char **args, t_list **env)
{
	int	i;
	int	ret;

	i = 0;
	while (args[i])
		i++;
	if (i == 2)
	{
		ret = chdir(args[1]);
		if (ret == 0)
			cd_core(args[1], env);
		if (ret == -1)
			ret == 1;
		if (ret == 1)
			perror(args[1]);
		return (ret);
	}
	return (1);
}
*/
