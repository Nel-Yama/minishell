/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-yama <nassr.elyamani@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 23:29:39 by nel-yama          #+#    #+#             */
/*   Updated: 2025/12/03 18:41:17 by nel-yama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void	ft_here_doc(t_arg *arg, t_cmd *cmd)
{
	char	*line;
	int		heredoc_pipe_fd[2];

	if (pipe(heredoc_pipe_fd) == -1)
		exit_error(arg, "minishell: heredoc pipe Failed");
	cmd->heredoc_fd = heredoc_pipe_fd[0];
	while (1)
	{
		line = readline("heredoc>");
		if (!line)
			break ;
		if (ft_strcmp(line, cmd->in_node) == 0)
		{
			free(line);
			break ;
		}
		write(heredoc_pipe_fd[1], line, ft_strlen(line));
		write(heredoc_pipe_fd[1], "\n", 1);
		free(line);
	}
	close(heredoc_pipe_fd[1]);
}

void	get_here_doc(t_arg *arg)
{
	int		i;
	t_cmd	*cmd;

	cmd = arg->cmd;
	i = 0;
	while (i < arg->cmd_count)
	{
		if (cmd[i].in_redir == 2)
			ft_here_doc(arg, &cmd[i]);
		i++;
	}
}
