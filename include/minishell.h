/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpalisse <mpalisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 10:45:20 by dwianni           #+#    #+#             */
/*   Updated: 2025/05/27 14:30:23 by mpalisse         ###   ########.fr       */
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
# include <linux/limits.h>
# include <dirent.h>
# include <signal.h>
//# include <asm/signal.h>
# include "../lib/libft/include/libft.h"
# include "../lib/printf/include/ft_printf.h"

/* Standard Value Definition for token */
# define INPUT			1	//"<"
# define HEREDOC		2	//"<<"
# define OUTPUT			3	//">"
# define APPEND			4	//">>"
# define PIPE			5	//"|"
# define CMD			6	
# define ARG			7	

/* Value definition for BUILT IN*/
# define BUILTIN_NOT	0
# define BUILTIN_ECHO	1
# define BUILTIN_CD		2
# define BUILTIN_PWD	3
# define BUILTIN_EXPORT	4
# define BUILTIN_UNSET	5
# define BUILTIN_ENV	6
# define BUILTIN_EXIT	7

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
# define ERN_FILE		1
# define ERM_STD		"trouble in STD management"	
# define ERN_STD		16
# define ERM_QUOTE		"opened single and/or double quote"	
# define ERN_QUOTE		17
# define ERM_INPUT_NULL	"bash: syntax error: unexpected EOF"	
# define ERN_INPUT_NULL	18
# define ERM_MALLOC		"malloc failed"	
# define ERN_MALLOC		19
# define ERM_TOKEN		"unexpected token : "	
# define ERN_TOKEN		2
# define ERM_WAITPID	"Waitpid failed"	
# define ERN_WAITPID	21
# define ERN_NOTEXEC	127
# define ERM_EXPORT		"export: not a valid identifier"
# define ERN_EXPORT		1
# define ERM_CD			"cd: too many arguments"
# define ERN_CD			1
# define ERM_EXIT		"exit: too many arguments"
# define ERN_EXIT		1
# define ERM_ISDIR		"Is a directory"
# define ERN_ISDIR		126
# define ERM_PERM		"Permission denied"
# define ERN_PERM		126
# define ERM_NOTFD		"No such file or directory"
# define ERN_NOTFD		127

extern int g_signal;

typedef struct s_token
{
	char			*content;
	int				type;
	struct s_token	*next;
}				t_token;

typedef struct s_expand
{
	char	*input;
	char	*output;
	char	*env_name;
	char	*tmp_env_var;
	int		i;
	int		start;
}				t_expand;

typedef struct s_command
{
	t_list	*args;
	t_list	*redirection;
	char	**tab_args;
	int		fd_infile;
	int		fd_outfile;
	char	*infile;
	char	*outfile;
	int		hd_pipe[2];
	char	*hd_input;
	int		redir_test;
}	t_command;

typedef struct s_cmd_line
{
	char		*input;
	t_token		*token;
	t_list		*env;
	char		**tab_env;
	int			nb_simple_cmd;
	t_command	*tab_cmd;
	char		**tab_path;
	int			*tab_fd;
	int			*tab_pid;
	int			cmd_step;
	int			fd_saved_stdin;
	int			fd_saved_stdout;
	int			err_nb;
	int			exit_code;
}	t_cmd_line;

/* main.c */

/* built_in */
int			echo(char **args, t_cmd_line *cmd, int in_child);
int			env(t_list *env, t_cmd_line *cmd, int in_child);
int			export(char **args, t_list **env, t_cmd_line *cmd, int in_child);
bool		export_core(char *arg, t_list **env);
int			pwd(t_cmd_line *cmd, int in_child);
int			unset(char **args, t_list **env, t_cmd_line *cmd, int in_child);
int			cd(char **args, t_list *env, t_cmd_line *cmd, int in_child);
int			ft_exit(t_cmd_line *cmd, char **args);
void		free_exit(t_cmd_line *cmd, bool err, int exit_status);

