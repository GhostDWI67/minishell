/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwianni <dwianni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 14:52:30 by dwianni           #+#    #+#             */
/*   Updated: 2025/03/08 18:58:20 by dwianni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/******************************************************************************
Main

cat out1 out2 out3 | grep out
test >t1 > t2 >>t3 >> t4 <t5 <   t6 <<t7 <<     t8 "<<   t8"
echo " | " 		| grep ' |	 ' | 	echo " | " | grep ' | ' ||
test1|test2 est NOK

******************************************************************************/
int	main(void)
{
	char	*input;
	char	*input2;
	t_list	*cmd;
	t_list	*token;
	t_list	*tmp;

	input2 = readline("minishell $");
	input = NULL;
	if (input2 != NULL)
	{
		printf("%s\n", input2);
		printf("check quote : %d\n", check_quote(input2));
		input = clean_space(input2);
	}
	
	printf("clean input : %s***\n", input);
	
	cmd = parse_cmd(input);
	tmp = cmd;
	while (tmp != NULL)
	{
		printf("parse : %s***\n", (char *)tmp->content);
		tmp = tmp->next;
	}
	tmp = cmd;
	token = parse_token((char *)tmp->content);
	tmp = token;
	while (tmp != NULL)
	{
		printf("token : %s***\n", ((char *)tmp->content));
		tmp = tmp->next;
	}
	return (0);
}
