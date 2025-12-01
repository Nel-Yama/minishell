/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_fds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-yama <nassr.elyamani@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 12:09:50 by nel-yama          #+#    #+#             */
/*   Updated: 2025/12/01 00:33:14 by nel-yama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void	ft_close_current_files(t_cmd *cmd)
{
	if (cmd->infile_fd >= 3)
	{
		close(cmd->infile_fd);
		cmd->infile_fd = -1;
	}
	if (cmd->outfile_fd >= 3)
	{
		close(cmd->outfile_fd);
		cmd->outfile_fd = -1;
	}
}

void	ft_open_fds(t_cmd *cmd)
{
	if (cmd->in_node && cmd->in_redir == 1)
			cmd->infile_fd = open(cmd->in_node, O_RDONLY);
	if (cmd->out_node)
	{
		if (cmd->out_redir == 1)
			cmd->outfile_fd = open(cmd->out_node, O_WRONLY
					| O_CREAT | O_TRUNC, 0644);
		else if (cmd->out_redir == 2)
			cmd->outfile_fd = open(cmd->out_node, O_WRONLY
					| O_CREAT | O_APPEND, 0644);
	}
}

void	ft_in_redirect_only(t_cmd *cmd)
{
	if (cmd->in_redir == 1 && cmd->infile_fd >= 0)
	{
		if (dup2(cmd->infile_fd, STDIN_FILENO) == -1)
			perror("dup2 infile");
	}
	// if (cmd->in_redir == 2 && cmd->heredoc_fd >= 0)
	// {
	// 	if (dup2(cmd->heredoc_fd, STDIN_FILENO) == -1)
	// 		perror("dup2 heredoc");
	// }
}

void	ft_dup_fds(t_arg *arg, t_cmd *cmd, int i)
{
	if (cmd->in_node && (cmd->in_redir == 1 || cmd->in_redir == 2))
		ft_in_redirect_only(cmd);
	else if (i > 0)
	{
		if (dup2(arg->fd_pipe[i - 1][0], STDIN_FILENO) == -1)
			perror("dup2 pipe in");
	}
	if (cmd->out_node && cmd->outfile_fd >= 0)
	{
		if (dup2(cmd->outfile_fd, STDOUT_FILENO) == -1)
			perror("dup2 outfile");
	}
	else if (i < arg->cmd_count - 1)
	{
		if (dup2(arg->fd_pipe[i][1], STDOUT_FILENO) == -1)
			perror("dup2 pipe out");
	}
	ft_close_pipes(arg);
	ft_close_current_files(cmd);
}
