/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_vars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 21:21:28 by marvin            #+#    #+#             */
/*   Updated: 2025/11/26 21:21:28 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	get_var_name_len(char *str)
{
	int	len;

	len = 0;
	if (str[0] == '{')
	{
		str++;
		while (str[len] && str[len] != '}')
			len++;
		return (len);
	}
	while (str[len] && (ft_isalnum(str[len]) || str[len] == '_'))
		len++;
	return (len);
}

char	*get_env_varue(char *var_name, char **env)
{
	int		i;
	int		len;
	char	*value;

	if (!var_name || !env)
		return (ft_strdup(""));
	len = ft_strlen(var_name);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], var_name, len) == 0 && env[i][len] == '=')
		{
			value = ft_strdup(env[i] + len + 1);
			return (value);
		}
		i++;
	}
	return (ft_strdup(""));
}

char	*extract_var(char *str)
{
	int		len;
	int		start;
	char	*name;

	start = 0;
	if (str[0] == '{')
		start = 1;
	len = get_var_name_len(str);
	if (len == 0)
		return (NULL);
	name = ft_substr(str, start, len);
	return (name);
}

int	find_dollar_var(char *str)

{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			if (str[i + 1] == '?')
			{
				i += 2;
				continue ;
			}
			if (str[i + 1] == '{' || (ft_isalnum(str[i + 1])
					|| str[i + 1] == '_'))
				return (i);
		}
		i++;
	}
	return (-1);
}

int	get_dollar_len(char *str)

{
	int	len;

	len = 1;
	if (str[0] == '{')
	{
		len++;
		while (str[len] && str[len] != '}')
			len++;
		if (str[len] == '}')
			len++;
	}
	else
	{
		while (str[len] && (ft_isalnum(str[len]) || str[len] == '_'))
			len++;
	}
	return (len);
}
