/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwianni <dwianni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 14:52:30 by dwianni           #+#    #+#             */
/*   Updated: 2025/03/30 19:50:21 by dwianni          ###   ########.fr       */
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
- wait gerer par rapport au numero de PID pour afficher le bon message en cas
	de pb
- nettoyer des white space avec les redirection <   < out1 est NOK
- melange des < et << ca deconne PB de dup2 A revcoir suite a la mise a la
	norme ca deconne voir redir mgt
- tous les free a revoir
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
DWI OK- traiter la ligne de commande vide
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
CHAT : 
en francais  construire en pseudo code un lexer, un parser, un AST 
et un interpreteur d'AST pour un shell

Main

Test a faire :
cat out1 out2 out3 | grep out
    >   t1    test >t1 >   t2 >>t3 >>   t4 <t5 <   t6 <<t7   <<   t8  "<<   t8"
echo " | " 		| grep ' |	 ' | 	echo " | " | grep ' | ' ||
test1|test2
ligme sans rien    test??
ping -c 5 google.com | grep rtt
cat        out1              out2 |        grep               Out
ls -l | cat out1 | grep Out
ls -l |ls -l |ls -l |ls -l |ls -l |cat out1 | grep Out
cat out1 | grep Out |wc -l | ls -la
ls | ls -l | grep out

cat <out1 <out2 <<EOF >t1 >t2   Pas OK
cat <out1 <<EOF <out2 >t1 >t2	Pas OK

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

static void	main_input_mgt(t_cmd_line	*cmd)
{
	t_list		*tmp;

	cmd->input = readline("minishell$");
	if (cmd->input != NULL)
	{
		if (cmd->input[0] != '\0' || ws_check(cmd->input) != 0)
			add_history(cmd->input);
		if (check_quote(cmd->input) != 0)
			cmd->err_nb = msg_inf(ERM_QUOTE, ERN_QUOTE);
		if (ws_check(cmd->input) != 0 && cmd->err_nb == 0)
		{
			clean_space(cmd->input);
			printf("clean input : %s***\n", cmd->input);//a retirer
			cmd->simple_cmd = parse_cmd(cmd->input);
			tmp = cmd->simple_cmd;
			cmd->nb_simple_cmd = ft_lstsize(tmp);
			printf("*************************************\n\n\n");//a retirer
		}
	}
	else
	{
		cmd->err_nb = msg_inf(ERM_INPUT_NULL, ERN_INPUT_NULL);
	}
}

static int	main_exec_mgt(t_cmd_line *cmd, t_list *token, char **environ)
{
	int		i;
	t_list	*tmp;

	if (cmd->input != NULL)
	{
		cmd->tab_cmd = malloc(sizeof(t_command) * cmd->nb_simple_cmd);
		if (cmd->tab_cmd == NULL)
			return (1); //voir ce qu'il faudrait faire si malloc echoue??
		i = 0;
		tmp = cmd->simple_cmd;
		while (i < cmd->nb_simple_cmd)
		{
			token = parse_token((char *)cmd->simple_cmd->content);
			cmd->tab_cmd[i] = lexer(token);
			cmd->tab_cmd[i].tab_args = args_to_tab(cmd->tab_cmd[i].args);
			i++;
			cmd->simple_cmd = cmd->simple_cmd->next;
		}
		cmd->simple_cmd = tmp;
		cmd->tab_path = ft_split(getenv("PATH"), ':');
		build_hd_pipe(cmd);
		redir_mgt(cmd);
		f_pipe(cmd, environ);
	}
	return (0);
}

static void	main_free_mgt(t_cmd_line *cmd, t_list *token)
{
	int	i;

	i = 0;
	while (i < cmd->nb_simple_cmd)
	{
		ft_close(cmd->tab_cmd[i].fd_infile);
		ft_close(cmd->tab_cmd[i].fd_outfile);
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
		free(token);
		token = NULL;
	}
}

int	main(void)
{
	t_list		*token;
	extern char	**environ;
	t_cmd_line	*cmd;

	token = NULL;
	while (1)
	{
		cmd = malloc(sizeof(t_cmd_line) * 1);
		if (cmd == NULL)
			return (1);
		main_init(cmd);
		main_input_mgt(cmd);
		if (cmd->err_nb == 0)
		{
			main_exec_mgt(cmd, token, environ);
			main_free_mgt(cmd, token);
		}
	}
	rl_clear_history();
	return (0);
}
