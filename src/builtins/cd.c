/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/16 19:51:57 by marvin            #+#    #+#             */
/*   Updated: 2025/11/16 19:51:57 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	update_env_var(char *key, char *value, t_shell *shell)
{
	int		i;
	char	*tmp;
	char	*new_entry;

	i = 0;
	while (shell->env_copy[i])
	{
		if (ft_strncmp(shell->env_copy[i], key, ft_strlen(key)) == 0
			&& shell->env_copy[i][ft_strlen(key)] == '=')
		{
			tmp = ft_strjoin(key, "=");
			if (!tmp)
				return (1);
			new_entry = ft_strjoin(tmp, value);
			free(tmp);
			if (!new_entry)
				return (1);
			free(shell->env_copy[i]);
			shell->env_copy[i] = new_entry;
			return (0);
		}
		i++;
	}
	return (1);
}

char	*get_target_path(char **args, t_shell *shell)
{
	char	*path;

	if (!args[1] || ft_strcmp(args[1], "~") == 0)
	{
		path = get_env_value("HOME", shell);
		if (!path)
			ft_putendl_fd("minishell: cd: HOME not set", STDERR_FILENO);
		return (path);
	}
	if (ft_strcmp(args[1], "-") == 0)
	{
		path = get_env_value("OLDPWD", shell);
		if (!path)
			ft_putendl_fd("minishell: cd: OLDPWD not set", STDERR_FILENO);
		else
			ft_putendl_fd(path, STDOUT_FILENO);
		return (path);
	}
	return (args[1]);
}

int	change_dir(char **args, char *path)

{
	if (chdir(path) != 0)
	{
		ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
		if (args[1])
			ft_putstr_fd(args[1], STDERR_FILENO);
		else
			ft_putstr_fd(path, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putendl_fd(strerror(errno), STDERR_FILENO);
		return (1);
	}
	return (0);
}

int	cd(char **args, t_shell *shell)

{
	char	*path;
	char	*old_pwd;
	char	*new_pwd;

	if (!shell || !args)
		return (1);
	if (args[1] && args[2])
		return (ft_putendl_fd("minishell: cd: too many arguments",
				STDERR_FILENO), 1);
	path = get_target_path(args, shell);
	if (!path)
		return (1);
	old_pwd = getcwd(NULL, 0);
	if (!old_pwd || change_dir(args, path))
		return (free(old_pwd), 1);
	new_pwd = getcwd(NULL, 0);
	if (!new_pwd)
		return (free(old_pwd), 1);
	update_env_var("PWD", new_pwd, shell);
	update_env_var("OLDPWD", old_pwd, shell);
	free(old_pwd);
	free(new_pwd);
	return (0);
}
