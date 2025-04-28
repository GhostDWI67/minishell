/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwianni <dwianni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 14:52:30 by dwianni           #+#    #+#             */
/*   Updated: 2025/04/28 14:16:06 by dwianni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "../include/minishell.h"
#include "../include/minishell.h"

/******************************************************************************
---- A FAIRE DWI ce jour---- :

POUR MEMOIRE : on fait les redirections quoi qu'il arrive et ensuite on lance
	les exec (creation des outfile meme si la fonction n'existe pas)

	
- verifier si leaks avec quote ouverte

- waitpid gerer par rapport au numero de PID pour afficher le bon message en cas
	de pb

	- cas
	cmd |			=> ouvre une ligne de commande
	cmd ||		=> idem mais mettre nimp ca marche la cmd avant/NE PAS GERER ?
	cmd | |			=> unexpected token |
	cmd |||			=> unexpected token ||
	cmd ||||		=> unexpected token ||
	cmd ||||..		=> unexpected token ||
	cat <>  out1	=> affiche out1 NE PAS GERER ?? mais sinon, c'est 
		assez simple
- tous les free a revoir

EN COURS !!!!!!
- gerer la remise sur les bons fd en fin de cycle pour ne pas avoir de fd ouvert
	dans les childs + gerer aussi celui du HEREDOC qui traine dans les childs OK
	mais un peu merdique avec plein de close, voir si on peut faire mieux

- EXPAND
	- gerer quand EXPAND ressort NULL
	- reste a gerer les trim entre $TEST et "$TEST"
	- EXPAND sur le HEREDOC, fait des trucs bizarre, a tester avec bash
	- ajouter les exemples d'Expand qui sont geres

- SIGNAUX

- gerer les valeurs d'exit ou du message d'erreur => parametre exit_code
		integrer pour $? => voir dans Expand

- leak quand ligne vide (juste ENTER)
	=> voir comment on gerer la ligne vide, on ne devrait pas lancer la suite ??
	A VERIFIER J AI UN DOUTE AVEC SANITIZE / tester avec VALGRIND

- HEREDOC
	- voir comment on archive l'historique avec le HEREDOC comme dans bash,
		pour l'instant pas pareil

- Dans PARENTS, gerer le waitpid pour recuperer les exit code

- INTEGRATION des Built-In
	- si cde seul, a lancer au niveau parent sinon en mode child
	- fonction qui gere si c'est un built-in : OK
	- fonction qui lance dans parent (gestion des reidrection a faire) : OK
	- fonction qui lance dans child : OK

- LEAK dans child abec les BI

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
- TEST="ls -l" ne fonctionne pas => il faut expand
	il faut expand apres le lexer au moment ou on a la liste des ARGS ou faire
	un expand avant de lexer => meilleur solution a priori
- Manque le expand des redirections
- Test qvec es vqriqbles d'environnement suivamtes
	TEST=ls -l
	TEST3=   out1    
	TEST2=out1
	TEST4=     out1    out2 

1) finir integration built in
2) expand mettre les exemples geres + faire le dernier + $?
2a) mettre a la norme les modfis + nettoyer les print de debug sauf la sortie
	propre
3) exit code dans parents
4) signaux
5) shell level
6) gerer les leaks et verifier les fd ouverts avec valgrind



et ca sera deja tres bien :)))!
******************************************************************************/

/******************************************************************************
---- A FAIRE ---- :

DWI - differentes redirections
DWI - free des structures
MAX - gestion des variables d'environnememt
- gestion de $?
- signaux ctrl +c, ctrl + d, ctrl + \ (rien)
DWI - traiter la ligne de commande vide
- leak memory et free
- mode intercatif ?
MAX - built in :
	X echo avec -n
	- cd relatif et absolue path
	X pwd
	X export
	- unset
	X env
	- exit
- gerer les erreurs possibles quand une fonction decone + Tester

A FAIRE EN DETAIL // point bloquant actuel // a finir :


******************************************************************************/

