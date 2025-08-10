/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwianni <dwianni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 14:52:30 by dwianni           #+#    #+#             */
/*   Updated: 2025/08/10 17:35:02 by dwianni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	g_signal;

/******************************************************************************
Init the fd IN/OUT
******************************************************************************/
static void	main_init(t_cmd_line *cmd)
{
	cmd->fd_saved_stdout = dup(STDOUT_FILENO);
	if (cmd->fd_saved_stdout == -1)
	{
		cmd->exit_code = msg_error(ERM_STD, ERN_STD);
	}
	cmd->fd_saved_stdin = dup(STDIN_FILENO);
	if (cmd->fd_saved_stdin == -1)
	{
		cmd->exit_code = msg_error(ERM_STD, ERN_STD);
	}
	cmd->err_nb = 0;
}

/******************************************************************************
Exec part of the main
******************************************************************************/
static int	main_exec_mgt(t_cmd_line *cmd, char **environ)
{
	char	*path;

	if (cmd->input != NULL)
	{
		cmd->nb_simple_cmd = check_token_nb_cmd(cmd->token);
		cmd->tab_cmd = malloc(sizeof(t_command) * cmd->nb_simple_cmd);
		if (cmd->tab_cmd == NULL)
			return (cmd->exit_code = msg_inf(ERM_MALLOC, ERN_MALLOC), 1);
		init_tab_cmd(cmd->tab_cmd);
		parsing(cmd);
		parsing_args(cmd);
		cmd_arg_to_tab(cmd);
		path = ft_getenv("PATH", cmd->env);
		if (path != NULL)
			cmd->tab_path = ft_split(path, ':');
		else
			cmd->tab_path = NULL;
		build_hd_pipe(cmd);
		redir_mgt(cmd);
		if (g_signal != SIGINT)
		{
			f_exec(cmd, environ);
		}
	}
	return (0);
}

/******************************************************************************
Sub main loop
******************************************************************************/
static void	main_loop(t_cmd_line *cmd)
{
	cmd->tab_env = ft_lst_to_arr(cmd->env);
	cmd->err_nb = 0;
	setup_sigs_handler();
	main_input_mgt(cmd);
	if (cmd->err_nb == 0)
	{
		main_init(cmd);
		setup_sigs_exec();
		main_exec_mgt(cmd, cmd->tab_env);
		setup_sigs_handler();
		main_free_mgt(cmd);
	}
	else
	{
		if (cmd->token)
			token_clear(&cmd->token);
		free(cmd->tab_env);
	}
}

/******************************************************************************
MAIN
******************************************************************************/
int	main(int argc, char **argv, char **environ)
{
	t_cmd_line	*cmd;

	(void)argc;
	cmd = malloc(sizeof(t_cmd_line) * 1);
	if (cmd == NULL)
		return (msg_inf(ERM_MALLOC, ERN_MALLOC));
	init_cmd(cmd);
	if (init_env(cmd, environ, argv) == 1)
		free_exit(cmd, false, 1);
	while (1)
	{
		main_loop(cmd);
	}
	return (0);
}
