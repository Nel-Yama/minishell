/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_dollar.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-yama <nassr.elyamani@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 22:47:53 by nel-yama          #+#    #+#             */
/*   Updated: 2025/12/07 08:54:35 by nel-yama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

char	*ft_dollar_quest(t_arg *arg)
{
	return (ft_itoa(arg->exit_code));
}

char	*ft_dollar_var(char *var, t_arg *arg)
{
	char	*var_expansion;

	var_expansion = ft_get_env(var, arg->shell->envp);
	if (!var_expansion)
		return (ft_strdup(""));
	return (ft_strdup(var_expansion));
}
