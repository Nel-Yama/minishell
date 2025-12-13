/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-yama <nassr.elyamani@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 01:12:46 by nel-yama          #+#    #+#             */
/*   Updated: 2025/12/13 14:42:16 by nel-yama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <signal.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <errno.h>

# include "libft.h"
# include "parsing.h"

# define BLANK " \t"
# define WHITE_SPACE " \t\n\v\f\r"
# define CONTROL_OP "|&;()"
# define META_CHAR1 "|&;()<>"
# define SPECIAL_CHAR "|&;()<>/\\ \t\'\""
# define META_CHAR2 " \t\n"
# define ILLEGAL_CHARS "\\&;()"

typedef struct s_shell
{
	int		*last_exit_status;
	char	**envp;
	char	**env_copy;
}	t_shell;

/** cmd_arg : might not be used */
typedef struct s_cmd
{
	char	*cmd_name;
	char	**cmd_arg;
	int		in_redir;
	int		out_redir;
	char	*in_node;
	int		infile_fd;
	char	*out_node;
	int		outfile_fd;
	int		heredoc_fd;
}	t_cmd;

typedef struct s_arg
{
	int		cmd_count;
	int		*pid;
	int		*status;
	int		(*fd_pipe)[2];
	int		exit_code;
	t_cmd	*cmd;
	t_shell	*shell;
}	t_arg;

/** Builtin Functions */

void	sigint_handlers(int sig);
int		is_builtin(char *cmd);
int		execute_builtin(char **split_cmd, t_shell *shell);
int		ft_echo(char **args);
int		ft_cd(char **args, t_shell *shell);
int		built_exit(char **args, t_shell *shell);
int		ft_env(t_shell *shell);
int		ft_pwd(void);
int		ft_unset(char **args, t_shell *shell);
int		ft_export(char **args, t_shell *shell);
int		valid_identifier(char *str);
int		set_env_var(char *arg, t_shell *shell);
int		print_export(t_shell *shell);
char	*prepare_export_entry(char *str, char *key);
char	**copy_env(char **envp);
char	*get_env_value(char *key, t_shell *shell);
char	*get_env_varue(char *key, char **env);
void	free_env(char **env);
int		handle_append(char *str, int idx, t_shell *shell);
char	*get_key(char *str);
int		is_append_mode(char *str);
void	increment_shlvl(t_shell *shell);

/** Expansion Functions */
char	*ft_expand(char **line, t_arg *arg);
char	*ft_dollar_quest(t_arg *arg);
char	*ft_dollar_var(char *var, t_arg *arg);
int		ft_check_braces(char *var);
char	*ft_get_expand(char *var, t_arg *arg, int *i);
char	*ft_expand_var(t_arg *arg, char *var, int *idx);
void	ft_exp_append_chunk(char **result, char *chunk);
void	ft_exp_dollar(t_arg *arg, char *dollar_ptr,
			char **res, int *i);
void	ft_exp_single_quotes(char **res, char *line, int *i);
void	ft_exp_copy_literal(char **res, char *line, int *i, int start);

/** Lexing, Parsing and Execution Functions */

int		ft_check_quotes(char *s);
int		ft_chk_illegal_chars(char *s);
int		ft_syntax_lexing(char *s);
int		is_empty_line(char *line);
int		ft_shell_init(t_arg *arg, t_shell *shell, char **envp);
int		ft_lex_parse_exec(t_arg *arg, char **line, t_cmd **cmd);
void	ft_run_cmds_process(t_arg *arg, char **line, char **envp);
void	ft_init_arg(t_arg *arg, char **cmd_list);
void	ft_init_cmd(t_cmd *cmd);
void	ft_in_redirect_only(t_cmd *cmd);
void	ft_open_fds(t_cmd *cmd);
void	ft_dup_fds(t_arg *arg, t_cmd *cmd, int i);
void	ft_close_pipes(t_arg *arg);
void	ft_close_files(t_arg *arg);
void	ft_close_current_files(t_cmd *cmd);
void	close_fds(t_arg *arg);
void	get_here_doc(t_arg *arg);
int		check_file_access(int type, int redir, char *file_name);
int		ft_parse_redirection(t_cmd *cmd, char *sub_cmd, int *i);
int		ft_parse_cmd_args(t_cmd *cmd, char *sub_cmd, int *i);
int		ft_cmd_line_parsing(char *line, t_arg *arg, t_cmd **cmd);
int		create_child_process(t_arg *arg);
int		check_executable_file(t_arg *arg, char *cmd);
int		pre_exec(char **cmd, char **envp);
int		run_cmd(t_arg *arg, char *cmd, char **envp);
void	run_children(t_arg *arg, char **envp);
char	*ft_get_env(const char *var, char **envp);
void	exit_error(t_arg *arg, char *msg);
void	print_custom_error(int fd, char *s1, char *s2);
void	free_and_exit(t_arg *arg);
void	free_and_return(t_arg *arg);
int		end_main(t_arg *arg);

#endif
