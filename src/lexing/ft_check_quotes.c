/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-yama <nel-yama@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 11:32:31 by nel-yama          #+#    #+#             */
/*   Updated: 2025/11/18 11:32:31 by nel-yama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	ft_check_quotes(char *s)
{
	int	i;

	i = 0;
	while (s && s[i])
	{
		ft_skip_unquoted(s, &i);
		if (ft_skip_quoted(s, &i))
		{
			printf ("minishell: syntax error unclosed quote\n");
			return (1);
		}
	}
	return (0);
}

int	ft_chk_illegal_chars(char *s)
{
	int	i;

	i = 0;
	while (s && s[i])
	{
		if (is_char_in_str(ILLEGAL_CHARS, s[i]))
		{
			printf ("minishell: syntax error illegal char '%c'\n", s[i]);
			return (1);
		}
		i++;
	}
	return (0);
}
