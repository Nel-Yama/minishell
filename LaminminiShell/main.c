/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 20:36:52 by nel-yama          #+#    #+#             */
/*   Updated: 2025/12/03 22:36:35 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	g_signal = 0;

void	sigint_handler(int sig)
{
	g_signal = sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

static	int	is_empy_line(char *line)

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

char	**expand_and_split(char *cmd, t_shell *shell)

{
	char	*expanded;
	char	*tmp;
	char	**args;

	expanded = expand_exit_stat(cmd, shell->last_exit_status);
	tmp = expand_vars(expanded, shell->env_copy);
	free(expanded);
	expanded = tmp;
	args = ft_split(expanded, ' ');
	free(expanded);
	return (args);
}

int	main(int ac, char **av, char **envp)
{
	char	*line;
	char	**cmds;
	char	**args;
	int		i;
	int		j;
	t_shell	shell;

	shell.last_exit_status = 0;
	shell.envp = envp;
	shell.env_copy = copy_env(envp);
	if (!shell.env_copy)
		return (1);
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	if (ac != 1 || !av || !envp)
		return (printf("minishell>: wrong input arguments"), 0);
	while (1)
	{
		line = readline("minishell$ > ");
		if (!line)
		{
			ft_putendl_fd("exit", STDERR_FILENO);
			break ;
		}
		if (is_empy_line(line))
		{
			free(line);
			continue ;
		}
		cmds = ft_split_smart(line, "|");
		add_history(line);
		i = 0;
		while (cmds && cmds[i])
		{
			args = expand_and_split(cmds[i], &shell);
			if (args[0] && is_builtin(args[0]))
				shell.last_exit_status = execute_builtin(args, &shell);
			j = 0;
			while (args[j])
			{
				free(args[j]);
				j++;
			}
			free(args);
			free(cmds[i]);
			i++;
		}
		free(cmds);
		free(line);
	}
	rl_clear_history();
	free_env(shell.env_copy);
	return (shell.last_exit_status);
}
