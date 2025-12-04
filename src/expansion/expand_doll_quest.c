/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 18:44:14 by marvin            #+#    #+#             */
/*   Updated: 2025/11/25 18:44:14 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	find_dollar_quest(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] == '?')
			return (i);
		i++;
	}
	return (-1);
}

static char	*join_three_exit(char *before, char *exit_st, char *after)
{
	char	*tmp;
	char	*result;

	tmp = ft_strjoin(before, exit_st);
	if (!tmp)
		return (NULL);
	result = ft_strjoin(tmp, after);
	free(tmp);
	return (result);
}

static char	*replace_exit_status(char *result, int pos, int exit_stat)
{
	char	*before;
	char	*after;
	char	*exit_st;
	char	*new_result;

	before = ft_substr(result, 0, pos);
	after = ft_substr(result, pos + 2, ft_strlen(result) - pos - 2);
	exit_st = ft_itoa(exit_stat);
	new_result = join_three_exit(before, exit_st, after);
	free(before);
	free(after);
	free(exit_st);
	free(result);
	return (new_result);
}

char	*expand_exit_stat(char *str, int exit_stat)
{
	char	*result;
	int		pos;

	pos = 0;
	result = ft_strdup(str);
	if (!result)
		return (NULL);
	while (1)
	{
		pos = find_dollar_quest(result);
		if (pos == -1)
			break ;
		result = replace_exit_status(result, pos, exit_stat);
		if (!result)
			return (NULL);
	}
	return (result);
}
/*
char	**expand_args(char **args, t_shell *shell)

{
	char	*expanded;
	int		i;

	i = 0;
	while (args[i])
	{
		expanded = expand_exit_stat(args[i], shell->last_exit_status);
		free(args[i]);
		args[i] = expand_vars(expanded, shell->env_copy);
		free(expanded);
		i++;
	}
	return (args);
}
*/