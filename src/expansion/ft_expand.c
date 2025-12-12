/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-yama <nassr.elyamani@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 20:22:30 by nel-yama          #+#    #+#             */
/*   Updated: 2025/12/09 00:47:23 by nel-yama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static int	ft_exp_process_quote(char **res, char *line, int *i, int *start)
{
	if (line[*i] == '\'')
	{
		ft_exp_copy_literal(res, line, i, *start);
		ft_exp_single_quotes(res, line, i);
		*start = *i;
		return (1);
	}
	return (0);
}

static int	ft_exp_process_dollar(t_arg *arg, char **res, char *line, int *i)
{
	int	start;

	start = *i;
	if (line[*i] == '$')
	{
		if (line[*i + 1] == '\0' || is_char_in_str(SPECIAL_CHAR, line[*i + 1]))
		{
			ft_exp_copy_literal(res, line, i, start);
			ft_exp_append_chunk(res, "$");
			(*i)++;
		}
		else
			ft_exp_dollar(arg, line + *i, res, i);
		return (1);
	}
	return (0);
}

char	*ft_expand(char **line, t_arg *arg)
{
	int		i;
	int		start;
	char	*res;

	if (!line || !(*line))
		return (NULL);
	res = ft_strdup("");
	i = 0;
	start = 0;
	while ((*line)[i])
	{
		if (ft_exp_process_quote(&res, *line, &i, &start))
			continue ;
		while ((*line)[i] && (*line)[i] != '$' && (*line)[i] != '\'')
			i++;
		ft_exp_copy_literal(&res, *line, &i, start);
		start = i;
		if (ft_exp_process_dollar(arg, &res, *line, &i))
			start = i;
	}
	if ((*line)[start])
		ft_exp_append_chunk(&res, *line + start);
	free(*line);
	return (res);
}
