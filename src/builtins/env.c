/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/16 19:52:06 by marvin            #+#    #+#             */
/*   Updated: 2025/11/16 19:52:06 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	env(t_shell *shell)

{
	int	i;

	i = 0;
	if (!shell->env_copy)
		return (1);
	while (shell->env_copy[i])
	{
		if (ft_strchr(shell->env_copy[i], '='))
			ft_putendl_fd(shell->env_copy[i], STDOUT_FILENO);
		i++;
	}
	return (0);
}
