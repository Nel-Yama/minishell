/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/16 19:51:41 by marvin            #+#    #+#             */
/*   Updated: 2025/11/16 19:51:41 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	valid_identifier(char *str)

{
	int	i;

	i = 0;
	if (!str || !str[0])
		return (0);
	if (!(ft_isalpha((unsigned char)str[0]) || str[0] == '_'))
		return (0);
	i++;
	while (str[i] && str[i] != '=')
	{
		if (!(ft_isalnum((unsigned char)str[i]) || str[i] == '_'))
			return (0);
		i++;
	}
	return (1);
}

static int	find_key_index(char **env, char *key, int key_len)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], key, key_len) == 0
			&& (env[i][key_len] == '=' || env[i][key_len] == '\0'))
			return (i);
		i++;
	}
	return (-1);
}

static char	**add_to_env(char **old_env, char *new_entry)
{
	char	**new_env;
	int		i;

	i = 0;
	while (old_env[i])
		i++;
	new_env = malloc(sizeof(char *) * (i + 2));
	if (!new_env)
		return (NULL);
	i = 0;
	while (old_env[i])
	{
		new_env[i] = old_env[i];
		i++;
	}
	new_env[i] = new_entry;
	new_env[i + 1] = NULL;
	free(old_env);
	return (new_env);
}

int	set_env_var(char *str, t_shell *shell)

{
	char	*eq;
	char	*new_entry;
	int		idx;
	int		key_len;

	eq = ft_strchr(str, '=');
	if (eq)
		key_len = eq - str;
	else
		key_len = ft_strlen(str);
	idx = find_key_index(shell->env_copy, str, key_len);
	if (idx != -1 && !eq)
		return (0);
	new_entry = ft_strdup(str);
	if (!new_entry)
		return (1);
	if (idx != -1)
	{
		free(shell->env_copy[idx]);
		shell->env_copy[idx] = new_entry;
		return (0);
	}
	shell->env_copy = add_to_env(shell->env_copy, new_entry);
	return (shell->env_copy == NULL);
}

int	export(char **args, t_shell *shell)

{
	int	i;
	int	status;

	i = 1;
	status = 0;
	if (!args[1])
		print_export(shell);
	if (!shell->env_copy || !args || !shell)
		return (1);
	while (args[i])
	{
		if (!valid_identifier(args[i]))
		{
			ft_putstr_fd("minishell: export: `", STDERR_FILENO);
			ft_putstr_fd(args[i], STDERR_FILENO);
			ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
			status = 1;
		}
		else
			set_env_var(args[i], shell);
		i++;
	}
	return (status);
}
