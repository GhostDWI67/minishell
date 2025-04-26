/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_built_in.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwianni <dwianni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 13:49:26 by dwianni           #+#    #+#             */
/*   Updated: 2025/04/26 16:41:32 by dwianni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/******************************************************************************
Check if teh command is a built in
Return : BUILTIN_NOT if not or the BUILTIN number
******************************************************************************/
int	is_built_in(char *s)
{
	if (ft_strncmp(s, "echo", ft_strlen(s)) == 0)
		return (BUILTIN_ECHO);
	else if (ft_strncmp(s, "cd", ft_strlen(s)) == 0)
		return (BUILTIN_CD);
	else if (ft_strncmp(s, "pwd", ft_strlen(s)) == 0)
		return (BUILTIN_PWD);
	else if (ft_strncmp(s, "export", ft_strlen(s)) == 0)
		return (BUILTIN_EXPORT);
	else if (ft_strncmp(s, "unset", ft_strlen(s)) == 0)
		return (BUILTIN_UNSET);
	else if (ft_strncmp(s, "env", ft_strlen(s)) == 0)
		return (BUILTIN_ENV);
	else if (ft_strncmp(s, "exit", ft_strlen(s)) == 0)
		return (BUILTIN_EXIT);
	return (BUILTIN_NOT);
}

/******************************************************************************

******************************************************************************/
int	exec_builtin(int bi, t_cmd_line *cmd)
{
	if (bi == BUILTIN_ECHO)
	{
		return (echo(cmd->tab_cmd[cmd->cmd_step].tab_args));
	}
	else if (bi == BUILTIN_CD)
		return (cd(cmd->tab_cmd[cmd->cmd_step].tab_args, &cmd->env));
	else if (bi == BUILTIN_PWD)
		return (pwd());
	else if (bi == BUILTIN_EXPORT)
		return (export(cmd->tab_cmd[cmd->cmd_step].tab_args, &cmd->env));
	else if (bi == BUILTIN_UNSET)
		return (unset(cmd->tab_cmd[cmd->cmd_step].tab_args, &cmd->env));
	else if (bi == BUILTIN_ENV)
		return (env(cmd->env));
	else if (bi == BUILTIN_EXIT)
		return (BUILTIN_EXIT);// a implementer
	return (0);
}