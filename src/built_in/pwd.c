/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpalisse <mpalisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 12:25:22 by mpalisse          #+#    #+#             */
/*   Updated: 2025/07/03 15:03:32 by mpalisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/******************************************************************************
display the current working dir in the STDOUT
Return 0 si reussis et 1 si erreur
******************************************************************************/
int	pwd(t_cmd_line *cmd, int in_child)
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, PATH_MAX))
	{
		printf("%s\n", cwd);
		if (in_child == 1)
			free_cmd_line_exit(cmd);
		return (0);
	}
	else
	{
		perror("pwd failed");
		if (in_child == 1)
			free_cmd_line_exit(cmd);
		return (1);
	}
}
