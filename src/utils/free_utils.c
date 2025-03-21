/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwianni <dwianni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 10:18:41 by dwianni           #+#    #+#             */
/*   Updated: 2025/03/21 17:03:15 by dwianni          ###   ########.fr       */
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
Free a t_list
Return ; 0 if OK, else 1
******************************************************************************/
int	free_lst(t_list *lst)
{
	t_list	*next;

	if (lst == NULL)
		return (1);
	while (lst != NULL)
	{
		next = lst->next;
		free(lst->content);
		free(lst);
		lst = next;
	}
	lst = NULL;
	return (0);
}


/******************************************************************************
Free a comand structure
Return ; 0 if OK, else 1  A LA LIMITE NE SERT A RIEN !!!!!!!!!!!!!!!!!!
******************************************************************************/
int	free_command(t_command cmd)
{
	//ft_lstclear(&cmd.args, free); //utile et fonctionne
	free_lst(cmd.args); //utile et fonctionne
	free(cmd.tab_args);
	ft_lstclear(&cmd.redirection, free); // utile
	//free_lst(cmd.redirection); //utile
	return (0);
}

/******************************************************************************
Free a comand structure
Return ; 0 if OK, else 1
******************************************************************************/
int	free_cmd_line(t_cmd_line *cmd)
{
	int i;

	ft_lstclear(&cmd->simple_cmd, free);
	free(cmd->input);
	i = 0;
	while (i < cmd->nb_simple_cmd)	
	{
		free_command(cmd->tab_cmd[i]);
		i++;
	}
	free(cmd->tab_cmd);
	free_tab_char(cmd->tab_path);
	//ft_lstclear(&cmd->simple_cmd, free); //ne fait rien
	//free_lst(cmd->simple_cmd);
	free(cmd);
	return (0);
}