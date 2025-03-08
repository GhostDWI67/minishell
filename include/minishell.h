/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwianni <dwianni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 10:45:20 by dwianni           #+#    #+#             */
/*   Updated: 2025/03/08 17:30:09 by dwianni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <limits.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft.h"
# include "ft_printf.h"

# define INPUT		1	//"<"
# define HEREDOC	2	//"<<"
# define OUTPUT		3	//">"
# define APPEND		4	//">>"
# define PIPE		5	//"|"
# define CMD		6	
# define ARG		7	

typedef struct s_command {
	char *cmd;
	t_list *args;
	char **env;
	char *input_redirect;
	char *output_redirect;
	t_list *input;
	t_list *output;
	t_list *heredoc;
	t_list *append;
	int pipe;
}	t_command;



/* main.c */

/* check.c */
int		check_quote (char *s);

/* parsing.c */
char	*clean_space(char *s);
t_list	*parse_cmd(char *s);
t_list	*parse_token(char *s);

/* utils.c */
char	*ft_strndup(char const *src, int first, int last);
int		ft_is_white_space(char c);

#endif