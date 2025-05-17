/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpalisse <mpalisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 10:18:41 by dwianni           #+#    #+#             */
/*   Updated: 2025/05/17 12:28:09 by mpalisse         ###   ########.fr       */
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
	return (0);
}

/******************************************************************************
Free a command line
Return ; 0 if OK, else 1
******************************************************************************/
int	free_cmd_line(t_cmd_line *cmd)
{
	int	i;

	if (cmd->input != NULL)
		free(cmd->input);
	if (cmd->tab_fd)
		free(cmd->tab_fd);
	if (cmd->tab_pid)
		free(cmd->tab_pid);
	i = 0;
	while (i < cmd->nb_simple_cmd)
	{
		free_command(cmd->tab_cmd[i]);
		i++;
	}
	if (cmd->tab_cmd)
		free(cmd->tab_cmd);
	if (cmd->token)
		token_clear(&cmd->token);
	if (cmd->tab_path != NULL)
		free_tab_char(cmd->tab_path);
	free(cmd->tab_env);
	return (0);
}

int	free_cmd_line_exit(t_cmd_line *cmd)
{
	int	i;

	if (cmd->input != NULL)
		free(cmd->input);
	if (cmd->tab_fd)
		free(cmd->tab_fd);
	if (cmd->tab_pid)
		free(cmd->tab_pid);
	i = 0;
	while (i < cmd->nb_simple_cmd)
	{
		free_command(cmd->tab_cmd[i]);
		i++;
	}
	if (cmd->tab_cmd)
		free(cmd->tab_cmd);
	if (cmd->token)
		token_clear(&cmd->token);
	if (cmd->tab_path != NULL)
		free_tab_char(cmd->tab_path);
	if (cmd->env)
	{
		ft_lstclear(&cmd->env, free);
		free(cmd->env);
	}
	if (cmd->tab_env)
		free(cmd->tab_env);
	if (cmd)
		free(cmd);
	rl_clear_history();
	return (0);
}
