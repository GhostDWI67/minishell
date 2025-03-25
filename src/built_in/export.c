/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpalisse <mpalisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 12:41:32 by mpalisse          #+#    #+#             */
/*   Updated: 2025/03/25 15:31:05 by mpalisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static bool	no_args(t_list *env)
{
	int		i;
	int		j;
	char	**tab;

	i = 0;
	tab = ft_lst_to_arr(env);
	if (!tab)
		return (false);
	sort_tab(tab, ft_lstsize(env));
	while (tab[i])
	{
		//printf("declare -x ");
		j = 0;
		while (tab[i][j] && tab[i][j] != '=')
			printf("%c", tab[i][j++]);
		if (tab[i][j] && tab[i][j] == '=')
			printf("=\"%s\"\n", &tab[i][j + 1]);
		else
			printf("\n");
		i++;
	}
	free(tab);
	return (true);
}

int	export(char **args, t_list **env)
{
	int	i;

	i = 1;
	if (!args || !args[i])
	{
		if (*env && !no_args((*env)))
			return (msg_error("export error", 1));
		return (0);
	}
	return (0);
}
