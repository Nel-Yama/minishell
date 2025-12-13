/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-yama <nassr.elyamani@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 19:03:45 by nel-yama          #+#    #+#             */
/*   Updated: 2025/12/13 14:49:20 by nel-yama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void	pre_exec_set_exit_code(t_arg *arg, char **split_cmd)
{
	if (errno == EACCES || errno == EISDIR)
	{
		print_custom_error(2, "Permission denied", split_cmd[0]);
		arg->exit_code = 126;
	}
	else
	{
		print_custom_error(2, "command not found", split_cmd[0]);
		arg->exit_code = 127;
	}
}

static void	execve_set_exit_code(t_arg *arg)
{
	if (errno == EACCES || errno == EISDIR)
		arg->exit_code = 126;
	else
		arg->exit_code = 1;
}

int	run_cmd(t_arg *arg, char *cmd, char **envp)
{
	char	**split_cmd;
	int		exec_ret;

	split_cmd = ft_split_quote_smart(cmd, " \t");
	if (is_builtin(cmd))
	{
		arg->exit_code = execute_builtin(split_cmd, arg->shell);
		free_split(split_cmd);
		return (0);
	}
	exec_ret = check_executable_file(arg, split_cmd[0]);
	if (exec_ret == -1)
		return (free_split(split_cmd), arg->exit_code);
	else if (exec_ret == 1 && !pre_exec(&split_cmd[0], envp))
	{
		pre_exec_set_exit_code(arg, split_cmd);
		return (free_split(split_cmd), arg->exit_code);
	}
	if (execve(split_cmd[0], split_cmd, envp) == -1)
		execve_set_exit_code(arg);
	free_split(split_cmd);
	return (errno);
}
