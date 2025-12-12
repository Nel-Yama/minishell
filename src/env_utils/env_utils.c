/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/16 19:58:32 by marvin            #+#    #+#             */
/*   Updated: 2025/11/16 19:58:32 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

char	**copy_env(char **envp)
{
	int		i;
	int		count;
	char	**new_env;

	count = 0;
	while (envp[count])
		count++;
	new_env = malloc(sizeof(char *) * (count + 1));
	if (!new_env)
		return (NULL);
	i = 0;
	while (i < count)
	{
		new_env[i] = ft_strdup(envp[i]);
		if (!new_env[i])
		{
			free_env(new_env);
			return (NULL);
		}
		i++;
	}
	new_env[i] = NULL;
	return (new_env);
}

void	free_env(char **env)
{
	int	i;

	if (!env)
		return ;
	i = 0;
	while (env[i])
	{
		free(env[i]);
		i++;
	}
	free(env);
}

char	*get_env_value(char *key, t_shell *shell)
{
	int	i;
	int	key_len;

	if (!key || !shell->env_copy)
		return (NULL);
	key_len = ft_strlen(key);
	i = 0;
	while (shell->env_copy[i])
	{
		if (ft_strncmp(shell->env_copy[i], key, key_len) == 0
			&& shell->env_copy[i][key_len] == '=')
			return (ft_strdup(shell->env_copy[i] + key_len + 1));
		i++;
	}
	return (NULL);
}

void	increment_shlvl(t_shell *shell)
{
	char	*val;
	char	*new_val_str;
	int		lvl;
	char	*new_entry;

	val = get_env_value("SHLVL", shell);
	if (!val || !*val || !ft_isdigit(*val))
		lvl = 1;
	else
		lvl = ft_atoi(val) + 1;
	if (val)
		free(val);
	if (lvl < 0)
		lvl = 0;
	new_val_str = ft_itoa(lvl);
	if (!new_val_str)
		return ;
	new_entry = ft_strjoin("SHLVL=", new_val_str);
	free(new_val_str);
	if (!new_entry)
		return ;
	set_env_var(new_entry, shell);
	free(new_entry);
}
