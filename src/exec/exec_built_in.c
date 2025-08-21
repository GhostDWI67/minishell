/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_built_in.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpalisse <mpalisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 13:49:26 by dwianni           #+#    #+#             */
/*   Updated: 2025/08/21 09:06:07 by mpalisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/******************************************************************************
Check if teh command is a built in
Return : BUILTIN_NOT if not or the BUILTIN number
******************************************************************************/
int	is_built_in(char **s)
{
	if (s == NULL || *s == NULL)
		return (BUILTIN_NOT);
	if (ft_strncmp(s[0], "echo", INT_MAX) == 0)
		return (BUILTIN_ECHO);
	else if (ft_strncmp(s[0], "cd", INT_MAX) == 0)
		return (BUILTIN_CD);
	else if (ft_strncmp(s[0], "pwd", INT_MAX) == 0)
		return (BUILTIN_PWD);
	else if (ft_strncmp(s[0], "export", INT_MAX) == 0)
		return (BUILTIN_EXPORT);
	else if (ft_strncmp(s[0], "unset", INT_MAX) == 0)
		return (BUILTIN_UNSET);
	else if (ft_strncmp(s[0], "env", INT_MAX) == 0)
		return (BUILTIN_ENV);
	else if (ft_strncmp(s[0], "exit", INT_MAX) == 0)
		return (BUILTIN_EXIT);
	return (BUILTIN_NOT);
}

/******************************************************************************
Execute build_in inside a child
******************************************************************************/
void	exec_builtin_c(int bi, t_cmd_line *cmd)
{
	if (bi == BUILTIN_ECHO)
		exit(echo(cmd->tab_cmd[cmd->cmd_step].tab_args, cmd, 1));
	else if (bi == BUILTIN_CD)
		exit(cd(cmd->tab_cmd[cmd->cmd_step].tab_args, &cmd->env, cmd, 1));
	else if (bi == BUILTIN_PWD)
		exit(pwd(cmd, 1));
	else if (bi == BUILTIN_EXPORT)
		exit(export(cmd->tab_cmd[cmd->cmd_step].tab_args, &cmd->env, cmd, 1));
	else if (bi == BUILTIN_UNSET)
		exit(unset(cmd->tab_cmd[cmd->cmd_step].tab_args, &cmd->env, cmd, 1));
	else if (bi == BUILTIN_ENV)
		exit(env(cmd->env, cmd, 1));
	else if (bi == BUILTIN_EXIT)
		exit(ft_exit(cmd, cmd->tab_cmd[cmd->cmd_step].tab_args));
	exit(0);
}

/******************************************************************************
Execute build-in inside a parent (when it's a single command)
******************************************************************************/
int	exec_builtin_p(int bi, t_cmd_line *cmd)
{
	if (bi == BUILTIN_ECHO)
		return (echo(cmd->tab_cmd[cmd->cmd_step].tab_args, cmd, 0));
	else if (bi == BUILTIN_CD)
		return (cd(cmd->tab_cmd[cmd->cmd_step].tab_args, &cmd->env, cmd, 0));
	else if (bi == BUILTIN_PWD)
		return (pwd(cmd, 0));
	else if (bi == BUILTIN_EXPORT)
		return (export(cmd->tab_cmd[cmd->cmd_step].tab_args, \
			&cmd->env, cmd, 0));
	else if (bi == BUILTIN_UNSET)
		return (unset(cmd->tab_cmd[cmd->cmd_step].tab_args, &cmd->env, cmd, 0));
	else if (bi == BUILTIN_ENV)
		return (env(cmd->env, cmd, 0));
	else if (bi == BUILTIN_EXIT)
		return (ft_exit(cmd, cmd->tab_cmd[cmd->cmd_step].tab_args));
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
			cmd->exit_code = msg_error(ERM_DUP2, ERN_DUP2);
		close(cmd->tab_cmd[cmd->cmd_step].fd_infile);
	}
	if (cmd->tab_cmd[cmd->cmd_step].fd_outfile > 1)
	{
		if (dup2(cmd->tab_cmd[cmd->cmd_step].fd_outfile, STDOUT_FILENO) == -1)
			cmd->exit_code = msg_error(ERM_DUP2, ERN_DUP2);
		close(cmd->tab_cmd[cmd->cmd_step].fd_outfile);
	}
}
