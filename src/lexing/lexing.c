/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-yama <nassr.elyamani@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 21:32:36 by nel-yama          #+#    #+#             */
/*   Updated: 2025/12/11 08:37:18 by nel-yama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void	syntax_error(char *s, char c)
{
	printf("minishell: syntax error near %s '%c'\n", s, c);
}

static int	ft_check_control_op_rules(char *s, int *i, int *last_token)
{
	if (s[*i] != '|' || *last_token == 1)
		return (1);
	(*i)++;
	*last_token = 1;
	return (0);
}

static int	ft_lexing_metachar(char *s, int *i, int *last_token)
{
	if (is_char_in_str(CONTROL_OP, s[*i]))
	{
		if (!(*last_token))
			return (1);
		if (ft_check_control_op_rules(s, i, last_token))
			return (1);
	}
	else if (s[*i] == '<' || s[*i] == '>')
	{
		if (*last_token == 2)
			return (1);
		if (s[*i] == s[*i + 1])
			(*i)++;
		(*i)++;
		*last_token = 2;
	}
	return (0);
}

static int	ft_unquoted_lexing(char *s, int *i, int *last_token)
{
	if (is_char_in_str(META_CHAR1, s[*i]))
	{
		if (ft_lexing_metachar(s, i, last_token))
			return (syntax_error("unexpected token", s[*i]), 1);
		else
			return (0);
	}
	if (!s[*i])
		return (0);
	*last_token = 3;
	ft_skip_word(s, i);
	return (0);
}

/**
 * Tokens : None = 0, Pipe = 1, redirection = 2, word = 3
 * expecting_word : true if the next non-blank must be a word
 **/
int	ft_syntax_lexing(char *s)
{
	int	i;
	int	last_token;

	if (ft_check_quotes(s) || ft_chk_illegal_chars(s))
		return (1);
	i = 0;
	last_token = 0;
	while (s && s[i])
	{
		if (ft_isquote(s[i]))
		{
			ft_skip_quoted(s, &i);
			last_token = 3;
		}
		else if (ft_isblank(s[i]))
			ft_skip_blank(s, &i);
		else if (ft_unquoted_lexing(s, &i, &last_token))
			return (1);
	}
	if (last_token == 1 || last_token == 2)
		return (printf("minishell: invalid end of command\n"), 1);
	return (0);
}
