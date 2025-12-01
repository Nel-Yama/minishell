/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ismeta_char.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-yama <nel-yama@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 16:55:45 by nel-yama          #+#    #+#             */
/*   Updated: 2025/04/27 16:55:45 by nel-yama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief : check if a character is a meta character 
           (including &, |, ;, etc.)
 * @param c : char to check if it's a meta char or not.
 * @return : 1 if c is a meta char, 0 otherwise;
 * meta chars in ascii are as follow : 
 * Tab ('\t', ASCII 9)
 * Line feed ('\n', ASCII 10)
 * Space (' ', ASCII 32)
 * '&', ASCII 38
 * '(', ASCII 40
 * ')', ASCII 41
 * ';', ASCII 59
 * '<', ASCII 60
 * '>', ASCII 62
 * '|', ASCII 124
 */
int	ft_ismeta_char(int c)
{
	unsigned char	uc;

	uc = (unsigned char)c;
	if (uc == '\t' || uc == '\n' || uc == ' ' || uc == '&' || uc == '('
		|| uc == ')' || uc == ';' || uc == '<' || uc == '>' || uc == '|')
		return (1);
	return (0);
}
