/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-yama <nassr.elyamani@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 23:39:19 by nel-yama          #+#    #+#             */
/*   Updated: 2025/11/30 19:24:19 by nel-yama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	free_and_return(t_arg *arg)
{
	if (arg->fd_pipe)
	{
		free(arg->fd_pipe);
		arg->fd_pipe = NULL;
	}
	if (arg->pid)
	{
		free(arg->pid);
		arg->pid = NULL;
	}
	if (arg->status)
	{
		free(arg->status);
		arg->status = NULL;
	}
	if (arg->cmd)
	{
		free(arg->cmd);
		arg->cmd = NULL;
	}
}

void	exit_error(t_arg *arg, char *msg)
{
	if (arg)
		close_fds(arg);
	free_and_return(arg);
	perror(msg);
	exit(1);
}

void	print_custom_error(int fd, const char *s1, const char *s2)
{
	char	*error_msg;
	char	*tmp;
	int		msg_len;

	if (!s1 || !s2)
		return ;
	tmp = ft_strjoin(s1, s2);
	if (!tmp)
		return ;
	error_msg = ft_strjoin(tmp, "\n");
	free(tmp);
	if (!error_msg)
		return ;
	msg_len = ft_strlen(error_msg);
	write(fd, error_msg, msg_len);
	free(error_msg);
}

void	free_and_exit(t_arg *arg)
{
	exit_error(arg, "minishell>: fork Failed for child process");
}
