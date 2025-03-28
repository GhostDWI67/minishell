/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwianni <dwianni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 12:49:14 by dwianni           #+#    #+#             */
/*   Updated: 2025/03/28 17:11:48 by dwianni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/******************************************************************************
Manage heredoc
Return : 
******************************************************************************/
int	redir_heredoc(t_cmd_line *cmd, char *s, int i)
{
	char	*eof;
	char	*input_hd;
	//int		pipe_fd[2];
	int		fd;

	if (cmd->tab_cmd[i].infile != NULL)
		free(cmd->tab_cmd[i].infile);
	if (cmd->tab_cmd[i].fd_infile != 0)
		close(cmd->tab_cmd[i].fd_infile);
		
	//if (pipe(pipe_fd) == -1)
	//	msg_error(ERM_DUP2, ERN_DUP2);
	
	eof = ft_strndup(s, 2, ft_strlen(s));
	input_hd = build_heredoc_input(eof);
	free(eof);
	
	fd = open("heredoc.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	write(fd, input_hd, ft_strlen(input_hd));
	//close(fd);
	free(input_hd);
	cmd->tab_cmd[i].fd_infile = fd;
	
	//cmd->tab_cmd[i].fd_infile = open(cmd->tab_cmd[i].infile, O_RDONLY);
	//return (cmd->tab_cmd[i].fd_infile);
	return (cmd->tab_cmd[i].fd_infile);
}

char	*build_heredoc_input(char *eof)
{
	char	*read;
	char	*tmp;
	char	*input_hd;
	
	tmp = NULL;
	input_hd = malloc (sizeof(char) * 1);
	input_hd[0] = '\0';
	while (1)
	{
		write(1, &">", 1);
		read = get_next_line(0);
		if (read == NULL)
			break;  // Si on atteint la fin de l'entrée (CTRL+D), on sort
		if (ft_strncmp(read, eof, ft_strlen(eof)) == 0 && read[ft_strlen(eof)] == '\n')
		{
			free(read);
			break;
		}
		tmp = input_hd;
		input_hd = ft_strjoin(input_hd, read);
		free (tmp);
		free (read);
    }
	return (input_hd);
}