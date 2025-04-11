/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwianni <dwianni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 14:52:30 by dwianni           #+#    #+#             */
/*   Updated: 2025/04/11 16:56:22 by dwianni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "../include/minishell.h"
#include "../include/minishell.h"

/******************************************************************************
---- A FAIRE DWI ce jour---- :
- verifier si leaks avec quote ouverte
- pb a debugger avec le clean space idem que pour le check quote ??
- cat <out <out1 ne doit pas s'executer quand out n'existe pas => integrer
	les valeurs de defaut
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
- revoir le parsing pour les version tout colles et < < out1
	- nouveau parsing parse les token : OK
	- check si on a un | à la fin de la commande => on refait un input 
		(a l'infini)) : OK
	- on teste d'abord si le lexing est OK et ensuite on check si besoin de
		rajouter un input, mais on stock la chaine avec l'input avec le defaut
		de token
	A FAIRE :
		- testeur de token : OK
		- testeur de | final + intégration nouvelle demande OK
		- calcul du nombre de commande OK
		- dans l'ordre, on test token si NOK on enregistre la commande sinon, on
			continue avec nouveau pipe et on boucle ... OK
		- integration dans simple cmd pour raccrocher les wagons a l'ancienne
			version OK
		- nettoyer les vestiges OK
		- mettre le tout à la norme OK

- gerer la remise sur les bons fd en fin de cycle pour ne pas avoir de fd ouvert
	dans les childs + gerer aussi celui du HEREDOC qui traine dans les childs OK
	mais un peu merdique avec plein de close, voir on peut faire mieux

- EXPAND
- SIGNAUX

et ca sera deja tres bien :)))!
******************************************************************************/

/******************************************************************************
---- A FAIRE ---- :
- expend ; ls et "ls" doit idem et pas "ls "
- gerer les $ dans les quotes '$qwe' ne fait rien mais "$qwe" met le contenu de
	qwe
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
- nettoyer des white space avec les redirection <   < out1 est NOK

******************************************************************************/

/******************************************************************************
CHATGPT : 
en francais  construire en pseudo code un lexer, un parser, un AST 
et un interpreteur d'AST pour un shell

Main

Test a faire :
cat out1 out2 out3 | grep out
    >   t1    test >t1 >   t2 >>t3 >>   t4 <t5 <   t6 <<t7   <<   t8  "<<   t8"
echo " | " 		| grep ' |	 ' | 	echo " | " | grep ' | ' ||
test1|test2
ping -c 5 google.com | grep rtt
cat        out1              out2 |        grep               Out
ls -l | cat out1 | grep Out
ls -l |ls -l |ls -l |ls -l |ls -l |cat out1 | grep Out
cat out1 | grep Out |wc -l | ls -la
ls | ls -l | grep out

cat <out1 <out2 <<EOF >t1 >t2   Pas OK
cat <out1 <<EOF <out2 >t1 >t2	Pas OK

>out20 | >out21 | cat out1

cat <out1|grep Out|wc -l

CA COINCE : !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
cat <out1 <<EOF >t1    Fais crash => OK mais passer par adresse
cqt out1 | grep Out		Fais palnter les dup => il faut ne pas gerer les 
	dup si une des fonctions deconne ou gerer avec le resultat des exits

tester un executable qvec un chemin relatif => tester de base avec le chemin
	avant le PATH

---- FAIT ----
1) on lit la ligne de commande => A FAIRE : free la ligne, 
	utiliser GNL à la place ?
2) check les quote : OK
3) clean les espaces devant les redirections : OK?, tester cat <   <  out1
	==> A RETRAVAILLER car genere cat <<out1
4) parse la ligne de commande en commande simple : OK
5) chaque commande simple est parsée en token : OK
6) on transforme les listes de token vers un tableau de commande et de
	redirection + pipe dans une struct command : OK
7) Pipe mutliple : OK
8) creer une fonction pour la gestion des erreurs => passe en para le texte et
	la valeur du return : OK ??, a voir pour ajouter du free ??
9) historique et rappel : OK
10) commande simple OK
11) pipe OK
12) > OK >> OK < OK
******************************************************************************/
/*
static void	main_init(t_cmd_line	*cmd)
{
	cmd->fd_saved_stdout = dup(STDOUT_FILENO);
	if (cmd->fd_saved_stdout == -1)
		msg_error(ERM_STD, ERN_STD);
	cmd->fd_saved_stdin = dup(STDIN_FILENO);
	if (cmd->fd_saved_stdin == -1)
		msg_error(ERM_STD, ERN_STD);
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
		i = 0;
		while (i < cmd->nb_simple_cmd)
		{
			cmd->tab_cmd[i].tab_args = args_to_tab(cmd->tab_cmd[i].args);
			i++;
		}
		//display_simple_cmd(cmd);
		cmd->tab_path = ft_split(getenv("PATH"), ':');
		build_hd_pipe(cmd);
		redir_mgt(cmd);
		f_pipe(cmd, environ);
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
	close(cmd->fd_saved_stdout);
	if (dup2(cmd->fd_saved_stdin, STDIN_FILENO) == -1)
		msg_error(ERM_STD, ERN_STD);
	close(cmd->fd_saved_stdin);
	if (cmd->input != NULL)
	{
		free_cmd_line(cmd);
		cmd = NULL;
	}
}

int	main(void)
{
	extern char	**environ;
	t_cmd_line	*cmd;

	while (1)
	{
		cmd = malloc(sizeof(t_cmd_line) * 1);
		if (cmd == NULL)
			return (1);
		cmd->err_nb = 0; // A voir où on l'init
		main_input_mgt(cmd);
		if (cmd->err_nb == 0)
		{
			main_init(cmd);
			main_exec_mgt(cmd, environ);
			main_free_mgt(cmd);
		}
	}
	rl_clear_history();
	return (0);
}
*/

int	main(void)
{
	t_expand	*s;
	
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
