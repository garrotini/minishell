/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmanuel- <cmanuel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 22:06:26 by cmanuel-          #+#    #+#             */
/*   Updated: 2026/01/07 20:00:00 by cmanuel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include "builtins/builtins.h"
# include "utils/utils.h"

# define PS1 "minishell $ "
# define MAX_LEN 1024

# define HEREDOC_ERROR1 "minishell : warning: here-document at line "
# define HEREDOC_ERROR2 "delimited by end-of-file "
# define HEREDOC_NAME "/tmp/.minishell_heredoc_"

# define CMD_NOT_FOUND 127
# define CMD_NOT_EXEC 126

extern volatile sig_atomic_t	g_signal_exit_code;

typedef enum e_tk_type
{
	WORD,
	PIPE,
	SEMICOLON,
	INPUT,
	OUTPUT,
	HEREDOC,
	APPEND,
	S_QUOTE,
	D_QUOTE,
	END
}								t_tk_type;

typedef enum e_tk_mode
{
	UNQUOTED,
	IN_SQ,
	IN_DQ,
}								t_tk_mode;

typedef struct s_tk
{
	char						*str;
	char						*str_bak;
	t_tk_type					type;
	t_tk_mode					mode;
	int							expand;
	struct s_tk					*prev;
	struct s_tk					*next;
}								t_tk;

typedef struct s_env
{
	struct s_sh					*sh;
	char						*key;
	char						*value;
	struct s_env				*next;
}								t_env;

typedef struct s_io_fds
{
	char						*infile;
	char						*outfile;
	char						*heredoc_del;
	int							heredoc_expand;
	int							fd_in;
	int							fd_out;
	int							stdin_bak;
	int							stdout_bak;
}								t_io_fds;

typedef struct s_cmd
{
	char						*cmd;
	char						**av;
	t_tk_mode					*av_mode;
	char						*path;
	int							pipe_out;
	int							*pipe_fd;
	t_io_fds					*io_fds;
	struct s_cmd				*prev;
	struct s_cmd				*next;
}								t_cmd;

typedef struct s_sh
{
	char						*input;
	t_env						*env;
	t_cmd						*cmd;
	t_tk						*tk;
	pid_t						pid;
	int							exit_code;
}								t_sh;

// init
int								init_shell(t_sh *sh, char **env);
void							init_io(t_cmd *cmd);
void							set_signals_on(void);
void							set_signals_off(void);
void							set_signals_heredoc(void);

// lexer
int								lexer(t_sh *sh);

// split.c
char							**split_input(char *input);

// split_utils.c
size_t							count_av_size(char **av);
char							*create_tk_str(char *s, size_t len);
char							**add_str(char **av, char *s, size_t len);
char							*rm_dollar_pattern(char *s, int i);
char							*rm_dollar_quote(char *s);

// token.c
t_tk							*get_tk_list(char **av);
int								calc_word_len(char *s);

// var_expansion.c
void							var_expansion(t_tk **tk, t_env *env,
									int exit_code);

// var_expansion_utils.c
int								get_var_len(char *s, int i);
char							*replace_var(char *s, int *i, char *value,
									int var_len);
char							*expand_exit_code(char *s, int *i,
									int exit_code);

// var_split.c
int								needs_word_splitting(t_tk *tk, int expanded);
char							**split_by_whitespace(char *str);
void							ins_split_tk(t_tk **tk_list, t_tk *ins_pos,
									char **av);
void							apply_word_splitting(t_tk **tk_list,
									t_tk **cur);

// var_split_utils.c
void							ins_tk_after(t_tk *cur, t_tk *new_tk);
void							rm_tk_from_list(t_tk **head, t_tk *tk);
char							**malloc_av(int n);
void							fill_av(char **av, char *s, int n);
int								count_av(char **av);

// var_split_utils2.c
int								is_whitespace(char c);
int								count_words(char *s);
char							*extract_word(char *str, int *pos);
void							finalize_split(t_tk **tk_list, t_tk **current,
									char **av);

// rm_quote.c
void							rm_quote(t_tk *tk);

// rm_quote_utils.c
char							*process_backslash_dq(char *str, int i, int j);
char							*process_backslash(char *str, int i, int j);
char							strip_quotes(t_tk *tk);

// syntaxer.c
int								syntaxer(t_tk **tk);

// error.c
int								perror_syntax(int type);
int								perror_syntax_str(char *token);
void							perror_msg(char *s1, char *s2, char *s3);
int								cmd_not_found(char *cmd);
int								perror_unclosed_quote(char quote);

// parser.c
void							parser(t_sh *sh);

void							parse_word(t_cmd **cmd_lst, t_tk **tk_lst);
void							cmd_fill_av(t_tk **tk, t_cmd *last_cmd);

void							parse_pipe(t_cmd **cmd_lst, t_tk **tk_lst);
void							parse_semicolon(t_cmd **cmd_lst, t_tk **tk_lst);
void							parse_input(t_cmd **cmd_lst, t_tk **tk_lst);
void							parse_output(t_cmd **cmd_lst, t_tk **tk_lst,
									char c);

// parser_heredoc, parser_heredoc_utils, parser_heredoc_expand
void							parse_heredoc(t_sh *sh, t_tk **tk_lst);
int								heredoc_clear(t_io_fds *io);
int								heredoc_fill(t_io_fds *io, int fd, t_sh *sh);
int								heredoc_create(t_io_fds *io, t_sh *sh);
char							*expand_heredoc_line(char *line, t_env *env,
									int exit_code);

// utils.c
void							free_split(char **av);

// exit_clean.c
void							close_fds(t_cmd *cmd);
void							exit_sh(t_sh *sh);
void							free_env_list(t_env *env);
void							free_sh(t_sh *sh);
void							full_clean(t_sh *sh);

// exit_clean_utils.c
void							exit_child(t_sh *sh, int exit_code);

// executor.c
int								executor(t_sh *sh);
void							exec_child(t_sh *sh, t_cmd *cmd, int in_fd,
									int out_fd);

// exec_builtin_utils.c
int								exec_builtin(t_sh *sh, t_cmd *cmd, t_env **env);

// exec_utils.c
char							**env_list_to_envp(t_env *env);
char							*resolve_cmd_path(char *cmd, t_env *env);
void							exec_command(t_sh *sh, t_cmd *cmd);

// exec_utils_2.c
char							*join_env_entry(t_env *env);
int								count_envp(t_env *env);
int								fill_envp(char **envp, t_env *env);

// exec_pipeline.c
int								execute_pipeline(t_sh *sh, t_cmd *start,
									t_cmd *end);

#endif
