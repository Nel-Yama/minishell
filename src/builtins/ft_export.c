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
		if (str[i] == '+' && str[i + 1] == '=')
			break ;
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
	char	*new_entry;
	char	*key;
	int		idx;

	key = get_key(str);
	if (!key)
		return (1);
	idx = find_key_index(shell->env_copy, key, ft_strlen(key));
	if (idx != -1 && !ft_strchr(str, '='))
		return (free(key), 0);
	if (is_append_mode(str) && idx != -1)
		return (free(key), handle_append(str, idx, shell));
	new_entry = prepare_export_entry(str, key);
	free(key);
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

int	ft_export(char **args, t_shell *shell)

{
	int	i;
	int	status;

	i = 1;
	status = 0;
	if (!shell->env_copy || !args || !shell)
		return (1);
	if (!args[1])
		return (print_export(shell));
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
