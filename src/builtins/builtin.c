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
	if (!cmd)
		return (0);
	if (ft_strncmp(cmd, "echo", 5) == 0)
		return (1);
	if (ft_strncmp(cmd, "cd", 3) == 0)
		return (1);
	if (ft_strncmp(cmd, "pwd", 4) == 0)
		return (1);
	if (ft_strncmp(cmd, "export", 7) == 0)
		return (1);
	if (ft_strncmp(cmd, "unset", 6) == 0)
		return (1);
	if (ft_strncmp(cmd, "env", 4) == 0)
		return (1);
	if (ft_strncmp(cmd, "exit", 5) == 0)
		return (1);
	return (0);
}

int	execute_builtin(char **args, t_shell *shell)

{
	(void)shell;
	if (!args || !args[0])
		return (1);
	if (ft_strncmp(args[0], "echo", 5) == 0)
		return (echo(args));
	if (ft_strncmp(args[0], "exit", 5) == 0)
		return (built_exit(args, shell));
	if (ft_strncmp(args[0], "cd", 3) == 0)
		return (cd(args, shell));
	if (ft_strncmp(args[0], "pwd", 4) == 0)
		return (pwd());
	if (ft_strncmp(args[0], "export", 7) == 0)
		return (export(args, shell));
	if (ft_strncmp(args[0], "unset", 6) == 0)
		return (unset(args, shell));
	if (ft_strncmp(args[0], "env", 4) == 0)
		return (env(shell));
	return (0);
}
