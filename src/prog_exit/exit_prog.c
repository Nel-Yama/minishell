/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_prog.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-yama <nassr.elyamani@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 23:41:08 by nel-yama          #+#    #+#             */
/*   Updated: 2025/11/30 19:45:35 by nel-yama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

/**
void	close_fds(t_arg *arg, int in_pipe, int out_pipe)
{
	int	i;

	i = 0;
	while (i < arg->cmd_count)
	{
		if (arg->cmd[i].infile_fd >= 3)
			close(arg->cmd[i].infile_fd);
		if (arg->cmd[i].outfile_fd >= 3)
			close(arg->cmd[i].outfile_fd);
		i++;
	}
	while (in_pipe >= 0)
	{
		close(arg->fd_pipe[in_pipe][0]);
		in_pipe--;
	}
	while (out_pipe >= 0)
	{
		close(arg->fd_pipe[out_pipe][1]);
		out_pipe--;
	}
}
**/
void	ft_close_pipes(t_arg *arg)
{
	int	i;

	if (!arg || !arg->fd_pipe)
		return ;
	if (arg->cmd_count < 2)
		return ;
	i = 0;
	while (i < arg->cmd_count - 1)
	{
		if (arg->fd_pipe[i][0] >= 0)
		{
			close(arg->fd_pipe[i][0]);
			arg->fd_pipe[i][0] = -1;
		}
		if (arg->fd_pipe[i][1] >= 0)
		{
			close(arg->fd_pipe[i][1]);
			arg->fd_pipe[i][1] = -1;
		}
		i++;
	}
}

void	ft_close_files(t_arg *arg)
{
	t_cmd	*cmd;
	int		i;

	cmd = arg->cmd;
	i = 0;
	while (i < arg->cmd_count)
	{
		if (cmd[i].infile_fd >= 3)
		{
			close(cmd[i].infile_fd);
			cmd[i].infile_fd = -1;
		}
		if (cmd[i].outfile_fd >= 3)
		{
			close(cmd[i].outfile_fd);
			cmd[i].outfile_fd = -1;
		}
		if (cmd[i].heredoc_fd >= 3)
		{
			close(cmd[i].heredoc_fd);
			cmd[i].heredoc_fd = -1;
		}
		i++;
	}
}

void	close_fds(t_arg *arg)
{
	ft_close_pipes(arg);
	ft_close_files(arg);
}

/**
 * Normal exit: low 7 bits = 0, Killed by signal: low 7 bits != 0
 * [ high byte (status >> 8) ] → exit code if normal exit
 * [ low 7 bits (status & 0x7F) ] → signal number if killed
 * [ bit 7 of low byte ] → core dump flag (ignored for pipex)
 * Adding 128 for signals follows shell convention (kill -9 → exit 137
**/
int	end_main(t_arg *arg)
{
	int	i;

	close_fds(arg);
	arg->status = (int *)malloc(arg->cmd_count * sizeof(int));
	if (!arg->status)
		exit_error(arg, "minishel: malloc failed for status");
	i = 0;
	while (i < arg->cmd_count)
	{
		if (arg->pid[i] > 0)
			waitpid(arg->pid[i], &arg->status[i], 0);
		else
			arg->status[i] = 0;
		i++;
	}
	if (arg->cmd_count > 0)
	{
		if ((arg->status[arg->cmd_count - 1] & (0x7F)) == 0)
			arg->exit_code = arg->status[arg->cmd_count - 1] >> 8;
		else
			arg->exit_code = (arg->status[arg->cmd_count - 1] & (0x7F)) + 128;
	}
	free_and_return(arg);
	return (arg->exit_code);
}
