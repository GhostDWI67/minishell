/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwianni <dwianni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 10:45:20 by dwianni           #+#    #+#             */
/*   Updated: 2025/03/16 15:19:13 by dwianni          ###   ########.fr       */
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
	t_list *args;
	t_list *redirection;
	char	**tab_args;
	int pipe;
}	t_command;

typedef struct s_cmd_line {
	char		*input;
	t_list		*simple_cmd;
	int			nb_simple_cmd;
	t_command	*tab_cmd;
	char		**tab_path;
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

typedef struct s_toto {
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
}	t_toto;



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