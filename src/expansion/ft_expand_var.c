/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_var.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-yama <nassr.elyamani@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 22:55:02 by nel-yama          #+#    #+#             */
/*   Updated: 2025/12/07 14:04:07 by nel-yama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	ft_check_braces(char *var)
{
	int	i;

	i = 0;
	if (var[i] != '{')
		return (0);
	i++;
	if (!var[i])
		return (1);
	if (var[i] == '?')
		i++;
	else
	{
		while (var[i] && (ft_isalnum(var[i]) || var[i] == '_') && var[i] != '?')
			i++;
	}
	if (var[i] != '}')
		return (1);
	return (0);
}

char	*ft_get_expand(char *var, t_arg *arg, int *i)
{
	char	*tmp;
	char	*expand;
	int		j;

	j = *i;
	if (var[*i] == '?')
		(*i)++;
	else
	{
		while (var[*i] && (ft_isalnum(var[*i]) || var[*i] == '_'))
			(*i)++;
	}
	tmp = ft_strldup(var + j, *i - j);
	if (!tmp)
		return (NULL);
	if (ft_strcmp(tmp, "?") == 0)
		expand = ft_dollar_quest(arg);
	else
		expand = ft_dollar_var(tmp, arg);
	free(tmp);
	return (expand);
}

static void	ft_incr_idx(int *idx, int i)
{
	if (i == 0)
		*idx += 1;
	else
		*idx += i;
}

char	*ft_expand_var(t_arg *arg, char *var, int *idx)
{
	int		i;
	char	*expand;

	i = 0;
	if (ft_check_braces(var))
		return (ft_strdup(""));
	if (var[i] == '{')
		i++;
	if (!ft_isalpha(var[i]) && var[i] != '_' && var[i] != '?')
	{
		ft_incr_idx(idx, i);
		return (ft_strdup(""));
	}
	expand = ft_get_expand(var, arg, &i);
	if (var[i] == '}')
		*idx += i + 1;
	else
		*idx += i;
	if (!expand)
		return (ft_strdup(""));
	return (expand);
}
