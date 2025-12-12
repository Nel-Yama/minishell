/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-yama <nassr.elyamani@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 23:28:29 by nel-yama          #+#    #+#             */
/*   Updated: 2025/12/12 18:05:44 by nel-yama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void	ft_increment_char(char *sub_cmd, int *i)
{
	if (ft_isquote(sub_cmd[*i]))
		ft_skip_quoted(sub_cmd, i);
	else
		(*i)++;
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
		ft_increment_char(sub_cmd, i);
	if (*i == tmp)
		return (0);
	*node = ft_strdup_smart(&sub_cmd[tmp], *i - tmp);
	if (!(*node))
		return (1);
	return (0);
}

/*
 * Function to parse a redirection token.
 * It calls helpers to check file access and tokenization.
 * Only the last valid file is stored (Check All, Keep Last).
 * Returns 0 on success, 1 on parsing or file access error.
 */
int	ft_parse_redirection(t_cmd *cmd, char *sub_cmd, int *i)
{
	if (sub_cmd[*i] == '<')
	{
		if (cmd->in_node)
			free(cmd->in_node);
		if (ft_set_redirection(sub_cmd, i, &cmd->in_redir, &cmd->in_node))
			return (free(cmd->in_node), 1);
		if (check_file_access(0, cmd->in_redir, cmd->in_node))
			return (free(cmd->in_node), 1);
	}
	else if (sub_cmd[*i] == '>')
	{
		if (cmd->out_node)
			free(cmd->out_node);
		if (ft_set_redirection(sub_cmd, i, &cmd->out_redir, &cmd->out_node))
			return (free(cmd->out_node), 1);
		if (check_file_access(1, cmd->out_redir, cmd->out_node))
			return (free(cmd->out_node), 1);
	}
	ft_skip_blank(sub_cmd, i);
	return (0);
}

int	ft_parse_cmd_args(t_cmd *cmd, char *sub_cmd, int *i)
{
	int		tmp;
	char	*tmp_str;
	char	*tmp_cmd;

	ft_skip_blank(sub_cmd, i);
	tmp = *i;
	if (!cmd->cmd_name)
		cmd->cmd_name = ft_strdup("");
	while (sub_cmd[*i] && sub_cmd[*i] != '<' && sub_cmd[*i] != '>')
		ft_increment_char(sub_cmd, i);
	if (*i == tmp)
		return (0);
	tmp_str = ft_strldup(&sub_cmd[tmp], *i - tmp);
	if (!tmp_str)
		return (1);
	tmp_cmd = cmd->cmd_name;
	cmd->cmd_name = ft_strjoin(cmd->cmd_name, tmp_str);
	free(tmp_str);
	free(tmp_cmd);
	return (0);
}
