/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzaatreh <rzaatreh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/25 13:34:33 by rzaatreh          #+#    #+#             */
/*   Updated: 2026/06/16 12:41:16 by rzaatreh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <sys/wait.h>
# include <sys/stat.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <signal.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft/libft.h"

extern int	g_exit_status;

typedef enum e_token_type
{
	WORD,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	HEREDOC
}	t_token_type;

typedef enum e_quote_type
{
	NO_QUOTE,
	SINGLE_QUOTE,
	DOUBLE_QUOTE
}	t_quote_type;

typedef struct s_token
{
	char			*value;
	t_token_type	type;
	t_quote_type	quote;
	struct s_token	*next;
}	t_token;

typedef struct s_redir
{
	t_token_type	type;
	char			*file;
	int				heredoc_fd;
	struct s_redir	*next;
}	t_redir;

typedef struct s_cmd
{
	char			**argv;
	t_quote_type	*quotes;
	t_redir			*redir;
	int				pipe_to_next;
	struct s_cmd	*next;
}	t_cmd;

t_token			*lexer(char *input);
char			*read_word(char *input, int *i, t_quote_type *quote);
char			*read_quoted(char *input, int *i, t_quote_type *quote);
t_token			*create_operator_token(char *input, int *i);

int				is_space(char c);
int				is_operator(char c);
char			*strjoin_free(char *s1, char *s2);
int				operator_length(char *s);
t_token_type	operator_type(char *s);

t_token			*token_create(t_token_type type, char *value,
					t_quote_type quote);
void			token_add_back(t_token **list, t_token *tokn);
void			token_clear(t_token **list);

t_cmd			*parse_tokens(t_token *tokens);
t_cmd			*cmd_new(void);
int				cmd_add_arg(t_cmd *cmd, char *arg, t_quote_type quote);
void			cmd_clear(t_cmd **cmds);
int				argv_len(char **argv);
int				is_redir_only(t_cmd *cmd);

int				check_syntax(t_token *tokens);

t_redir			*redir_new(t_token_type type, char *file);
void			redir_add_back(t_redir **list, t_redir *new);
void			redir_clear(t_redir *redir);
int				is_redirection(t_token_type type);

int				expand_commands(t_cmd *cmds, char **envp);
char			*expand_string(char *str, char **envp);
int				is_var_char(char c);

char			*get_env_value(char *name, char **envp);

int				check_quotes(char *input);

int				execute_all(t_cmd *cmds, char ***envp);

int				execute_single_builtin(t_cmd *cmd, char ***envp);
int				run_redir_only(t_cmd *cmd);
void			exec_cmd(char *path, t_cmd *cmd, char ***envp);

int				apply_redirections(t_redir *redir);
void			setup_child_pipes(int **pipes, int index, int total);
void			reset_child_signals(void);

void			handle_sigint(int sig);

int				count_cmds(t_cmd *cmds);
int				**create_pipes(int count);
void			close_pipes(int **pipes, int count);
void			free_pipes(int **pipes, int count);
int				wait_all(pid_t last_pid, int *last_status);

int				alloc_pipes(int **pipes, int count);
char			*get_cmd_path(char **argv, char **envp);
int				is_directory(char *path);

int				open_heredocs(t_cmd *cmds);
void			close_heredocs(t_cmd *cmds);
int				read_heredoc(char *delimiter);
void			heredoc_child(char *delimiter, int write_fd);
int				heredoc_parent(int *pipefd, pid_t pid, struct sigaction *sa_old);

void			process_input(char *line, char ***envp);
char			**copy_env(char **envp);

int				builtin_cd(char **argv, char ***envp);
int				builtin_echo(char **argv);
int				builtin_env(char **envp);
int				builtin_exit(char **argv);
int				builtin_export(char **argv, char ***envp);
int				builtin_pwd(void);
int				builtin_unset(char **argv, char ***envp);

int				is_builtin(char *cmd);
int				execute_builtin(t_cmd *cmd, char ***envp);
void			update_env_var(char ***envp, char *key, char *value);

#endif
