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

******************************************************************************/
int	main(void)
{
	char	*input;
	t_list	*cmd;
	t_list	*token;
	t_list	*tmp;

	input = readline("minishell $");
	if (input != NULL)
	{
		printf("original input : %s***\n", input);
		printf("check quote : %d\n", check_quote(input));
		clean_space(input);
	}
	
	printf("clean input : %s***\n", input);
	
	cmd = parse_cmd(input);
	tmp = cmd;
	while (tmp != NULL)
	{
		printf("parse in simple cmd: %s***\n", (char *)tmp->content);
		tmp = tmp->next;
	}
	
	while (cmd != NULL)
	{
		token = parse_token((char *)cmd->content);
		tmp = token;
		while (tmp != NULL)
		{
			printf("token :%s***\n", ((char *)tmp->content));
			tmp = tmp->next;
		}
		cmd = cmd->next;
	}
	
	return (0);
}
