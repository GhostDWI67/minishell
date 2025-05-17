/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpalisse <mpalisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 12:41:32 by mpalisse          #+#    #+#             */
/*   Updated: 2025/05/17 17:42:23 by mpalisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/******************************************************************************
traverse l'env et check si la variable existe deja
Return -1 si non déclaré sinon l'index ou elle est déclaré;
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
check si le nom de la variable est valide
Return true si ok sinon false;
******************************************************************************/
static bool	check_name(char *arg)
{
	int	i;

	i = 0;
	if (!arg[i] || (arg[i] != '_' && !ft_isalpha(arg[i])))
		return (false);
	while (arg[i] && arg[i] != '=')
	{
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
			return (false);
		i++;
	}
	return (true);
}

/******************************************************************************
transforme l'env en array et range l'array puis l'affiche
Return true si ok sinon false;
******************************************************************************/
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
		printf("declare -x ");
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

/******************************************************************************
ajoute ou update la valeur de la variable passé en arg
Return true si ok sinon false;
******************************************************************************/
bool	export_core(char *arg, t_list **env)
{
	int		i;
	int		index;
	char	*var;
	t_list	*temp;

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
		i = 0;
		while (i++ < index)
			(*env) = (*env)->next;
		free((*env)->content);
		(*env)->content = var;
	}
	(*env) = temp;
	return (true);
}

/******************************************************************************
export ajoute la ou les variables passé en arg dans l'env si elles ont un nom
valable, si aucun argument alors export affiche l'env trié par ordre
alphabetique
Return 0 si ok sinon 1;
******************************************************************************/
int	export(char **args, t_list **env, t_cmd_line *cmd, int in_child)
{
	int	i;

	i = 1;
	if (!args || !args[i])
	{
		if ((*env) && !no_args((*env)))
		{
			if (in_child == 1)
				free_cmd_line_exit(cmd);
			return (msg_error("export no args", 1));
		}
		if (in_child == 1)
			free_cmd_line_exit(cmd);
		return (0);
	}
	while (args[i])
	{
		if (!check_name(args[i]))
		{
			if (in_child == 1)
				free_cmd_line_exit(cmd);
			return (msg_inf(ERM_EXPORT, ERN_EXPORT));
		}
		else if (!export_core(args[i], env))
		{
			if (in_child == 1)
				free_cmd_line_exit(cmd);
			return (0);
		}
		i++;
	}
	if (in_child == 1)
		free_cmd_line_exit(cmd);
	return (0);
}
