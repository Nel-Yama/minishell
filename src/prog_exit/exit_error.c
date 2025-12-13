/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-yama <nassr.elyamani@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 23:39:19 by nel-yama          #+#    #+#             */
/*   Updated: 2025/12/13 14:28:33 by nel-yama         ###   ########.fr       */
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

void	print_custom_error(int fd, char *s1, char *s2)
{
	ft_putstr_fd("minishell: ", fd);
	ft_putstr_fd(s2, fd);
	ft_putstr_fd(":  ", fd);
	ft_putendl_fd(s1, fd);
}

void	free_and_exit(t_arg *arg)
{
	exit_error(arg, "minishell: fork Failed for child process");
}
