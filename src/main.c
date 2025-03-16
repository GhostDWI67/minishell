/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwianni <dwianni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 14:52:30 by dwianni           #+#    #+#             */
/*   Updated: 2025/03/16 15:19:40 by dwianni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/******************************************************************************
A FAIRE :
- expend ; ls et "ls" doit idem et pas "ls "
- pipe multiple
- historique + rappel
- gerer les $ dans les quotes '$qwe' ne fait rien mais "$qwe" met le contenu de
	qwe
- differentes redirections
- gestion des variables d'environne;emt
- gestion de $?
- signaux ctrl +c, ctrl + d, ctrl + \ (rien)
- traiter la ligne de commande vide
- mode intercatif ?
- cat out1 et cat out1 <out2
- built in :
	- echo avec -n
	- cd reltif et absolue path
	- pwd
	- export
	- unset
	- env
	- exit
- gerer les erreurs possibles quand une fonction decone

A FAIRE EN DETAIL :
- fonction f_pipe a mette a la norme
- agglomerer le main

******************************************************************************/

/******************************************************************************
Main


Test a faire :
cat out1 out2 out3 | grep out
    >   t1    test >t1 >   t2 >>t3 >>   t4 <t5 <   t6 <<t7   <<   t8  "<<   t8"
echo " | " 		| grep ' |	 ' | 	echo " | " | grep ' | ' ||
test1|test2
ligme sans rien    test??
ping -c 5 google.com | grep rrt
cat        out1              out2 |        grep               Out

1) on lit la ligne de commande => A FAIRE : free la ligne, 
	utiliser GNL à la place ?
2) check les quote
3) clean les espaces devant les redirections
4) parse la ligne de commande en commande simple => A FAIRE : penser à free
5) chaque commande simple est parsée en token => A FAIRE : penser à free
6) on transforme les listes de token vers un tableau de commande et de
	redirection + pipe dans une struct command
7) A FAIRE :
	- PIPEX et traitements des redirections ??
******************************************************************************/
static void	init(t_cmd_line	*cmd)
{
	t_list		*tmp;

	cmd->input = readline("minishell $");
	if (cmd->input != NULL)
	{
		printf("original input : %s***\n", cmd->input);
		printf("check quote : %d\n", check_quote(cmd->input));
		clean_space(cmd->input);
	}
	printf("clean input : %s***\n", cmd->input);
	cmd->simple_cmd = parse_cmd(cmd->input);
	tmp = cmd->simple_cmd;
	while (tmp != NULL)
	{
		printf("parse in simple cmd: %s***\n", (char *)tmp->content);
		tmp = tmp->next;
	}
	tmp = cmd->simple_cmd;
	cmd->nb_simple_cmd = ft_lstsize(tmp);
	printf("nb simple cmd %d\n", cmd->nb_simple_cmd);
	printf("FIN DE L'INIT\nResultat de la ligne de commande\n");
	printf("*************************************\n\n\n");
}

int	main(void)
{
	int			i;
	t_list		*token;
	extern char	**environ;
	t_cmd_line	*cmd;

	cmd = malloc(sizeof(t_cmd_line) * 1);
	if (cmd == NULL)
		return (1);
	init(cmd);

	cmd->tab_cmd = malloc(sizeof(t_command) * cmd->nb_simple_cmd);
	if (cmd->tab_cmd == NULL)
		return (0);
	i = 0;
	while (i < cmd->nb_simple_cmd)
	{
		token = parse_token((char *)cmd->simple_cmd->content);
		cmd->tab_cmd[i] = lexer(token);
		cmd->tab_cmd[i].tab_args = args_to_tab(cmd->tab_cmd[i].args);
		i++;
		cmd->simple_cmd = cmd->simple_cmd->next;
	}
	cmd->tab_path = ft_split(getenv("PATH"), ':');
	f_pipe(cmd, environ);
	return (0);
}
