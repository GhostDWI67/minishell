/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwianni <dwianni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 11:59:20 by dwianni           #+#    #+#             */
/*   Updated: 2025/03/23 18:31:47 by dwianni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/******************************************************************************
Manage redirections
Return : 
******************************************************************************/
int	redir_mgt(t_cmd_line *cmd)
{
	t_list	*tmp;
	int		i;
	int		res;

	i = 0;
	res = 0;
	while (i < cmd->nb_simple_cmd)
	{
		tmp = cmd->tab_cmd[i].redirection;
		cmd->tab_cmd[i].fd_infile = 0;
		cmd->tab_cmd[i].fd_outfile = 1;
		while (tmp != NULL)
		{
			if (((char *)tmp->content)[0] == '<')
				res = redir_infile(cmd, (char *)tmp->content, i);
			else if (((char *)tmp->content)[0] == '>' &&
				((char *)tmp->content)[1] == '>')
				res = redir_appfile(cmd, (char *)tmp->content, i);
			else if (((char *)tmp->content)[0] == '>')
				res = redir_outfile(cmd, (char *)tmp->content, i);
			tmp = tmp->next;
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
	if (cmd->tab_cmd[i].infile != NULL)
		free(cmd->tab_cmd[i].infile);
	if (cmd->tab_cmd[i].fd_infile != 0)
		close(cmd->tab_cmd[i].fd_infile);
	cmd->tab_cmd[i].infile = ft_strndup(s, 1, ft_strlen(s));
	if (cmd->tab_cmd[i].infile == NULL)
	{
		msg_error(ERM_STRNDUP, ERN_STRNDUP);
		return (-1) ;
	}
	cmd->tab_cmd[i].fd_infile = open(cmd->tab_cmd[i].infile, O_RDONLY);
	return(cmd->tab_cmd[i].fd_infile);
}

/******************************************************************************
Manage OUTFILE
Return : the fd number of the file // -1 is NOK
******************************************************************************/
int	redir_outfile(t_cmd_line *cmd, char *s, int i)
{
	if (cmd->tab_cmd[i].outfile != NULL)
		free(cmd->tab_cmd[i].outfile);
	if (cmd->tab_cmd[i].fd_outfile != 0)
		close(cmd->tab_cmd[i].fd_infile);
	cmd->tab_cmd[i].outfile = ft_strndup(s, 1, ft_strlen(s));
	if (cmd->tab_cmd[i].outfile == NULL)
	{
		msg_error(ERM_STRNDUP, ERN_STRNDUP);
		return (-1) ;
	}
	cmd->tab_cmd[i].fd_outfile = open(cmd->tab_cmd[i].outfile,
		O_WRONLY | O_CREAT | O_TRUNC, 0644);
	return(cmd->tab_cmd[i].fd_infile);
}

/******************************************************************************
Manage APPENDFILE
Return : the fd number of the file // -1 is NOK
******************************************************************************/
int	redir_appfile(t_cmd_line *cmd, char *s, int i)
{
	if (cmd->tab_cmd[i].outfile != NULL)
		free(cmd->tab_cmd[i].outfile);
	if (cmd->tab_cmd[i].fd_outfile != 0)
		close(cmd->tab_cmd[i].fd_infile);
	cmd->tab_cmd[i].outfile = ft_strndup(s, 2, ft_strlen(s));
	if (cmd->tab_cmd[i].outfile == NULL)
	{
		msg_error(ERM_STRNDUP, ERN_STRNDUP);
		return (-1) ;
	}
	cmd->tab_cmd[i].fd_outfile = open(cmd->tab_cmd[i].outfile,
		O_WRONLY | O_APPEND);
	return(cmd->tab_cmd[i].fd_outfile);
}