/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwianni <dwianni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 10:45:20 by dwianni           #+#    #+#             */
/*   Updated: 2025/03/23 18:02:12 by dwianni          ###   ########.fr       */
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

/* Standard Value Definition */
# define ERM_DUP2		"dup2 failed"	
# define ERN_DUP2		10
# define ERM_EXECVE		"execve failed"	
# define ERN_EXECVE		11
# define ERM_FORK		"fork failed"	
# define ERN_FORK		12
# define ERM_PIPE		"pipe failed"	
# define ERN_PIPE		13
# define ERM_STRNDUP	"strndup failed"	
# define ERN_STRNDUP	14
# define ERM_FILE		"file failed to open : "	
# define ERN_FILE	15

	
typedef struct s_command {
	t_list	*args;
	t_list	*redirection;
	char	**tab_args;
	int 	pipe;
	int		fd_infile;
	int		fd_outfile;
	char	*infile;
	char	*outfile;
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

/* main.c */

/* check.c */
int			check_quote (char *s);

/* exec.c */
int			f_pipe(t_cmd_line *cmd, char **environ);

/* exec_utils.c */
char		*get_path(char **tab_path, char *fexec);
void 		close_fd(int *fd, int nb_fd);

/* free_utils.c */
int			free_tab_char(char	**tab);
int			free_command(t_command cmd);
int			free_cmd_line(t_cmd_line *cmd);

/* error_mgt */
int			msg_error(char *err_msg, int err_nb);

/* lexer.c */
t_command	lexer(t_list *token);
char		**args_to_tab(t_list *args);

/* parsing.c */
t_list		*parse_cmd(char *s);
t_list		*parse_token(char *s);

/* parsing_utils.c */
int			skip_quote(int i, char *s);
void		clean_space(char *s);

/* redirection.c */
int			redir_mgt(t_cmd_line *cmd);
int			redir_infile(t_cmd_line *cmd, char *s, int i);
int			redir_outfile(t_cmd_line *cmd, char *s, int i);
int			redir_appfile(t_cmd_line *cmd, char *s, int i);

/* utils.c */
char		*ft_strndup(char const *src, int first, int last);
int			ft_is_white_space(char c);

#endif