/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwianni <dwianni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 10:18:41 by dwianni           #+#    #+#             */
/*   Updated: 2025/03/28 10:26:22 by dwianni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/******************************************************************************
Free a char tab
Return ; 0 if OK, else 1
******************************************************************************/
int	free_tab_char(char	**tab)
{
	int	i;

	if (tab == NULL)
		return (1);
	i = 0;
	while (tab [i] != NULL)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (0);
}

/******************************************************************************
Free a comand structure
Return ; 0
******************************************************************************/
int	free_command(t_command cmd)
{
	free(cmd.infile);
	cmd.infile = NULL;
	free(cmd.outfile);
	cmd.outfile = NULL;
	if (cmd.args != NULL)
		ft_lstclear(&cmd.args, free);
	free(cmd.tab_args);
	if (cmd.redirection != NULL)
		ft_lstclear(&cmd.redirection, free);
	return (0);
}

/******************************************************************************
Free a comand structure
Return ; 0 if OK, else 1
******************************************************************************/
int	free_cmd_line(t_cmd_line *cmd)
{
	int	i;

	if (cmd->simple_cmd != NULL)
		ft_lstclear(&cmd->simple_cmd, free);
	free(cmd->input);
	i = 0;
	while (i < cmd->nb_simple_cmd)
	{
		free_command(cmd->tab_cmd[i]);
		i++;
	}
	free(cmd->tab_cmd);
	if (cmd->tab_path != NULL)
		free_tab_char(cmd->tab_path);
	free(cmd);
	return (0);
}
