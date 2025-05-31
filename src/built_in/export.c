/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpalisse <mpalisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 12:41:32 by mpalisse          #+#    #+#             */
/*   Updated: 2025/05/31 14:22:34 by mpalisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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

static int	export_norm(char **args, t_cmd_line *cmd)
{
	int	i;
	int	exit_status;

	i = 1;
	exit_status = 0;
	while (args[i])
	{
		if (!check_name(args[i]))
		{
			exit_status = 1;
			mod_error("export: `", args[i], "': not a valid identifier");
		}
		else if (!export_core(args[i], &cmd->env))
			return (1);
		i++;
	}
	return (exit_status);
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
	int	exit_status;

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
	exit_status = export_norm(args, cmd);
	if (in_child == 1)
		free_cmd_line_exit(cmd);
	return (exit_status);
}
