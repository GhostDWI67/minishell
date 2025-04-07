/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_mgt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 23:27:18 by admin             #+#    #+#             */
/*   Updated: 2025/04/07 23:51:19 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/******************************************************************************
Manage the input and history
******************************************************************************/
static void	input_first_check(t_cmd_line *cmd)
{
	cmd->token = parse_token(cmd->input);
	//display_token(cmd);
	if (check_token(cmd->token) == 1)
	{
		add_history(cmd->input);
		return ;
	}
	if (check_quote(cmd->input) != 0)
	{
		cmd->err_nb = msg_inf(ERM_QUOTE, ERN_QUOTE);
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
				add_history(cmd->input);
				break ;
			}
			if (check_quote(cmd->input) != 0)
			{
				cmd->err_nb = msg_inf(ERM_QUOTE, ERN_QUOTE);
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
	if (cmd->input != NULL)
	{
		input_first_check(cmd);
		input_last_pipe(cmd, tmp, input);
		if (ws_check(cmd->input) != 0 && cmd->input[0] != '\0')
			add_history(cmd->input);
	}
	else
	{
		cmd->err_nb = msg_inf(ERM_INPUT_NULL, ERN_INPUT_NULL);
	}
}

/*
void	main_input_mgt(t_cmd_line *cmd)
{
	char	*tmp;
	char	*input;	

	cmd->input = readline("minishell$");
	if (cmd->input != NULL)
	{
		cmd->token = parse_token(cmd->input);
		//display_token(cmd);
		if (check_token(cmd->token) == 1)
		{
			add_history(cmd->input);
			return ;
		}
		if (check_quote(cmd->input) != 0)
		{
			cmd->err_nb = msg_inf(ERM_QUOTE, ERN_QUOTE);
			add_history(cmd->input);
			return ;
		}
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
				tmp = cmd->input;
				cmd->input = ft_strjoin(tmp, input);
				free(tmp);
				token_clear(&cmd->token);
				cmd->token = parse_token(cmd->input);
				if (check_token(cmd->token) == 1)
				{
					add_history(cmd->input);
					break ;
				}
				if (check_quote(cmd->input) != 0)
				{
					cmd->err_nb = msg_inf(ERM_QUOTE, ERN_QUOTE);
					add_history(cmd->input);
					break ;
				}
			}
		}
		if (ws_check(cmd->input) != 0 && cmd->input[0] != '\0')
			add_history(cmd->input);
	}
	else
	{
		cmd->err_nb = msg_inf(ERM_INPUT_NULL, ERN_INPUT_NULL);
	}
}
*/