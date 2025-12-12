/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup_smart.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-yama <nassr.elyamani@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 20:59:13 by nel-yama          #+#    #+#             */
/*   Updated: 2025/12/07 22:28:10 by nel-yama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_copy_char(char *s2, char *s1, int *i, int *j)
{
	if (s1[*i] == '\"')
	{
		(*i)++;
		while (s1[*i] && s1[*i] != '\"')
		{
			s2[*j] = s1[*i];
			(*j)++;
			(*i)++;
		}
	}
	else if (s1[*i] == '\'')
	{
		(*i)++;
		while (s1[*i] && s1[*i] != '\'')
		{
			s2[*j] = s1[*i];
			(*j)++;
			(*i)++;
		}
	}
	else
	{
		s2[*j] = s1[*i];
		(*j)++;
	}
}

char	*ft_strdup_smart(char *s1, int l)
{
	char	*s2;
	int		i;
	int		j;

	i = ft_strcount_char(s1, l, '\"');
	i += ft_strcount_char_smart(s1, l, '\'');
	s2 = (char *)malloc((l - i + 1) * sizeof(char));
	if (!s2)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i] && i < l)
	{
		ft_copy_char(s2, s1, &i, &j);
		i++;
	}
	s2[j] = '\0';
	return (s2);
}
