/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 20:36:52 by nel-yama          #+#    #+#             */
/*   Updated: 2025/12/10 17:49:20 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	g_signal = 0;

void	sigint_handler(int sig)
{
	(void)sig;
	g_signal = SIGINT;
	rl_replace_line("", 0);
	write(1, "\n", 1);
	rl_on_new_line();
	rl_redisplay();
}

int	main(int ac, char **av, char **envp)
{
	t_arg	arg;
	t_cmd	*cmd;
	char	*line;
	t_shell	shell;

	if (ac != 1 || !av || !envp || ft_shell_init(&arg, &shell, envp))
		return (1);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		signal(SIGINT, sigint_handler);
		line = readline("minishell$ > ");
		if (!line)
		{
			if (isatty(STDIN_FILENO))
				ft_putendl_fd("exit", STDERR_FILENO);
			break ;
		}
		if (ft_lex_parse_exec(&arg, &line, &cmd))
			continue ;
		ft_run_cmds_process(&arg, &line, envp);
	}
	rl_clear_history();
	free_env(shell.env_copy);
	return (arg.exit_code);
}
