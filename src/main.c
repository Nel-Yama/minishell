/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-yama <nassr.elyamani@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 20:36:52 by nel-yama          #+#    #+#             */
/*   Updated: 2025/12/01 00:37:13 by nel-yama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	g_signal = 0;

void sigint_handler(int sig)
{
	g_signal = sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

int	main(int ac, char **av, char **envp)
{
	t_arg	arg;
	t_cmd	*cmd;
	char	*line;
	//char	**cmds;
	//int		i;
	//t_shell	shell;

	//shell.last_exit_status = 0;
	//shell.envp = envp;
	//shell.env_copy = copy_env(envp);
	//if (!shell.env_copy)
	//	return (1);
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
		if (line[0] == '\0')
		{
			free(line);
			continue ;
		}
		add_history(line);
		if (ft_syntax_lexing(line))
		{
			printf("minishell> Syntax Error");
			continue ;
		}
		if (ft_cmd_line_parsing(line, &arg, &cmd))
		{
			printf("minishell> Syntax Error");
			continue ;
		}
		create_child_process(&arg);
		run_children(&arg, envp);
		free(line);
		end_main(&arg);
		//i = 0;
		//printf("|cmds[%d] : %s|\n", i, cmds[i]);
		//free(cmds);
	}
	return (0);
}
