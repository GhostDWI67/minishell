/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwianni <dwianni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 12:49:14 by dwianni           #+#    #+#             */
/*   Updated: 2025/03/30 19:39:15 by dwianni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/******************************************************************************
Generate the pipe for HEREDOC
******************************************************************************/
void	build_hd_pipe(t_cmd_line *cmd)
{
	cmd->cmd_step = 0;
	while (cmd->cmd_step < cmd->nb_simple_cmd)
	{
		if (pipe(cmd->tab_cmd[cmd->cmd_step].hd_pipe) == -1)
			msg_error(ERM_DUP2, ERN_DUP2);
		cmd->tab_cmd[cmd->cmd_step].hd_input = NULL;
		cmd->cmd_step++;
	}
	cmd->cmd_step = 0;
}

/******************************************************************************
Manage heredoc / write in the fd
Return : int fd
******************************************************************************/
int	redir_heredoc(t_cmd_line *cmd, char *s, int i)
{
	char	*eof;

	cmd->tab_cmd[i].hd_bool = 1;
	if (cmd->tab_cmd[i].hd_input != NULL)
		free(cmd->tab_cmd[i].hd_input);
	if (cmd->tab_cmd[i].infile != NULL)
		free(cmd->tab_cmd[i].infile);
	if (cmd->tab_cmd[i].fd_infile != 0)
		close(cmd->tab_cmd[i].fd_infile);
	eof = ft_strndup(s, 2, ft_strlen(s));
	if (eof == NULL)
		msg_error(ERM_STRNDUP, ERN_STRNDUP);
	cmd->tab_cmd[i].hd_input = build_heredoc_input(eof);
	free(eof);
	return (0);
}

/******************************************************************************
HEREDOC build the string
Return : a string with the full message of the HEREDOC
******************************************************************************/
static char	*build_heredoc_input_int(char *eof, char *read, char *tmp,
	char *input_hd)
{
	while (1)
	{
		ft_putstr_fd(">", 1);
		read = get_next_line(0);
		if (read == NULL)
			break ;
		if (ft_strncmp(read, eof, ft_strlen(eof)) == 0
			&& read[ft_strlen(eof)] == '\n')
		{
			free(read);
			break ;
		}
		tmp = input_hd;
		input_hd = ft_strjoin(input_hd, read);
		if (input_hd == NULL)
			msg_error(ERM_STRNDUP, ERN_STRNDUP);
		free (tmp);
		free (read);
	}
	return (input_hd);
}

char	*build_heredoc_input(char *eof)
{
	char	*read;
	char	*tmp;
	char	*input_hd;

	tmp = NULL;
	read = NULL;
	input_hd = ft_strdup("");
	return (build_heredoc_input_int(eof, read, tmp, input_hd));
}
