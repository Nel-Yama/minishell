/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_child.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-yama <nassr.elyamani@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 17:48:22 by nel-yama          #+#    #+#             */
/*   Updated: 2025/11/30 14:34:20 by nel-yama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void	run_first_child(t_arg *arg, char **envp)
{
	t_cmd	*cmd;

	cmd = arg->cmd;
	ft_open_fds(cmd);
	if (cmd->infile_fd < 0 || cmd->outfile_fd < 0)
	{
		close_fds(arg);
		free_and_return(arg);
		exit(1);
	}
//    printf("before dup stdout : First child \n      |%s|\n", cmd->cmd_name);
	ft_dup_fds(arg, cmd, 0);
//    printf("after dup stdout : First child \n      |%s|\n", cmd->cmd_name);
	run_cmd(arg, cmd->cmd_name, envp);
	free_and_return(arg);
	exit(arg->exit_code);
}

static void	run_last_child(t_arg *arg, char **envp)
{
	t_cmd	*cmd;

    cmd = &arg->cmd[arg->cmd_count - 1];
	ft_open_fds(cmd);
	if (cmd->infile_fd < 0 || cmd->outfile_fd < 0)
	{
		close_fds(arg);
		free_and_return(arg);
		exit(1);
	}
//    printf("before dup stdout : last child \n      |%s|\n", arg->cmd[arg->cmd_count - 1].cmd_name);
	ft_dup_fds(arg, cmd, arg->cmd_count - 1);
    printf("after dup stdout : last child \n      |%s|\n", cmd->cmd_name);
	run_cmd(arg, cmd->cmd_name, envp);
	free_and_return(arg);
	exit(arg->exit_code);
}

static void	run_mid_child(t_arg *arg, char **envp, int i)
{
	t_cmd	*cmd;

    cmd = &arg->cmd[i];
	ft_open_fds(cmd);
	if (cmd->infile_fd < 0 || cmd->outfile_fd < 0)
	{
		close_fds(arg);
		free_and_return(arg);
		exit(1);
	}
    printf("before dup stdout : mid child \n      |%s|\n", cmd->cmd_name);
	ft_dup_fds(arg, cmd, i);
//    printf("after dup stdout : mid child \n      |%s|\n", arg->cmd[i].cmd_name);
	run_cmd(arg, cmd->cmd_name, envp);
	free_and_return(arg);
	exit(arg->exit_code);
}

void	run_children(t_arg *arg, char **envp)
{
	int	i;

	if (!arg->pid[0])
		run_first_child(arg, envp);
//        printf("stdout : First child \n      |%s|\n", arg->cmd->cmd_name);
	i = 1;
	while (i < arg->cmd_count - 1)
	{
		if (arg->pid[i - 1] && !arg->pid[i])
			run_mid_child(arg, envp, i);
//            printf("stdout : mid child |%d|\n        |%s|\n", i, arg->cmd[i].cmd_name);
		i++;
	}
	if (arg->pid[arg->cmd_count - 2] && !arg->pid[arg->cmd_count - 1])
        run_last_child(arg, envp);
//        printf("stdout : last child \n      |%s|\n", arg->cmd[arg->cmd_count - 1].cmd_name);
}
