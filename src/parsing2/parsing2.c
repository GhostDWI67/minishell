/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwianni <dwianni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 13:08:52 by dwianni           #+#    #+#             */
/*   Updated: 2025/05/09 16:20:15 by dwianni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/******************************************************************************
parsing_args
Rebuild the arg list of all the simple comman of the command line
Rebuild a string
Free the old list
Rebuild a new lit
******************************************************************************/
static t_list	*parse_arg_add_arg(t_list *res, char *s, int start, int end)
{
	char	*tmp;

	tmp = ft_strndup(s, start, end);
	if (tmp == NULL)
		return (NULL);
	if (tmp[0] != 0)
		ft_lstadd_back(&res, ft_lstnew(tmp));
	return (res);
}

static int	parse_arg_skip(char *s, int i)
{
	while (ft_is_white_space(s[i]) == 0 && s[i] != '\0')
	{
		if (s[i] == '"' || s[i] == 39)
			i = skip_quote(i, s);
		else
			i++;
	}
	return (i);
}

t_list	*sub_parse_arg(char *s, t_list *res, int i, int start)
{
	while (s[i] != 0)
	{
		while (ft_is_white_space(s[i]) == 1 && s[i] != '\0')
			i++;
		if (ft_is_white_space(s[i]) == 0 && s[i] != '\0')
		{
			start = i;
			i = parse_arg_skip(s, i);
			res = parse_arg_add_arg(res, s, start, i - 1);
		}
	}
	return (res);
}

static t_list	*parse_arg(char *s)
{
	t_list	*res;
	int		i;
	int		start;

	i = 0;
	res = NULL;
	start = 0;
	while (s[i] != 0)
	{
		while (ft_is_white_space(s[i]) == 1 && s[i] != '\0')
			i++;
		if (ft_is_white_space(s[i]) == 0 && s[i] != '\0')
		{
			start = i;
			i = parse_arg_skip(s, i);
			res = parse_arg_add_arg(res, s, start, i - 1);
		}
	}
	return (res);
}

void	parsing_args(t_cmd_line *cmd)
{
	char	*tmp;
	int		i;

	i = 0;
	while (i < cmd->nb_simple_cmd)
	{
		tmp = rebuilt_args(cmd, i);
		//printf("REBUILT-%s-\n", tmp);//
		if (cmd->tab_cmd[i].args != NULL)
			ft_lstclear(&cmd->tab_cmd[i].args, free);
		cmd->tab_cmd[i].args = parse_arg(tmp);
		free(tmp);
		i++;
	}
}
