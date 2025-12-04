/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-yama <nassr.elyamani@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 01:12:46 by nel-yama          #+#    #+#             */
/*   Updated: 2025/12/04 00:03:55 by nel-yama         ###   ########.fr       */
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
# include <errno.h>

# include "libft.h"
# include "parsing.h"

# define BLANK " \t"
# define WHITE_SPACE " \t\n\v\f\r"
# define CONTROL_OP "|&;()"
# define META_CHAR1 "|&;()<>"
# define META_CHAR2 " \t\n"
# define ILLEGAL_CHARS "\\&;()"

typedef struct s_shell
{
	int		last_exit_status;
	char	**envp;
	char	**env_copy;
}	t_shell;

void	sigint_handlers(int sig);
int		is_builtin(char *cmd);
int		execute_builtin(char **args, t_shell *shell);
int		echo(char **args);
int		cd(char **args, t_shell *shell);
int		built_exit(char **args, t_shell *shell);
int		env(t_shell *shell);
int		pwd(void);
char	*expand_vars(char *str, char **env);
int		get_var_name_len(char *str);
char	*get_env_varue(char *var_name, char **env);
char	*extract_var(char *str);
int		find_dollar_var(char *str);
int		get_dollar_len(char *str);
int		unset(char **args, t_shell *shell);
char	*expand_exit_stat(char *str, int exit_stat);
int		export(char **args, t_shell *shell);
int		valid_identifier(char *str);
int		set_env_var(char *arg, t_shell *shell);
int		print_export(t_shell *shell);
char	**copy_env(char **envp);
char	*get_env_value(char *key, t_shell *shell);
char	*get_env_varue(char *key, char **env);
void	free_env(char **env);

/** cmd_arg : might not be used */
typedef struct s_cmd
{
	char	*cmd_name;
	char	*cmd_arg;
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

int		ft_check_quotes(char *s);
int		ft_chk_illegal_chars(char *s);
int		ft_syntax_lexing(char *s);
void	ft_init_arg(t_arg *arg, char **cmd_list);
void	ft_init_cmd(t_cmd *cmd);
void	ft_open_fds(t_cmd *cmd);
void	ft_dup_fds(t_arg *arg, t_cmd *cmd, int i);
void	ft_close_pipes(t_arg *arg);
void	ft_close_files(t_arg *arg);
void	close_fds(t_arg *arg);
void	get_here_doc(t_arg *arg);
int		ft_parse_redirection(t_cmd *cmd, char *sub_cmd, int *i);
int		ft_parse_cmd_args(t_cmd *cmd, char *sub_cmd, int *i);
int		ft_cmd_line_parsing(char *line, t_arg *arg, t_cmd **cmd);
int		create_child_process(t_arg *arg);
int		run_cmd(t_arg *arg, char *cmd, char **envp);
void	run_children(t_arg *arg, char **envp);
char	*ft_get_env(const char *var, char **envp);
void	exit_error(t_arg *arg, char *msg);
void	print_custom_error(int fd, const char *s1, const char *s2);
void	free_and_exit(t_arg *arg);
void	free_and_return(t_arg *arg);
int		end_main(t_arg *arg);

#endif
