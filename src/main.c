/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpalisse <mpalisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 14:52:30 by dwianni           #+#    #+#             */
/*   Updated: 2025/05/27 16:16:16 by mpalisse         ###   ########.fr       */
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
6) parsing : analyse les token pour creer les args et les redirections(avec expand)
7) rebuild les list d'ARG de chaque commande pour expand les $VAR
8) on reconstruit ls list d'ARG expand
9) on lance l'execution 
	- tableau d'ARG de fonction
	- creation des pipes
	- lancememt des Built_In et des execve dans processus child
		avec gestion des in/out file, cde qui n'existe pas, ...

******************************************************************************/

/******************************************************************************
---- A FAIRE ---- :

- signaux ctrl +c, ctrl + d, ctrl + \ (rien)
- leak memory et free
- gerer les erreurs possibles quand une fonction decone + Tester
- verifier si leaks avec quote ouverte
- tous les free a revoir
- gerer la remise sur les bons fd en fin de cycle pour ne pas avoir de fd ouvert
	dans les childs + gerer aussi celui du HEREDOC qui traine dans les childs OK
	mais un peu merdique avec plein de close, voir si on peut faire mieux
- SIGNAUX
- gerer les valeurs d'exit ou du message d'erreur => parametre exit_code
		integrer pour $? => voir dans Expand
- leak quand ligne vide (juste ENTER)
	=> voir comment on gerer la ligne vide, on ne devrait pas lancer la suite ??
	A VERIFIER J AI UN DOUTE AVEC SANITIZE / tester avec VALGRIND
- INTEGRATION des Built-In
	- si cde seul, a lancer au niveau parent sinon en mode child
	- fonction qui gere si c'est un built-in : OK
	- fonction qui lance dans parent (gestion des reidrection a faire) : OK
	- fonction qui lance dans child : OK
- LEAK dans child abec les BI
- gerer les leaks et verifier les fd ouverts avec valgrind


******************************************************************************/

/******************************************************************************
REPARTITION DES TACHES :
MAX : 	- implementer la solution lexer expand lexer parsing
		- shell lvl
		- SIGNAUX
MAX - built in :
	X echo avec -n					CHILD !!!!!
	X - cd relatif et absolue path 	PARENT
	X pwd							NA
	X export						PARENT
	X - unset						PARENT
	X env							NA
	- exit							NA
		
DOM : 	- tester avec sanitize et valgrind pour verifier les fd
			cat <out1 <out2 | grep out | wc -l >test.txt
			reste des fd ouvert

		- regarder les SIGNAUX

A DEBUG
	- expand du heredoc a revoir, faudrait pas expand => a modifier SAMEDI PROCHAIN   FAIT
	- msg_error : rajouter exit_code ?? partout ?? => partout on met le cmd->exit_code
		dans lexer-check reste 2 msg_error / heredoc 1 msg_error/ 
	- gestion des exit code si on a des NULL dans la structure ?? =>SAMEDI
	- BI leaks dans child => fonction free allegee ?? A CREER et TESTER
	- verifier les fd qui reste ouvert => SAMEDI PROCHAIN

ft_putstr_fd("TOTO passe ici\n", 2);

valgrind --track-origins=yes --track-fds=yes --trace-children=yes ./minishell
valgrind --leak-check=full --show-leak-kinds=all --suppressions=leaks.supp

******************************************************************************/

int	g_signal;

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

static int	main_exec_mgt(t_cmd_line *cmd, char **environ)
{
	char	*path;

	if (cmd->input != NULL)
	{
		cmd->nb_simple_cmd = check_token_nb_cmd(cmd->token);
		cmd->tab_cmd = malloc(sizeof(t_command) * cmd->nb_simple_cmd);
		if (cmd->tab_cmd == NULL)
			return (1);
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

static void	main_free_mgt(t_cmd_line *cmd)
{
	int	i;

	i = 0;
	while (i < cmd->nb_simple_cmd)
	{
		ft_close(cmd->tab_cmd[i].fd_infile);
		ft_close(cmd->tab_cmd[i].fd_outfile);
		ft_close(cmd->tab_cmd[i].hd_pipe[0]);
		ft_close(cmd->tab_cmd[i].hd_pipe[1]);
		i++;
	}
	if (dup2(cmd->fd_saved_stdout, STDOUT_FILENO) == -1)
		cmd->exit_code = msg_error(ERM_STD, ERN_STD);
	else
		close(cmd->fd_saved_stdout);
	if (dup2(cmd->fd_saved_stdin, STDIN_FILENO) == -1)
		cmd->exit_code = msg_error(ERM_STD, ERN_STD);
	else
		close(cmd->fd_saved_stdin);
	if (cmd->input != NULL)
	{
		free_cmd_line(cmd);
		cmd = NULL;
	}
}

int	main(int argc, char **argv, char **environ)
{
	t_cmd_line	*cmd;

	(void)argc;
	cmd = malloc(sizeof(t_cmd_line) * 1);
	if (cmd == NULL)
		return (1);
	init_cmd(cmd);
	if (init_env(cmd, environ, argv) == 1)
		free_exit(cmd, false, 1);
	while (1)
	{
		cmd->tab_env = ft_lst_to_arr(cmd->env);
		cmd->err_nb = 0;
		main_input_mgt(cmd);
		//ft_putstr_fd("Point 1\n", 2);//
		if (cmd->err_nb == 0)
		{
			//ft_putstr_fd("Point 2\n", 2);//
			main_init(cmd);
			//ft_putstr_fd("Point 2-bis\n", 2);//
			setup_sigs_exec();
			main_exec_mgt(cmd, cmd->tab_env);
			setup_sigs_handler();
			//ft_putstr_fd("Point 3\n", 3);//
			main_free_mgt(cmd);
			//ft_putstr_fd("Point 4\n", 2);//
		}
		else
		{
			//ft_putstr_fd("Point 5\n", 2);//
			if (cmd->token)					//pb avec redir seule
				token_clear(&cmd->token);	//pb avec redir seule
			free(cmd->tab_env);
		}
	}
	return (0);
}
