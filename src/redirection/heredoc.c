/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwianni <dwianni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 12:49:14 by dwianni           #+#    #+#             */
/*   Updated: 2025/06/27 10:13:50 by dwianni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/******************************************************************************
Generate the pipe for HEREDOC
******************************************************************************/
void	build_hd_pipe(t_cmd_line *cmd)
{
	int		i;
	t_list	*tmp;

	i = 0;
	while (i < cmd->nb_simple_cmd)
	{
		cmd->tab_cmd[i].hd_test = 0;
		tmp = cmd->tab_cmd[i].redirection;
		while (tmp != NULL)
		{
			if (ft_strncmp(tmp->content, "<<", 2) == 0)
				cmd->tab_cmd[i].hd_test++;
			tmp = tmp->next;
		}
		if (cmd->tab_cmd[i].hd_test != 0)
		{
			if (pipe(cmd->tab_cmd[i].hd_pipe) == -1)
				cmd->exit_code = msg_error(ERM_PIPE, ERN_PIPE);
			cmd->tab_cmd[i].hd_input = NULL;
		}
		i++;
	}
}

/******************************************************************************
Manage heredoc / write in the fd
Return : int fd
******************************************************************************/
int	redir_heredoc(t_cmd_line *cmd, char *s, int i)
{
	char	*eof;

	free_null(&cmd->tab_cmd[i].hd_input);
	free_null(&cmd->tab_cmd[i].infile);
	cmd->tab_cmd[i].hd_input = NULL;
	cmd->tab_cmd[i].infile = NULL;
	if (cmd->tab_cmd[i].fd_infile > 0)
		close(cmd->tab_cmd[i].fd_infile);
	eof = ft_strndup(s, 2, ft_strlen(s));
	if (eof == NULL)
		cmd->exit_code = msg_error(ERM_STRNDUP, ERN_STRNDUP);
	cmd->tab_cmd[i].hd_input = build_heredoc_input(eof);
	free(eof);
	if (cmd->tab_cmd[i].hd_test == 1)
	{
		write(cmd->tab_cmd[i].hd_pipe[1], cmd->tab_cmd[i].hd_input,
			ft_strlen(cmd->tab_cmd[i].hd_input));
		cmd->tab_cmd[i].fd_infile = cmd->tab_cmd[i].hd_pipe[0];
	}
	else
		cmd->tab_cmd[i].hd_test--;
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
		read = readline("> ");
		read = ft_strjoin(read, "\n");
		if (read == NULL)
		{
			mod_error("warning: here-document delimited by " \
				"end-of-file (wanted `", eof, "')");
			break ;
		}
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
	setup_sigs_hd();
	return (build_heredoc_input_int(eof, read, tmp, input_hd));
}
