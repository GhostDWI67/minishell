/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwianni <dwianni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 14:52:30 by dwianni           #+#    #+#             */
/*   Updated: 2025/03/09 19:15:01 by dwianni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/******************************************************************************
Main

cat out1 out2 out3 | grep out           est OK
    >   t1    test >t1 >   t2 >>t3 >>    t4 <t5 <   t6 <<t7     <<     t8     "<<   t8"    est OK
echo " | " 		| grep ' |	 ' | 	echo " | " | grep ' | ' ||   est OK
test1|test2 est OK
cat out1 out2 out3 | grep out|    >   t1    test >t1 >   t2 >>t3 >>    t4 <t5 <   t6 <<t7     <<     t8     "<<   t8"  |test1|test2 |echo " | " 		| grep ' |	 ' | 	echo " | " | grep ' | ' ||   
ligme sans rien    test??


1) on lit la ligne de commande => A FAIRE : free la ligne, utiliser GNL à la place ?
2) check les quote
3) clean les espaces devant les redirections
4) parse la ligne de commande en commande simple => A FAIRE : penser à free
5) chaque commande simple est parsée en token => A FAIRE : penser à free
6) on transfome les listes de token vers un tableau de commande et de redirection + pipe dans une struct command
7) A FAIRE :
	***- transformer la liste des args en tableau d'args => dans la structure command ?
	- créer un split de l'environnement et surtout du PATH sous forme de tableau => struct cmd_line nota : 
	- fonction qui teste les différents PATH pour faire l'EXEC
	- PIPEX et traitements des redirections ??
******************************************************************************/
int	main(void)
{
	char		*input;
	t_list		*simple_cmd;
	int			nb_simple_cmd;
	int			i;
	t_list		*token;
	t_list		*tmp;
	t_command	*command;

	input = readline("minishell $");
	if (input != NULL)
	{
		printf("original input : %s***\n", input);
		printf("check quote : %d\n", check_quote(input));
		clean_space(input);
	}
	
	printf("clean input : %s***\n", input);
	
	simple_cmd = parse_cmd(input);
	tmp = simple_cmd;
	while (tmp != NULL)
	{
		printf("parse in simple cmd: %s***\n", (char *)tmp->content);
		tmp = tmp->next;
	}
	
	tmp = simple_cmd;
	nb_simple_cmd = ft_lstsize(tmp);
	printf("nb simple cmd %d\n", nb_simple_cmd);
	command = malloc(sizeof(t_command) * nb_simple_cmd);
	if (command == NULL)
		return (0);
	i = 0;
	while (i < nb_simple_cmd)
	{
		token = parse_token((char *)simple_cmd->content);
		command[i] = lexer(token);
		i++;
		simple_cmd = simple_cmd->next;
	}
	return (0);
}


/*
	tmp = token;
	while (tmp != NULL)
	{
		printf("token :%s***\n", ((char *)tmp->content));
		tmp = tmp->next;
	}
*/