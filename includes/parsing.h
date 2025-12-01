/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-yama <nel-yama@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 22:30:59 by nel-yama          #+#    #+#             */
/*   Updated: 2025/11/17 22:30:59 by nel-yama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

/**
 * Tokens : 0 = None, 1 = Pipe, 2 = redirection, 3 = word
 * quote : 0 = None, 1 = ' or "
 * expecting_word : true if the next non-blank must be a word
 **/
typedef struct s_lexing
{
	int	idx;
	int	quote;
	int	prev_token;
	int	expect_word;
}	t_lexing;

#endif
