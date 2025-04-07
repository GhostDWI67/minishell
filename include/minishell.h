/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwianni <dwianni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 10:45:20 by dwianni           #+#    #+#             */
/*   Updated: 2025/04/05 16:36:56 by dwianni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
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

/* Standard Value Definition for token */
# define INPUT			1	//"<"
# define HEREDOC		2	//"<<"
# define OUTPUT			3	//">"
# define APPEND			4	//">>"
# define PIPE			5	//"|"
# define CMD			6	
# define ARG			7	

/* Standard Value Definition for error message*/
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
# define ERN_FILE		15
# define ERM_STD		"trouble in STD management"	
# define ERN_STD		16
# define ERM_QUOTE		"opened single and/or double quote"	
# define ERN_QUOTE		17
# define ERM_INPUT_NULL	"NULL input ?!?"	
# define ERN_INPUT_NULL	18
# define ERM_MALLOC		"malloc failed"	
# define ERN_MALLOC		19
# define ERM_TOKEN		"unexpected token : "	
# define ERN_TOKEN		20

typedef struct s_token
{
	char			*content;
	int				type;
	struct s_token	*next;
}				t_token;
	
typedef struct s_command {
	t_list	*args; //free OK
	t_list	*redirection; //free OK
	char	**tab_args; //free ?? a revoir ?
	int 	pipe;
	int		fd_infile;
	int		fd_outfile;
	char	*infile; //free OK
	char	*outfile; //free OK
	int		hd_pipe[2];
	char	*hd_input; //free OK
	int		redir_test;
}	t_command;

typedef struct s_cmd_line {
	char		*input;
	t_token		*token;
	//t_list		*simple_cmd;
	int			nb_simple_cmd;
	t_command	*tab_cmd;
	char		**tab_path;
	int			fd_in;// a virer ??
	int			fd_out;// a virer ??
	int			*tab_fd;
	int			*tab_pid;
	int			cmd_step;
	int			fd_saved_stdin;//a virer ??
	int			fd_saved_stdout;//a virer ??
	int			err_nb;
}	t_cmd_line;

/* main.c */

/* check.c */
int			check_quote (char *s);
int			ws_check(char *s);

/* display.c */
void		display_simple_cmd(t_cmd_line *cmd);
void		display_token(t_cmd_line *cmd);

/* exec.c */
int			f_pipe(t_cmd_line *cmd, char **environ);

/* exec_child.c */
int			child(t_cmd_line *cmd, char **environ);

/* exec_utils.c */
char		*get_path(char **tab_path, char *fexec);
void 		close_fd(int *fd, int nb_fd);
void		build_pipe(t_cmd_line *cmd);
void		close_tab_pipe(t_cmd_line *cmd);

/* error_mgt */
int			msg_error(char *err_msg, int err_nb);
int			msg_inf(char *err_msg, int err_nb);

/* free_utils.c */
void		free_null(char *s);
int			free_tab_char(char	**tab);
int			free_command(t_command cmd);
int			free_cmd_line(t_cmd_line *cmd);

/* heredoc.c */
int			redir_heredoc(t_cmd_line *cmd, char *s, int i);
char		*build_heredoc_input(char *eof);
void		build_hd_pipe(t_cmd_line *cmd);

/* lexer.c */
t_token		*parse_token(char *s);

/* lexer_check.c */
int			check_token(t_token *token);
int			check_token_last_pipe(t_token *token);
int			check_token_nb_cmd(t_token *token);

/* lexer_utils.c */
t_token		*token_new(char *content, int type);
t_token		*token_last(t_token *lst);
void		token_add_back(t_token **lst, t_token *new);
void		token_clear(t_token **lst);

/* parsing.c */
void		parsing(t_cmd_line *cmd);
char		**args_to_tab(t_list *args);

/* parsing_utils.c */
int			skip_quote(int i, char *s);

/* redirection.c */
int			redir_mgt(t_cmd_line *cmd);
int			redir_infile(t_cmd_line *cmd, char *s, int i);
int			redir_outfile(t_cmd_line *cmd, char *s, int i);
int			redir_appfile(t_cmd_line *cmd, char *s, int i);

/* utils.c */
char		*ft_strndup(char const *src, int first, int last);
int			ft_is_white_space(char c);
void		ft_close(int fd);

#endif