/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/16 18:54:07 by marvin            #+#    #+#             */
/*   Updated: 2025/11/16 18:54:07 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "main.h"

int	is_builtin(char *cmd)
{
	char	**cmd_list;
	char	**split_cmd;

	if (!cmd)
		return (0);
	cmd_list = ft_split_smart(cmd, "|");
	if (!cmd_list)
		return (0);
	if (cmd_list[1])
		return (free_split(cmd_list), 0);
	free_split(cmd_list);
	split_cmd = ft_split_quote_smart(cmd, " \t");
	if (!split_cmd)
		return (0);
	if (ft_strncmp(split_cmd[0], "echo", 5) == 0
		|| ft_strncmp(split_cmd[0], "cd", 3) == 0
		|| ft_strncmp(split_cmd[0], "pwd", 4) == 0
		|| ft_strncmp(split_cmd[0], "export", 7) == 0
		|| ft_strncmp(split_cmd[0], "unset", 6) == 0
		|| ft_strncmp(split_cmd[0], "env", 4) == 0
		|| ft_strncmp(split_cmd[0], "exit", 5) == 0)
		return (free_split(split_cmd), 1);
	free_split(split_cmd);
	return (0);
}

int	execute_builtin(char **split_cmd, t_shell *shell)
{
	if (!split_cmd || !split_cmd[0])
		return (1);
	if (ft_strncmp(split_cmd[0], "echo", 5) == 0)
		return (ft_echo(split_cmd));
	if (ft_strncmp(split_cmd[0], "exit", 5) == 0)
		return (built_exit(split_cmd, shell));
	if (ft_strncmp(split_cmd[0], "cd", 3) == 0)
		return (ft_cd(split_cmd, shell));
	if (ft_strncmp(split_cmd[0], "pwd", 4) == 0)
		return (ft_pwd());
	if (ft_strncmp(split_cmd[0], "export", 7) == 0)
		return (ft_export(split_cmd, shell));
	if (ft_strncmp(split_cmd[0], "unset", 6) == 0)
		return (ft_unset(split_cmd, shell));
	if (ft_strncmp(split_cmd[0], "env", 4) == 0)
		return (ft_env(shell));
	return (0);
}
