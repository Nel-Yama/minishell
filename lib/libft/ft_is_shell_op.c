/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_shell_op.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-yama <nel-yama@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 16:55:45 by nel-yama          #+#    #+#             */
/*   Updated: 2025/04/27 16:55:45 by nel-yama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief : check if a character is a shell operator character 
           (including &, |, ;, etc.)
 * @param c : char to check if it's an operator or not.
 * @return : 1 if c is an op char, 0 otherwise;
 * shell operator chars in ascii are as follow : 
 * '&', ASCII 38
 * '(', ASCII 40
 * ')', ASCII 41
 * ';', ASCII 59
 * '|', ASCII 124
 */
int	ft_is_shell_op(int c)
{
	unsigned char	uc;

	uc = (unsigned char)c;
	if (uc == '&' || uc == '(' || uc == ')' || uc == ';' || uc == '|')
		return (1);
	return (0);
}
