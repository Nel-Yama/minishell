/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_skip_quoted.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-yama <nel-yama@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 01:04:06 by nel-yama          #+#    #+#             */
/*   Updated: 2025/11/17 01:04:06 by nel-yama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_skip_single_quote(char *s, int *i)
{
	char	single_quote;

	single_quote = (char)39;
	if (!s || s[*i] != single_quote)
		return (0);
	(*i)++;
	while (s[*i] && s[*i] != single_quote)
		(*i)++;
	if (!s[*i])
		return (1);
	(*i)++;
	return (0);
}

int	ft_skip_double_quote(char *s, int *i)
{
	char	double_quote;

	double_quote = (char)34;
	if (!s || s[*i] != double_quote)
		return (0);
	(*i)++;
	while (s[*i] && (s[*i] != double_quote || ft_is_escaped(s, *i)))
		(*i)++;
	if (!s[*i])
		return (1);
	(*i)++;
	return (0);
}

int	ft_skip_quoted(char *s, int *i)
{
	if (s[*i] == '\'')
		return (ft_skip_single_quote(s, i));
	if (s[*i] == '\"')
		return (ft_skip_double_quote(s, i));
	return (0);
}

int	ft_skip_unquoted(char *s, int *i)
{
	while (s[*i] && (!ft_isquote(s[*i]) || ft_is_escaped(s, *i)))
		(*i)++;
	return (0);
}
