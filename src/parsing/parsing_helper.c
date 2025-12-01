/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-yama <nel-yama@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 23:28:29 by nel-yama          #+#    #+#             */
/*   Updated: 2025/11/25 23:28:29 by nel-yama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	ft_init_arg(t_arg *arg, char **cmd_list)
{
	arg->cmd_count = 0;
	while (cmd_list && cmd_list[arg->cmd_count])
		arg->cmd_count++;
	arg->pid = NULL;
	arg->fd_pipe = NULL;
	arg->cmd = NULL;
	arg->status = NULL;
	arg->exit_code = 0;
}

void	ft_init_cmd(t_cmd *cmd)
{
	cmd->cmd_name = NULL;
	cmd->cmd_arg = NULL;
	cmd->in_redir = 0;
	cmd->out_redir = 0;
	cmd->in_node = NULL;
	cmd->infile_fd = 0;
	cmd->out_node = NULL;
	cmd->outfile_fd = 1;
	cmd->heredoc_fd = -1;
}

static int	ft_set_redirection(char *sub_cmd, int *i, int *redir, char **node)
{
	int	tmp;

	tmp = 0;
	*redir = 1;
	if (sub_cmd[*i] == sub_cmd[*i + 1])
	{
		*redir = 2;
		(*i)++;
	}
	(*i)++;
	ft_skip_blank(sub_cmd, i);
	tmp = *i;
	while (sub_cmd[*i] && sub_cmd[*i] != '<' && sub_cmd[*i] != '>'
		&& !ft_isblank(sub_cmd[*i]))
		(*i)++;
	if (*i == tmp)
		return (0);
	*node = ft_strdup_smart(&sub_cmd[tmp], *i - tmp);
	if (!(*node))
		return (1);
	return (0);
}

int	ft_parse_redirection(t_cmd *cmd, char *sub_cmd, int *i)
{
	if (sub_cmd[*i] == '<')
	{
		if (ft_set_redirection(sub_cmd, i, &cmd->in_redir, &cmd->in_node))
			return (1);
	}
	else if (sub_cmd[*i] == '>')
	{
		if (ft_set_redirection(sub_cmd, i, &cmd->out_redir, &cmd->out_node))
			return (1);
	}
	ft_skip_blank(sub_cmd, i);
	return (0);
}

int	ft_parse_cmd_args(t_cmd *cmd, char *sub_cmd, int *i)
{
	int	tmp;

	ft_skip_blank(sub_cmd, i);
	tmp = *i;
	while (sub_cmd[*i] && sub_cmd[*i] != '<' && sub_cmd[*i] != '>')
		(*i)++;
	if (*i == tmp)
		return (0);
	cmd->cmd_name = ft_strdup_smart(&sub_cmd[tmp], *i - tmp);
	if (!cmd->cmd_name)
		return (1);
	return (0);
}
