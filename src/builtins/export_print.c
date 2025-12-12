/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 16:52:28 by marvin            #+#    #+#             */
/*   Updated: 2025/12/01 16:52:28 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void	sort_env(char **env, int len)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (i < len - 1)
	{
		j = 0;
		while (j < len - 1 - i)
		{
			if (ft_strcmp(env[j], env[j + 1]) > 0)
			{
				tmp = env[j];
				env[j] = env[j + 1];
				env[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
}

static void	print_entry(char *entry)
{
	char	*eq;

	ft_putstr_fd("export ", 1);
	eq = ft_strchr(entry, '=');
	if (!eq)
		ft_putendl_fd(entry, 1);
	else
	{
		*eq = '\0';
		ft_putstr_fd(entry, 1);
		ft_putstr_fd("=\"", 1);
		ft_putstr_fd(eq + 1, 1);
		ft_putendl_fd("\"", 1);
		*eq = '=';
	}
}

int	print_export(t_shell *shell)
{
	char	**sorted;
	int		i;

	sorted = copy_env(shell->env_copy);
	if (!sorted)
		return (1);
	i = 0;
	while (sorted[i])
		i++;
	sort_env(sorted, i);
	i = 0;
	while (sorted[i])
		print_entry(sorted[i++]);
	free_env(sorted);
	return (0);
}
