/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isblank.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-yama <nel-yama@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 00:03:26 by nel-yama          #+#    #+#             */
/*   Updated: 2025/11/17 00:03:26 by nel-yama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief : check if a character is a space or tab character 
 * @param c : char to check if it's a blank char or not.
 * @return : 1 if c is a space char, 0 otherwise;
 * space chars in ascii are as follow : 
 * Space (' ', ASCII 32)
 * Tab ('\t', ASCII 9)
 */
int	ft_isblank(int c)
{
	unsigned char	uc;

	uc = (unsigned char)c;
	if (uc == 9 || uc == 32)
		return (1);
	return (0);
}
