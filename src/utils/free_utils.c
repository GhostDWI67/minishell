/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwianni <dwianni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 10:18:41 by dwianni           #+#    #+#             */
/*   Updated: 2025/03/21 16:20:09 by dwianni          ###   ########.fr       */
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
Return ; 0 if OK, else 1
******************************************************************************/
int	free_command(t_command cmd)
{
	free(cmd.tab_args);
	ft_lstclear(&cmd.args, free);
	//free(cmd.tab_args);
	ft_lstclear(&cmd.redirection, free);
	return (0);
}

/******************************************************************************
Free a comand structure
Return ; 0 if OK, else 1
******************************************************************************/
int	free_cmd_line(t_cmd_line *cmd)
{
	int i;

	free(cmd->input);
	i = 0;
	while (i < cmd->nb_simple_cmd)	
	{
		free_command(cmd->tab_cmd[i]);
		i++;
	}
	free(cmd->tab_cmd);
	free_tab_char(cmd->tab_path);
	ft_lstclear(&cmd->simple_cmd, free);
	free(cmd);
	return (0);
}