/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-yama <nassr.elyamani@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 16:31:01 by nel-yama          #+#    #+#             */
/*   Updated: 2025/12/10 18:20:26 by nel-yama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	is_empty_line(char *line)
{
	int	i;

	if (!line)
		return (1);
	i = 0;
	while (line[i])
	{
		if (!ft_isspace(line[i]))
			return (0);
		i++;
	}
	return (1);
}

int	ft_shell_init(t_arg *arg, t_shell *shell, char **envp)
{
	arg->shell = shell;
	arg->exit_code = 0;
	shell->last_exit_status = &arg->exit_code;
	shell->envp = envp;
	shell->env_copy = copy_env(envp);
	if (!shell->env_copy)
		return (1);
	increment_shlvl(shell);
	return (0);
}

int	ft_lex_parse_exec(t_arg *arg, char **line, t_cmd **cmd)
{
	if (*line[0] == '\0' || is_empty_line(*line))
	{
		free(*line);
		return (1);
	}
	add_history(*line);
	if (ft_syntax_lexing(*line))
	{
		printf("minishell> Syntax Error\n");
		return (1);
	}
	*line = ft_expand(line, arg);
	if (ft_cmd_line_parsing(*line, arg, cmd))
	{
		printf("minishell> Error\n");
		return (1);
	}
	return (0);
}
