/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-yama <nassr.elyamani@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 14:16:36 by nel-yama          #+#    #+#             */
/*   Updated: 2025/12/10 16:35:07 by nel-yama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void	run_parent_builtin(t_arg *arg, char **envp)
{
	t_cmd	*cmd;
	int		original_stdin;
	int		original_stdout;

	cmd = arg->cmd;
	original_stdin = dup(STDIN_FILENO);
	original_stdout = dup(STDOUT_FILENO);
	ft_open_fds(cmd);
	if (cmd->infile_fd < 0 || cmd->outfile_fd < 0)
		exit_error(arg, "open redirection file");
	if (cmd->in_node && (cmd->in_redir == 1 || cmd->in_redir == 2))
		ft_in_redirect_only(cmd);
	if (cmd->out_node && cmd->outfile_fd >= 0)
	{
		if (dup2(cmd->outfile_fd, STDOUT_FILENO) == -1)
			perror("dup2 outfile");
	}
	ft_close_current_files(cmd);
	run_cmd(arg, cmd->cmd_name, envp);
	dup2(original_stdin, STDIN_FILENO);
	dup2(original_stdout, STDOUT_FILENO);
	close(original_stdin);
	close(original_stdout);
}

void	ft_run_cmds_process(t_arg *arg, char **line, char **envp)
{
	(void)envp;
	if (is_builtin(*line))
	{
		run_parent_builtin(arg, arg->shell->env_copy);
		return ;
	}
	if (create_child_process(arg))
		return ;
	run_children(arg, arg->shell->env_copy);
	free(*line);
	if (end_main(arg))
		return ;
}
