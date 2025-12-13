/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cmd_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-yama <nassr.elyamani@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 14:39:32 by nel-yama          #+#    #+#             */
/*   Updated: 2025/12/13 14:42:04 by nel-yama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static char	*create_cmd_path(char *path_dir, char *cmd)
{
	char	*exec_path;
	char	*tmp;

	if (!path_dir || !cmd)
		return (NULL);
	tmp = ft_strjoin(path_dir, "/");
	if (!tmp)
		return (NULL);
	exec_path = ft_strjoin(tmp, cmd);
	free(tmp);
	return (exec_path);
}

static char	*check_cmd(char *cmd, char *path_var)
{
	char	**path_dirs;
	char	*executable_path;
	int		dir_index;

	path_dirs = ft_split(path_var, ':');
	if (!path_dirs)
		return (NULL);
	dir_index = 0;
	while (path_dirs[dir_index])
	{
		executable_path = create_cmd_path(path_dirs[dir_index], cmd);
		if (!executable_path)
			return (free_split(path_dirs), NULL);
		if (access(executable_path, X_OK) == 0)
			return (free_split(path_dirs), executable_path);
		free(executable_path);
		dir_index++;
	}
	return (free_split(path_dirs), NULL);
}

int	pre_exec(char **cmd, char **envp)
{
	char	*path_var;
	char	*executable_path;

	if (access(*cmd, X_OK) == 0)
		return (1);
	path_var = ft_get_env("PATH", envp);
	if (!path_var)
		return (0);
	executable_path = check_cmd(*cmd, path_var);
	if (!executable_path)
		return (0);
	free(*cmd);
	*cmd = ft_strdup(executable_path);
	if (!cmd || !*cmd)
		return (0);
	return (1);
}

int	check_executable_file(t_arg *arg, char *cmd)
{
	if (!cmd || !cmd[0])
		return (-1);
	if (cmd[0] == '.' && cmd[1] == '/')
	{
		if (access(cmd, X_OK) == 0)
			return (0);
		if (errno == EACCES || errno == EISDIR)
		{
			print_custom_error(2, "Permission denied", cmd);
			arg->exit_code = 126;
			return (-1);
		}
	}
	return (1);
}
