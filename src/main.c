/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpalisse <mpalisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 14:52:30 by dwianni           #+#    #+#             */
/*   Updated: 2025/05/07 13:21:01 by mpalisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "../include/minishell.h"
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

******************************************************************************/

int	g_signal;

static void	main_init(t_cmd_line	*cmd)
{
	cmd->fd_saved_stdout = dup(STDOUT_FILENO);
	if (cmd->fd_saved_stdout == -1)
	{
		msg_error(ERM_STD, ERN_STD);
	}
	cmd->fd_saved_stdin = dup(STDIN_FILENO);
	if (cmd->fd_saved_stdin == -1)
	{
		msg_error(ERM_STD, ERN_STD);
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
		//environ = ft_lst_to_arr(cmd->env);
		f_exec(cmd, environ);
		//free_tab_char(environ);
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
		msg_error(ERM_STD, ERN_STD);
	else
		close(cmd->fd_saved_stdout);
	if (dup2(cmd->fd_saved_stdin, STDIN_FILENO) == -1)
		msg_error(ERM_STD, ERN_STD);
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
	(void)argv;
	g_signal = 0;
	signals_handler();
	cmd = malloc(sizeof(t_cmd_line) * 1);
	if (cmd == NULL)
		return (1);
	init_env(cmd, environ);
	while (1)
	{
		environ = ft_lst_to_arr(cmd->env);
		cmd->err_nb = 0;
		main_input_mgt(cmd);
		if (cmd->err_nb == 0)
		{
			main_init(cmd);
			g_signal = 1;
			main_exec_mgt(cmd, environ);
			g_signal = 0;
			main_free_mgt(cmd);
		}
	}
	rl_clear_history();
	return (0);
}

/*
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>

// Handler pour les signaux
void handle_signal(int sig) {
    printf("Reçu le signal : %d\n", sig);
    fflush(stdout);  // Forcer l'affichage immédiat
}

int main() {
    struct sigaction sa;
    
    // Nettoyage et configuration de la structure sigaction
    memset(&sa, 0, sizeof(sa));
    sa.sa_handler = handle_signal;
    sa.sa_flags = SA_RESTART;  // Pour que les appels comme fgets ne soient pas interrompus

    // Installation des gestionnaires de signaux
    sigaction(SIGINT, &sa, NULL);   // Ctrl-C
    sigaction(SIGQUIT, &sa, NULL);  // Ctrl-/
	sigaction(EOF, &sa, NULL);  // Ctrl-/

    printf("Programme en attente (Ctrl-C, Ctrl-/, Ctrl-D pour tester)...\n");

    char buffer[100];
    while (1) {
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            printf("Fin de l'entrée détectée (probablement Ctrl-D)\n");
            break;
        }
        printf("Vous avez entré : %s", buffer);
    }

    return 0;
}
*/