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

void	ft_swap(char **a, char **b)

{
	char	*tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

int	ft_putenv(char **envcpy)

{
	int		i;
	char	*eq;

	i = 0;
	while (envcpy[i])
	{
		eq = ft_strchr(envcpy[i], '=');
		if (!eq)
		{
			ft_putstr_fd("export ", STDOUT_FILENO);
			ft_putendl_fd(envcpy[i], STDOUT_FILENO);
			i++;
			continue;
		}
		else
		{
			*eq = '\0';
			ft_putstr_fd("export ", STDOUT_FILENO);
			ft_putstr_fd(envcpy[i], STDOUT_FILENO);
			ft_putstr_fd("=\"", STDOUT_FILENO);
			ft_putstr_fd(eq + 1, STDOUT_FILENO);
			ft_putendl_fd("\"", STDOUT_FILENO);
			*eq = '=';
		}
		i++;
	}
	return (0);
}

int	print_export(t_shell *shell)

{
	int		i;
	int		j;
	int		len;
	char	**cpy_env;

	i = 0;
	j = 0;
	len = 0;
	cpy_env = copy_env(shell->env_copy);
	while (cpy_env[len])
		len++;
	while (i < len - 1)
	{
		j = 0;
		while (j < len - 1 - i)
		{
			if (ft_strcmp(cpy_env[j], cpy_env[j + 1]) > 0)
				ft_swap(&cpy_env[j], &cpy_env[j + 1]);
			j++;
		}
		i++;
	}
	ft_putenv(cpy_env);
	free_env(cpy_env);
	return (0);
}

int	find_key_index(t_shell *shell, const char *key)
{
	int	i;
	int	key_len;

	i = 0;
	key_len = ft_strlen(key);
	while (shell->env_copy[i])
	{
		if (ft_strncmp(shell->env_copy[i], key, key_len) == 0
			&& (shell->env_copy[i][key_len] == '='
				|| shell->env_copy[i][key_len] == '\0'))
			return (i);
		i++;
	}
	return (-1);
}

int	append_bare_key(t_shell *shell, const char *key)
{
	int		i;
	int		size;
	char	*new_entry;
	char	**new_env;

	if (!shell || !key)
		return (1);
	if (find_key_index(shell, key) != -1)
		return (0);

	new_entry = ft_strdup(key);
	if (!new_entry)
		return (1);

	size = 0;
	while (shell->env_copy[size])
		size++;

	new_env = malloc(sizeof(char *) * (size + 2));
	if (!new_env)
	{
		free(new_entry);
		return (1);
	}
	i = 0;
	while (i < size)
	{
		new_env[i] = shell->env_copy[i];
		i++;
	}
	new_env[size] = new_entry;
	new_env[size + 1] = NULL;
	free(shell->env_copy);
	shell->env_copy = new_env;
	return (0);
}

int	append_var_env(t_shell *shell, char *key, char *value)

{
	int		i;
	int		size;
	int		key_len;
	char	*tmp;
	char	*new_entry;
	char	**new_env;

	i = 0;
	size = 0;
	if (!shell || !key)
		return (1);
	if (!value)
		value = "";
	key_len = ft_strlen(key);
	tmp = ft_strjoin(key, "=");
	new_entry = ft_strjoin(tmp, value);
	free(tmp);
	while (shell->env_copy[i])
	{
		if (ft_strncmp(shell->env_copy[i], key, key_len) == 0
				&& (shell->env_copy[i][key_len] == '=' 
				|| shell->env_copy[i][key_len] == '\0'))
		{
			free(shell->env_copy[i]);
			shell->env_copy[i] = new_entry;
			return (0);
		}
		i++;
	}
	while (shell->env_copy[size])
		size++;
	new_env = malloc(sizeof(char *) * (size + 2));
	if (!new_env)
	{
		free(new_entry);
		return (1);
	}
	i = 0;
	while (i < size)
	{
		new_env[i] = shell->env_copy[i];
		i++;
	}
	new_env[size] = new_entry;
	new_env[size + 1] = NULL;
	free(shell->env_copy);
	shell->env_copy = new_env;
	return (0);
}

int	set_env_var(char *str, t_shell *shell)

{
	int		ret_val;
	char	*eq;
	char	*key;
	char	*value;

	if (!shell || !str)
		return (1);
	eq = ft_strchr(str, '=');
	if (eq)
	{
		key = ft_substr(str, 0, eq - str);
		if (!key)
			return (1);
		value = eq + 1;
		ret_val = append_var_env(shell, key, value);
		free(key);
		return (ret_val);
	}
	else
		return (append_bare_key(shell, str));
}

int	export(char **args, t_shell *shell)

{
	int	i;
	int	status;

	i = 1;
	status = 0;
	if (!args[1])
	{
		print_export(shell);
		return (0);
	}
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
			set_env_var(args[i] , shell);
		i++;
	}
	return (status);
}
