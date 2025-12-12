/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/16 19:51:49 by marvin            #+#    #+#             */
/*   Updated: 2025/11/16 19:51:49 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	rem_key(char	*key, t_shell *shell)

{
	int	key_len;
	int	j;
	int	k;

	j = 0;
	k = 0;
	key_len = ft_strlen(key);
	while (shell->env_copy[j])
	{
		if (ft_strncmp(key, shell->env_copy[j], key_len) == 0
			&& shell->env_copy[j][key_len] == '=')
		{
			free(shell->env_copy[j]);
			k = j;
			while (shell->env_copy[k + 1])
			{
				shell->env_copy[k] = shell->env_copy[k + 1];
				k++;
			}
			shell->env_copy[k] = NULL;
			break ;
		}
		j++;
	}
	return (0);
}

int	ft_unset(char **args, t_shell *shell)

{
	int	i;

	i = 1;
	if (!shell->env_copy || !args || !shell)
		return (1);
	while (args[i])
	{
		rem_key(args[i], shell);
		i++;
	}
	return (0);
}
