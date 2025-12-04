/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 00:00:00 by marvin            #+#    #+#             */
/*   Updated: 2025/12/01 00:00:00 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static char	*join_three_parts(char *before, char *middle, char *after)
{
	char	*tmp;
	char	*result;

	tmp = ft_strjoin(before, middle);
	if (!tmp)
		return (NULL);
	result = ft_strjoin(tmp, after);
	free(tmp);
	return (result);
}
/*
static void	free_expansion_parts(char *before, char *after, char *var_name,
		char*var_value)
{
	free(before);
	free(after);
	free(var_name);
	free(var_value);
}*/

char	*build_expanded_str(char *result, int pos, int doll_len,
		char *var_value)
{
	char	*before;
	char	*after;
	char	*new_result;

	before = ft_substr(result, 0, pos);
	if (!before)
		return (NULL);
	after = ft_strdup(result + pos + doll_len + 1);
	if (!after)
	{
		free(before);
		return (NULL);
	}
	new_result = join_three_parts(before, var_value, after);
	free(before);
	free(after);
	return (new_result);
}

char	*process_one_var(char *result, int pos, char **env)
{
	char	*var_name;
	char	*var_value;
	char	*new_result;
	int		doll_len;

	var_name = extract_var(result + pos + 1);
	if (!var_name)
		return (result);
	var_value = get_env_varue(var_name, env);
	doll_len = get_dollar_len(result + pos + 1);
	new_result = build_expanded_str(result, pos, doll_len, var_value);
	free(var_name);
	free(var_value);
	free(result);
	return (new_result);
}

char	*expand_vars(char *str, char **env)
{
	char	*result;
	int		pos;

	if (!str)
		return (NULL);
	result = ft_strdup(str);
	if (!result)
		return (NULL);
	while (1)
	{
		pos = find_dollar_var(result);
		if (pos == -1)
			break ;
		result = process_one_var(result, pos, env);
		if (!result)
			return (NULL);
	}
	return (result);
}
