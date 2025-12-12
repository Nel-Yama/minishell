/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcount_char.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-yama <nassr.elyamani@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 19:53:19 by nel-yama          #+#    #+#             */
/*   Updated: 2025/12/08 20:28:32 by nel-yama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcount_char(const char *s, int len, int c)
{
	int	i;
	int	count;

	if (!s)
		return (0);
	count = 0;
	i = 0;
	while (i < len)
	{
		if (s[i] == c)
			count++;
		i++;
	}
	return (count);
}

int	ft_strcount_char_smart(char *s, int len, int c)
{
	int	i;
	int	count;

	if (!s)
		return (0);
	count = 0;
	i = 0;
	while (i < len)
	{
		if (s[i] == '\"')
		{
			ft_skip_double_quote(s, &i);
			continue ;
		}
		else if (s[i] == '\'')
		{
			ft_skip_single_quote(s, &i);
			continue ;
		}
		else if (s[i] == c)
			count++;
		i++;
	}
	return (count);
}
