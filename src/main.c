/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwianni <dwianni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 14:52:30 by dwianni           #+#    #+#             */
/*   Updated: 2025/02/24 18:50:51 by dwianni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/******************************************************************************
Main
******************************************************************************/
int	main()
{
	char *input;
	t_list	*data;

	input = readline("minishell $");
	if (input != NULL)
	{
		printf("%s\n", input);
		printf("check quote : %d\n", check_quote(input));
	}
	data = parse_cmd(input);
	while (data != NULL)
	{
		printf("parse : %s\n", (char *)data->content);
		data = data->next;
	}
	return (0);
}
