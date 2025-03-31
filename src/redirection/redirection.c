/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwianni <dwianni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 11:59:20 by dwianni           #+#    #+#             */
/*   Updated: 2025/03/31 16:25:07 by dwianni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/******************************************************************************
Manage redirections
Return : 
******************************************************************************/
/*
static void	redir_mgt_heredoc(t_cmd_line *cmd)
{
	int	i;

	i = 0;
	while (i < cmd->nb_simple_cmd)
	{
		if (cmd->tab_cmd[i].hd_bool == 1)
		{
			if (dup2(cmd->tab_cmd[i].hd_pipe[0], STDIN_FILENO) == -1)
				msg_error(ERM_DUP2, ERN_DUP2);
			close(cmd->tab_cmd[i].hd_pipe[0]);
			write(cmd->tab_cmd[i].hd_pipe[1], cmd->tab_cmd[i].hd_input,
				ft_strlen(cmd->tab_cmd[i].hd_input));
			close(cmd->tab_cmd[i].hd_pipe[1]);
		}
		i++;
	}
}
*/

int	redir_mgt(t_cmd_line *cmd)
{
	t_list	*tmp;
	int		i;

	i = 0;
	while (i < cmd->nb_simple_cmd)
	{
		cmd->tab_cmd[i].redir_test = 1;
		tmp = cmd->tab_cmd[i].redirection;
		cmd->tab_cmd[i].fd_infile = 0;
		cmd->tab_cmd[i].fd_outfile = 1;
		cmd->tab_cmd[i].hd_bool = 0;
		while (tmp != NULL && cmd->tab_cmd[i].redir_test == 1)
		{
			if (ft_strncmp((char *)tmp->content, "<<", 2) == 0)
				redir_heredoc(cmd, (char *)tmp->content, i);
			else if (ft_strncmp((char *)tmp->content, "<", 1) == 0)
				redir_infile(cmd, (char *)tmp->content, i);
			else if (ft_strncmp((char *)tmp->content, ">>", 2) == 0)
				redir_appfile(cmd, (char *)tmp->content, i);
			else if (ft_strncmp((char *)tmp->content, ">", 1) == 0)
				redir_outfile(cmd, (char *)tmp->content, i);
			tmp = tmp->next;
		}
		i++;
	}
	i = 0;
	while (i < cmd->nb_simple_cmd)
	{
		if (cmd->tab_cmd[i].hd_bool == 1)
		{
			if (dup2(cmd->tab_cmd[i].hd_pipe[0], STDIN_FILENO) == -1)
				msg_error(ERM_DUP2, ERN_DUP2);
			close(cmd->tab_cmd[i].hd_pipe[0]);
			write(cmd->tab_cmd[i].hd_pipe[1], cmd->tab_cmd[i].hd_input,
				ft_strlen(cmd->tab_cmd[i].hd_input));
			close(cmd->tab_cmd[i].hd_pipe[1]);
		}
		i++;
	}
	return (0);
}

/******************************************************************************
Manage INFILE
Return : the fd number of the file // -1 is NOK
******************************************************************************/
int	redir_infile(t_cmd_line *cmd, char *s, int i)
{
	char	*msg;

	cmd->tab_cmd[i].hd_bool = 0;
	free_null(cmd->tab_cmd[i].infile);
	if (cmd->tab_cmd[i].fd_infile != 0)
		close(cmd->tab_cmd[i].fd_infile);
	cmd->tab_cmd[i].infile = ft_strndup(s, 1, ft_strlen(s));
	if (cmd->tab_cmd[i].infile == NULL)
	{
		msg_error(ERM_STRNDUP, ERN_STRNDUP);
		return (-1);
	}
	cmd->tab_cmd[i].fd_infile = open(cmd->tab_cmd[i].infile, O_RDONLY);
	if (cmd->tab_cmd[i].fd_infile == -1)
	{
		cmd->tab_cmd[i].redir_test = cmd->tab_cmd[i].redir_test * 0;
		msg = ft_strjoin(ERM_FILE, cmd->tab_cmd[i].infile);
		msg_error(msg, ERN_FILE);
		free(msg);
	}
	return (cmd->tab_cmd[i].fd_infile);
}

/******************************************************************************
Manage OUTFILE
Return : the fd number of the file // -1 is NOK
******************************************************************************/
int	redir_outfile(t_cmd_line *cmd, char *s, int i)
{
	char	*msg;

	free_null(cmd->tab_cmd[i].outfile);
	if (cmd->tab_cmd[i].fd_outfile > 2)
		close(cmd->tab_cmd[i].fd_outfile);
	cmd->tab_cmd[i].outfile = ft_strndup(s, 1, ft_strlen(s));
	if (cmd->tab_cmd[i].outfile == NULL)
	{
		msg_error(ERM_STRNDUP, ERN_STRNDUP);
		return (-1);
	}
	cmd->tab_cmd[i].fd_outfile = open(cmd->tab_cmd[i].outfile,
			O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (cmd->tab_cmd[i].fd_outfile == -1)
	{
		cmd->tab_cmd[i].redir_test = cmd->tab_cmd[i].redir_test * 0;
		msg = ft_strjoin(ERM_FILE, cmd->tab_cmd[i].outfile);
		msg_error(msg, ERN_FILE);
		free(msg);
	}
	return (cmd->tab_cmd[i].fd_outfile);
}

/******************************************************************************
Manage APPENDFILE
Return : the fd number of the file // -1 is NOK
******************************************************************************/
int	redir_appfile(t_cmd_line *cmd, char *s, int i)
{
	char	*msg;

	free_null(cmd->tab_cmd[i].outfile);
	if (cmd->tab_cmd[i].fd_outfile > 2)
		close(cmd->tab_cmd[i].fd_outfile);
	cmd->tab_cmd[i].outfile = ft_strndup(s, 2, ft_strlen(s));
	if (cmd->tab_cmd[i].outfile == NULL)
	{
		msg_error(ERM_STRNDUP, ERN_STRNDUP);
		return (-1);
	}
	cmd->tab_cmd[i].fd_outfile = open(cmd->tab_cmd[i].outfile,
			O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (cmd->tab_cmd[i].fd_outfile == -1)
	{
		cmd->tab_cmd[i].redir_test = cmd->tab_cmd[i].redir_test * 0;
		msg = ft_strjoin(ERM_FILE, cmd->tab_cmd[i].outfile);
		msg_error(msg, ERN_FILE);
		free(msg);
	}
	return (cmd->tab_cmd[i].fd_outfile);
}
