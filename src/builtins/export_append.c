/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_append.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 16:11:03 by marvin            #+#    #+#             */
/*   Updated: 2025/12/07 16:11:03 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static char	*join_key_value(char *key, char *value)
{
	char	*tmp;
	char	*res;

	tmp = ft_strjoin(key, "=");
	if (!tmp)
		return (NULL);
	res = ft_strjoin(tmp, value);
	free(tmp);
	return (res);
}

char	*get_key(char *str)
{
	char	*eq;
	int		len;

	eq = ft_strchr(str, '=');
	if (!eq)
		return (ft_strdup(str));
	if (eq > str && *(eq - 1) == '+')
		len = eq - str - 1;
	else
		len = eq - str;
	return (ft_substr(str, 0, len));
}

int	is_append_mode(char *str)
{
	char	*eq;

	eq = ft_strchr(str, '=');
	if (eq && eq > str && *(eq - 1) == '+')
		return (1);
	return (0);
}

char	*prepare_export_entry(char *str, char *key)
{
	if (is_append_mode(str))
		return (ft_strjoin(key, ft_strchr(str, '=')));
	return (ft_strdup(str));
}

int	handle_append(char *str, int idx, t_shell *shell)
{
	char	*old_val;
	char	*new_val;
	char	*key;
	char	*final;

	old_val = ft_strchr(shell->env_copy[idx], '=');
	if (old_val)
		old_val++;
	else
		old_val = "";
	new_val = ft_strjoin(old_val, ft_strchr(str, '=') + 1);
	if (!new_val)
		return (1);
	key = get_key(str);
	if (!key)
		return (free(new_val), 1);
	final = join_key_value(key, new_val);
	free(key);
	free(new_val);
	if (!final)
		return (1);
	free(shell->env_copy[idx]);
	shell->env_copy[idx] = final;
	return (0);
}
