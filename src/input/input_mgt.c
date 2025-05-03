/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_mgt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwianni <dwianni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 23:27:18 by admin             #+#    #+#             */
/*   Updated: 2025/05/03 13:42:36 by dwianni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/******************************************************************************
Manage the input and history

For debug
//display_token(cmd);
******************************************************************************/
static void	input_first_check(t_cmd_line *cmd)
{
	cmd->token = parse_token(cmd->input);
	if (check_token(cmd->token) == 1)
	{
		add_history(cmd->input);
		cmd->err_nb = ERN_TOKEN;
		cmd->exit_code = cmd->err_nb;
		return ;
	}
	if (check_quote(cmd->input) != 0)
	{
		cmd->err_nb = msg_inf(ERM_QUOTE, ERN_QUOTE);
		cmd->exit_code = cmd->err_nb;
		add_history(cmd->input);
		return ;
	}
}

static void	input_last_pipe_prep(t_cmd_line *cmd, char *tmp, char *input)
{
	tmp = cmd->input;
	cmd->input = ft_strjoin(tmp, input);
	free(tmp);
	token_clear(&cmd->token);
	cmd->token = parse_token(cmd->input);
}

static void	input_last_pipe(t_cmd_line *cmd, char *tmp, char *input)
{
	while (check_token_last_pipe(cmd->token) == 1)
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
			if (check_token(cmd->token) == 1)
			{
				cmd->err_nb = ERN_TOKEN;
				cmd->exit_code = cmd->err_nb;
				add_history(cmd->input);
				break ;
			}
			if (check_quote(cmd->input) != 0)
			{
				cmd->err_nb = msg_inf(ERM_QUOTE, ERN_QUOTE);
				cmd->exit_code = cmd->err_nb;
				add_history(cmd->input);
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
	cmd->input = readline("minishell$");
	if (cmd->input != NULL && cmd->input[0] != '\0')
	{
		input_first_check(cmd);
		input_last_pipe(cmd, tmp, input);
		if (ws_check(cmd->input) != 0 && cmd->input[0] != '\0')
			add_history(cmd->input);
		else
			cmd->err_nb = 1;
	}
	else if (cmd->input != NULL && cmd->input[0] == '\0')
		cmd->err_nb = 25;
	else
	{
		//
		exit (0);
	}
}
