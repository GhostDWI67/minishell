/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwianni <dwianni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 14:52:30 by dwianni           #+#    #+#             */
/*   Updated: 2025/03/23 18:55:54 by dwianni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "../include/minishell.h"
#include "../include/minishell.h"

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
- traiter la ligne de commande vide
- leak memory et free
- mode intercatif ?
- cat out1 et cat out1 <out2
MAX - built in :
	- echo avec -n
	- cd relatif et absolue path
	- pwd
	- export
	- unset
	- env
	- exit
- gerer les erreurs possibles quand une fonction decone + Tester

A FAIRE EN DETAIL // point bloquant actuel // a finir :
- agglomerer le main
- nettoyer des white space avec les redirection <   < out1 est NOK
- gerer ligne vide ou ligne de commande avec que de wspace

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
******************************************************************************/
static void	init(t_cmd_line	*cmd)
{
	t_list		*tmp;

	write(2, &"hello world00!\n", 15);
	cmd->input = readline("minishell$");
	write(2, &"hello world01!\n", 15);
	if (cmd->input != NULL)
	{
		if (cmd->input[0] != '\0')
			add_history(cmd->input);
		printf("original input : %s***\n", cmd->input);
		//printf("check quote : %d\n", check_quote(cmd->input));
		write(2, &"hello world02!\n", 15);
		clean_space(cmd->input);
		write(2, &"hello world03!\n", 15);
	}
	printf("clean input : %s***\n", cmd->input);
	cmd->simple_cmd = parse_cmd(cmd->input);
	tmp = cmd->simple_cmd;
	while (tmp != NULL)
	{
		//printf("parse in simple cmd: %s***\n", (char *)tmp->content);
		tmp = tmp->next;
	}
	tmp = cmd->simple_cmd;
	cmd->nb_simple_cmd = ft_lstsize(tmp);
	//printf("nb simple cmd %d\n", cmd->nb_simple_cmd);
	//printf("FIN DE L'INIT\nResultat de la ligne de commande\n");
	printf("*************************************\n\n\n");
}

int	main(void)
{
	int			i;
	t_list		*token;
	extern char	**environ;
	t_cmd_line	*cmd;
	t_list		*tmp;

	while(1) 
	{
		cmd = malloc(sizeof(t_cmd_line) * 1);
		if (cmd == NULL)
			return (1);
		init(cmd);
		write(2, &"hello world1!\n", 14);
		cmd->tab_cmd = malloc(sizeof(t_command) * cmd->nb_simple_cmd); 
		if (cmd->tab_cmd == NULL)
			return (0);//voir ce qu'il faudrait faire si malloc echoue, on doit rester 
		i = 0;
		tmp = cmd->simple_cmd;
		/* ----------------   lexing et tab_args ---------------------------*/
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
		//write(2, &"hello world2!\n", 14);
		redir_mgt(cmd);
		//write(2, &"hello world3!\n", 14);
		f_pipe(cmd, environ);
		//write(2, &"hello world40!\n", 15);
		free_cmd_line(cmd);
		cmd = NULL;
		free(token);
		token = NULL;
		ft_putnbr_fd(STDOUT_FILENO,2);
		write(2, &"\n", 1);
		write(2, &"hello world50!\n", 15);
	}
	rl_clear_history();
	return (0);
}

/*
int	main(void)
{
	//t_list	*test1;
	//t_list	*test2;
	//t_list	*test3;
	t_list	*start;
	t_list	*tmp;

	//test1 = ft_lstnew(ft_strndup("test1",1 , 4));
	//test2 = ft_lstnew(ft_strndup("test2",1 , 4));
	//test3 = ft_lstnew(ft_strndup("test3",1 , 4));
	start = NULL;
	ft_lstadd_back(&start, ft_lstnew(ft_strndup("test2",1 , 4)));
	ft_lstadd_back(&start, ft_lstnew(ft_strndup("test2",1 , 4)));
	ft_lstadd_back(&start, ft_lstnew(ft_strndup("test3",1 , 4)));
	tmp = start;
	while (tmp != NULL)
	{
		printf("%s\n",(char *)tmp->content);
		tmp = tmp->next;
	}
	ft_lstclear(&start,free);
	return (0);
}
*/

/*
int	main(void)
{
	t_list	*test1;
	t_list	*test2;
	t_list	*test3;
	t_list	*start;
	
	test1 = ft_lstnew(ft_strndup("test1",1 , 4));
	test2 = ft_lstnew(ft_strndup("test2",1 , 4));
	test3 = ft_lstnew(ft_strndup("test3",1 , 4));
	start = test1;
	ft_lstadd_back(&start, test2);
	ft_lstadd_back(&start, test3);
	start = test1;
	while (start != NULL)
	{
		printf("%s\n",(char *)start->content);
		start = start->next;
	}
	ft_lstclear(&test1,free);
	return (0);
}
*/