/******************************************************************************
CHATGPT : 
en francais  construire en pseudo code un lexer, un parser, un AST 
et un interpreteur d'AST pour un shell

Main

Test a faire :
cat out1 out2 out3 | grep out
    >   t1    test >t1 >   t2 >>t3 >>   t4 <t5 <   t6 <<t7   <<   t8  "<<   t8"
echo " | " 		| grep ' |	 ' | 	echo " | " | grep ' | '
test1|test2
ping -c 5 google.com | grep rtt
cat        out1              out2 |        grep               Out
ls -l | cat out1 | grep Out
ls -l |ls -l |ls -l |ls -l |ls -l |cat out1 | grep Out
cat out1 | grep Out |wc -l | ls -la
ls | ls -l | grep out

CA COINCE : !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

| grep ls : 1er token = | pas bien gere =>pb dans le check des token


---- FAIT ----
1) on lit la ligne de commande => A FAIRE : free la ligne, 
	utiliser GNL à la place ?
2) check les quote : OK
3) clean les espaces devant les redirections
4) lexing pour creer les token
5) analyse les token pour creer les args et les redirections
6) on transforme les listes de token vers un tableau de commande et de
	redirection + pipe dans une struct command : OK
7) Pipe mutliple : OK
8) creer une fonction pour la gestion des erreurs => passe en para le texte et
	la valeur du return : OK ??, a voir pour ajouter du free ??
9) historique et rappel : OK
10) commande simple OK
11) pipe OK
12) > OK >> OK < OK
13) HEREDOC OK
14) EXPAND a priori OK sauf trim des variables d'ENV
15) restera les signaux a traiter;
******************************************************************************/

/******************************************************************************
---- A FAIRE ---- :

DWI - differentes redirections
DWI - free des structures
MAX - gestion des variables d'environnememt
- gestion de $?
- signaux ctrl +c, ctrl + d, ctrl + \ (rien)
DWI - traiter la ligne de commande vide
- leak memory et free
- mode intercatif ?
MAX - built in :
	X echo avec -n
	- cd relatif et absolue path
	X pwd
	X export
	- unset
	X env
	- exit
- gerer les erreurs possibles quand une fonction decone + Tester

A FAIRE EN DETAIL // point bloquant actuel // a finir :


******************************************************************************/

/******************************************************************************
A FAIRE :
MAX : 	- implementer la solution lexer expand lexer parsing
		- shell lvl
		- SIGNAUX

DOM : 	- $?
		- recuperer les exit code du child et des BI dans parents

******************************************************************************/


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
	int		i;

	if (cmd->input != NULL)
	{
		cmd->nb_simple_cmd = check_token_nb_cmd(cmd->token);
		cmd->tab_cmd = malloc(sizeof(t_command) * cmd->nb_simple_cmd);
		if (cmd->tab_cmd == NULL)
			return (1); //voir ce qu'il faudrait faire si malloc echoue??
		parsing(cmd);
		//display_simple_cmd(cmd);//affiche les cmd simple***********
		i = 0;
		while (i < cmd->nb_simple_cmd)
		{
			cmd->tab_cmd[i].tab_args = args_to_tab(cmd->tab_cmd[i].args,
					cmd->env);
			i++;
		}
		cmd->tab_path = ft_split(ft_getenv("PATH", cmd->env), ':');
		build_hd_pipe(cmd);
		redir_mgt(cmd);
		//environ = ft_lst_to_arr(cmd->env);
		f_pipe(cmd, environ);
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
	cmd = malloc(sizeof(t_cmd_line) * 1);
	if (cmd == NULL)
		return (1);
	init_env(cmd, environ);
	while (1)
	{
		environ = ft_lst_to_arr(cmd->env);
		cmd->err_nb = 0;
		main_input_mgt(cmd);
		//display_token(cmd);//Affiche les token***********
		if (cmd->err_nb == 0)
		{
			main_init(cmd);
			main_exec_mgt(cmd, environ);
			main_free_mgt(cmd);
			//printf("ON SORT PROPRE !!!---------------------------\n");
		}
	}
	rl_clear_history();
	return (0);
}

/* main de test pour expand */
/*
int	main(void)
{
	t_expand	*s;

	while (1)
	{
		s = malloc(sizeof(t_expand) * 1);
		s->input = NULL;
		s->output = NULL;
		s->env_name = NULL;
		s->input = readline("minishell$ ");
		expand(s);
		printf("OUTPUT :%s\n", s->output);
		if (s->input != NULL)
			free(s->input);
		if (s->output != NULL)
			free(s->output);
		if (s->env_name != NULL)
			free(s->env_name);
		free(s);
	}
}
*/

/*
int main(void)
{
	char	*s = "      to          to      ";

	printf("%s", ft_strtrim(s, " "));
}
*/