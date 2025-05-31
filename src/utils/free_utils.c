/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwianni <dwianni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 10:18:41 by dwianni           #+#    #+#             */
/*   Updated: 2025/05/29 15:23:40 by dwianni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/******************************************************************************
Free a char tab
Return ; 0 if OK, else 1
******************************************************************************/
void	free_null(char **s)
{
	if (*s != NULL && s != NULL)
		free(*s);
	*s = NULL;
}

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
	tab = NULL;
	return (0);
}

/******************************************************************************
Free a comand structure
Return ; 0
******************************************************************************/
int	free_command(t_command cmd)
{
	free_null(&cmd.hd_input);
	free_null(&cmd.infile);
	free_null(&cmd.outfile);
	if (cmd.args != NULL)
		ft_lstclear(&cmd.args, free);
	free_tab_char(cmd.tab_args);
	if (cmd.redirection != NULL)
		ft_lstclear(&cmd.redirection, free);
	close(cmd.hd_pipe[0]);
	close(cmd.hd_pipe[1]);
	return (0);
}