/* check.c */
int			check_quote(char *s);
int			ws_check(char *s);

/* display.c */
void		display_simple_cmd(t_cmd_line *cmd);
void		display_token(t_cmd_line *cmd);

/* env.c */
int			init_env(t_cmd_line *cmd, char **env, char **argv);
char		*ft_getenv(const char *var, t_list *env);

/* exec.c */
void		f_exec(t_cmd_line *cmd, char **environ);

/* exec_built_in.c*/
int			is_built_in(char **s);
void		exec_builtin_c(int bi, t_cmd_line *cmd);
int			exec_builtin_p(int bi, t_cmd_line *cmd);
void		parent_redir_mgt_in_out(t_cmd_line *cmd);

/* exec_child.c */
int			child(t_cmd_line *cmd, char **environ);

/* exec_utils.c */
char		*get_path(char **tab_path, char *fexec, t_cmd_line *cmd);
void		close_fd(int *fd, int nb_fd);
void		build_pipe(t_cmd_line *cmd);
void		close_tab_pipe(t_cmd_line *cmd);

/* error_mgt */
int			msg_error(char *err_msg, int err_nb);
int			msg_inf(char *err_msg, int err_nb);
void		ft_perror(char *str);
void		mod_error(char *str1, char *str2, char *str3);

/* expand.c */
char		*s_expand(char *str, t_list *env, t_cmd_line *cmd);
void		free_expand(t_expand *s);

/* expand_utils1.c */
void		mod_no_case(t_expand *s);
void		get_env_var_name(t_expand *s);
void		mod_dollar(t_expand *s, t_list *env, t_cmd_line *cmd);
void		mode_squote(t_expand *s);
void		shorten_envvar_outq(t_expand *s);

/* expand_utils2.c */
void		mode_dquote(t_expand *s, t_list *env, t_cmd_line *cmd);

/* free_utils.c */
void		free_null(char **s);
int			free_tab_char(char	**tab);
int			free_command(t_command cmd);
int			free_cmd_line(t_cmd_line *cmd);
int			free_cmd_line_exit(t_cmd_line *cmd);
void		free_exit_ctrld(t_cmd_line *cmd, bool err, int exit_status);

/* heredoc.c */
int			redir_heredoc(t_cmd_line *cmd, char *s, int i);
char		*build_heredoc_input(char *eof);
void		build_hd_pipe(t_cmd_line *cmd);

/* input_mgt.c*/
void		main_input_mgt(t_cmd_line *cmd);

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

/* list_utils.c */
int			ft_lstaddback_content(t_list **env, char *content);
char		**ft_lst_to_arr(t_list *env);
void		sort_tab(char **arr, int len);

/* parsing.c */
void		parsing(t_cmd_line *cmd);
void		cmd_arg_to_tab(t_cmd_line *cmd);

/* parsing2.c */
void		parsing_args(t_cmd_line *cmd);

/* parsing_utils.c */
int			skip_quote(int i, char *s);

/* rebuilt_arg.c */
char		*rebuilt_args(t_cmd_line *cmd, int i);

/* redirection.c */
int			redir_mgt(t_cmd_line *cmd);
int			redir_infile(t_cmd_line *cmd, char *s, int i);
int			redir_outfile(t_cmd_line *cmd, char *s, int i);
int			redir_appfile(t_cmd_line *cmd, char *s, int i);

/* signals.c */
void		setup_sigs_handler(void);
void		setup_sigs_exec(void);
void		setup_sigs_hd(void);
void		sigint_handler(int sig);
void		sig_exec(int signal);
void		sig_heredoc(int signal);
void		sig_exit_status(t_cmd_line *cmd);

/* utils.c */
char		*ft_strndup(char const *src, int first, int last);
int			ft_is_white_space(char c);
void		ft_close(int fd);
bool		empty_line(char *line);

#endif