/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpalisse <mpalisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 13:57:29 by mpalisse          #+#    #+#             */
/*   Updated: 2025/03/25 15:31:19 by mpalisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/******************************************************************************
creer une node de t_list a la fin de la liste avec le contenu passé en arg
Return ; 0 if OK, else 1
******************************************************************************/
int	ft_lstaddback_content(t_list **env, char *content)
{
	t_list *new;
	
	new = ft_lstnew(content);
	if (!new)
		return (1);
	ft_lstadd_back(env, new);
	return (0);
}

char	**ft_lst_to_arr(t_list *env)
{
	int		i;
	t_list	*list;
	char	**ret;

	ret = NULL;
	i = 0;
	list = env;
	ret = (char **)malloc(sizeof(char *) * (ft_lstsize(list) + 1));
	if (!ret)
		return (NULL);
	while (list != NULL)
	{
		ret[i] = ((char *)list->content);
		list = list->next;
		i++;
	}
	ret[i] = NULL;
	return (ret);
}

static void	ft_swap(int i, int j, char **tab)
{
	char	*temp;

	temp = tab[i];
	tab[i] = tab[j];
	tab[j] = temp;
}

void	sort_tab(char **arr, int len)
{
	int	i;
	int	j;

	i = 0;
	while (i < len)
	{
		j = i + 1;
		while (j < len)
		{
			if (ft_strncmp(arr[i], arr[j], __INT_MAX__) > 0)
			{
				ft_swap(i, j, arr);
				continue ;
			}
			j++;
		}
	i++;
	}
}
