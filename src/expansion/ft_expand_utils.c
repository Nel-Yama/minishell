/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-yama <nassr.elyamani@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 16:43:00 by nel-yama          #+#    #+#             */
/*   Updated: 2025/12/07 14:42:54 by nel-yama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	ft_exp_append_chunk(char **result, char *chunk)
{
	char	*tmp;

	tmp = ft_strjoin(*result, chunk);
	free(*result);
	*result = tmp;
}

void	ft_exp_dollar(t_arg *arg, char *dollar_ptr,
			char **res, int *i)
{
	char	*expanded;
	char	*tmp;
	int		skip;

	skip = 0;
	expanded = ft_expand_var(arg, dollar_ptr + 1, &skip);
	tmp = ft_strjoin(*res, expanded);
	free(*res);
	*res = tmp;
	*i += 1 + skip;
}

void	ft_exp_single_quotes(char **res, char *line, int *i)
{
	int		start;
	char	*chunk;

	start = *i;
	(*i)++;
	while (line[*i] && line[*i] != '\'')
		(*i)++;
	if (line[*i] == '\'')
		(*i)++;
	chunk = ft_strldup(line + start, *i - start);
	ft_exp_append_chunk(res, chunk);
	free(chunk);
}

void	ft_exp_copy_literal(char **res, char *line, int *i, int start)
{
	char	*chunk;

	if (*i > start)
	{
		chunk = ft_strldup(line + start, *i - start);
		ft_exp_append_chunk(res, chunk);
		free(chunk);
	}
}
