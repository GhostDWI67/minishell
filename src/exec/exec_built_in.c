/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_built_in.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwianni <dwianni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 13:49:26 by dwianni           #+#    #+#             */
/*   Updated: 2025/04/27 14:25:45 by dwianni          ###   ########.fr       */
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
Execute build_in inside a child
******************************************************************************/
void	exec_builtin_c(int bi, t_cmd_line *cmd)
{
	if (bi == BUILTIN_ECHO)
		exit(echo(cmd->tab_cmd[cmd->cmd_step].tab_args));
	else if (bi == BUILTIN_CD)
		exit(cd(cmd->tab_cmd[cmd->cmd_step].tab_args, cmd->env));
	else if (bi == BUILTIN_PWD)
		exit(pwd());
	else if (bi == BUILTIN_EXPORT)
		exit(export(cmd->tab_cmd[cmd->cmd_step].tab_args, &cmd->env));
	else if (bi == BUILTIN_UNSET)
		exit(unset(cmd->tab_cmd[cmd->cmd_step].tab_args, &cmd->env));
	else if (bi == BUILTIN_ENV)
		exit(env(cmd->env));
	else if (bi == BUILTIN_EXIT)
		exit(BUILTIN_EXIT);// a implementer
	exit(0);
}

/******************************************************************************
Execute build-in inside a parent (when it's a single command)
******************************************************************************/
int	exec_builtin_p(int bi, t_cmd_line *cmd)
{
	if (bi == BUILTIN_ECHO)
		return (echo(cmd->tab_cmd[cmd->cmd_step].tab_args));
	else if (bi == BUILTIN_CD)
		return (cd(cmd->tab_cmd[cmd->cmd_step].tab_args, cmd->env));
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

/******************************************************************************
Function manage the child redirection + execution of the command
******************************************************************************/
void	parent_redir_mgt_in_out(t_cmd_line *cmd)
{
	if (cmd->tab_cmd[cmd->cmd_step].fd_infile > 0)
	{
		if (dup2(cmd->tab_cmd[cmd->cmd_step].fd_infile, STDIN_FILENO) == -1)
			msg_error(ERM_DUP2, ERN_DUP2);
		close(cmd->tab_cmd[cmd->cmd_step].fd_infile);
	}
	if (cmd->tab_cmd[cmd->cmd_step].fd_outfile > 1)
	{
		if (dup2(cmd->tab_cmd[cmd->cmd_step].fd_outfile, STDOUT_FILENO) == -1)
			msg_error(ERM_DUP2, ERN_DUP2);
		close(cmd->tab_cmd[cmd->cmd_step].fd_outfile);
	}
}
