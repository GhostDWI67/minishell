/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_mgt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwianni <dwianni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 23:27:18 by admin             #+#    #+#             */
/*   Updated: 2025/05/17 16:38:30 by dwianni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/******************************************************************************
Manage the input and history

First check open quote and token check : even if not OK add to the history
Check if the last token is a pipe and manage the additionnal entries
Check if the line is only with white space => return a new command linde and
	don't add in history
Manage the exit

For debug
//display_token(cmd);
******************************************************************************/
static int	input_first_check(t_cmd_line *cmd)
{
	cmd->token = parse_token(cmd->input);
	if (check_token(cmd->token) != 0)
	{
		add_history(cmd->input);
		cmd->err_nb = ERN_TOKEN;
		cmd->exit_code = cmd->err_nb;
		return (1);
	}
	if (check_quote(cmd->input) != 0)
	{
		cmd->err_nb = msg_inf(ERM_QUOTE, ERN_QUOTE);
		cmd->exit_code = cmd->err_nb;
		add_history(cmd->input);
		return (1);
	}
	return (0);
}

static void	input_last_pipe_prep(t_cmd_line *cmd, char *tmp, char *input)
{
	tmp = cmd->input;
	cmd->input = ft_strjoin(tmp, input);
	free(tmp);
	token_clear(&cmd->token);
	cmd->token = parse_token(cmd->input);
}

static void	input_last_pipe_check(t_cmd_line *cmd)
{
	if (check_token(cmd->token) != 0)
	{
		cmd->err_nb = ERN_TOKEN;
		cmd->exit_code = cmd->err_nb;
		add_history(cmd->input);
	}
	if (check_quote(cmd->input) != 0)
	{
		cmd->err_nb = msg_inf(ERM_QUOTE, ERN_QUOTE);
		cmd->exit_code = cmd->err_nb;
		add_history(cmd->input);
	}
}

static void	input_last_pipe(t_cmd_line *cmd, char *tmp, char *input)
{
	while (check_token_last_pipe(cmd->token) != 0)
	{
		input = readline("pipe> ");
		if (input == NULL)
		{
			cmd->err_nb = msg_inf(ERM_INPUT_NULL, ERN_INPUT_NULL);
			break ;
		}
		else if (ws_check(input) != 0 && input[0] != '\0')
		{
			input_last_pipe_prep(cmd, tmp, input);
			if (check_token(cmd->token) != 0 || check_quote(cmd->input) != 0)
			{
				input_last_pipe_check(cmd);
				break ;
			}
		}
	}
}

void	main_input_mgt(t_cmd_line *cmd)
{
	char	*tmp;
	char	*input;	

	tmp = NULL;
	input = NULL;
	cmd->input = readline("minishell$ ");
	if (empty_line(cmd->input))
	{
		cmd->err_nb = 25;
		return ;
	}
	if (cmd->input != NULL && cmd->input[0] != '\0')
	{
		if (input_first_check(cmd) == 0)
			input_last_pipe(cmd, tmp, input);
		if (ws_check(cmd->input) != 0 && cmd->input[0] != '\0')
			add_history(cmd->input);
		else
			cmd->err_nb = 1;
	}
	else
	{
		free_exit_ctrld(cmd, false, 0);
	}
}
