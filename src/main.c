/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwianni <dwianni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 14:52:30 by dwianni           #+#    #+#             */
/*   Updated: 2025/05/31 18:49:10 by dwianni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/******************************************************************************
Comment fonctionne le minishell 

1) initialise l'ENV et on cree une liste chainee de l'ENV
2) on lit la ligne de commande => A FAIRE : free la ligne, 
	utiliser GNL à la place ?
3) check les quote et les tokens bizarre
4) lexing pour creer les token
5) verifie les suite de token non valide
6) parsing : analyse les token pour creer les args et 
	les redirections(avec expand)
7) rebuild les list d'ARG de chaque commande pour expand les $VAR
8) on reconstruit les list d'ARG expand
9) on lance l'execution 
	- tableau d'ARG de fonction
	- creation des pipes
	- lancememt des Built_In et des execve dans processus child
		avec gestion des in/out file, cde qui n'existe pas, ...
******************************************************************************/

/******************************************************************************
	- msg_error : rajouter exit_code ?? partout ?? 
			=> partout on met le cmd->exit_code
		dans lexer-check reste 2 msg_error / heredoc 1 msg_error/ 
	- gestion des exit code si on a des NULL dans la structure ?? =>SAMEDI

valgrind --track-origins=yes --track-fds=yes --trace-children=yes ./minishell
valgrind --leak-check=full --show-leak-kinds=all --suppressions=leaks.supp

******************************************************************************/

int	g_signal;

/******************************************************************************
Init the cmd structure
******************************************************************************/
static void	init_cmd(t_cmd_line *cmd)
{
	cmd->input = NULL;
	cmd->token = NULL;
	cmd->tab_env = NULL;
	cmd->env = NULL;
	cmd->nb_simple_cmd = 0;
	cmd->tab_cmd = NULL;
	cmd->tab_path = NULL;
	cmd->tab_fd = NULL;
	cmd->tab_pid = NULL;
	cmd->cmd_step = 0;
	cmd->fd_saved_stdin = 0;
	cmd->fd_saved_stdout = 0;
	cmd->err_nb = 0;
	cmd->exit_code = 0;
	g_signal = 0;
	setup_sigs_handler();
}

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
		{
			cmd->exit_code = msg_inf(ERM_MALLOC, ERN_MALLOC);
			return (1);
		}
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
		f_exec(cmd, environ);
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
	main_input_mgt(cmd);
	if (cmd->err_nb == 0)
	{
		main_init(cmd);
		setup_sigs_exec();
		main_exec_mgt(cmd, cmd->tab_env);
		//ft_putstr_fd("POINT 3\n", 2);//
		setup_sigs_handler();
		main_free_mgt(cmd);
		//ft_putstr_fd("POINT 4\n", 2);//
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
