/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwianni <dwianni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 10:45:20 by dwianni           #+#    #+#             */
/*   Updated: 2025/03/17 19:11:29 by dwianni          ###   ########.fr       */
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
	t_list	*args;
	t_list	*redirection;
	char	**tab_args;
	int 	pipe;
}	t_command;

typedef struct s_cmd_line {
	char		*input;
	t_list		*simple_cmd;
	int			nb_simple_cmd;
	t_command	*tab_cmd;
	char		**tab_path;
	int			fd_in;
	int			fd_out;
	int			old_fd[2];
	int			new_fd[2];
	int			cmd_step;
}	t_cmd_line;


/*
A faire / Ajouter
Dans command : 
input et output de la commande
voir comment on traite la liste des redirection


Dans cmd_line
nb de commande simple : vient de la taille de la liste des commande simple au départ
environnement
path sous forme de tableau
*/



/* main.c */

/* check.c */
int			check_quote (char *s);

/* exec.c */
char		*get_path(char **tab_path, char *fexec);
int			f_pipe(t_cmd_line *cmd, char **environ);

/* lexer.c */
t_command	lexer(t_list *token);
char		**args_to_tab(t_list *args);

/* parsing.c */
t_list		*parse_cmd(char *s);
t_list		*parse_token(char *s);

/* parsing_utils.c */
int			skip_quote(int i, char *s);
void		clean_space(char *s);

/* utils.c */
char		*ft_strndup(char const *src, int first, int last);
int			ft_is_white_space(char c);

#endif