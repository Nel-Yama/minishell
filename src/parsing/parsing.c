/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-yama <nassr.elyamani@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 22:28:18 by nel-yama          #+#    #+#             */
/*   Updated: 2025/12/11 09:17:51 by nel-yama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static int	ft_parse_subcmd(t_cmd *cmd, char *sub_cmd)
{
	int	i;

	ft_init_cmd(cmd);
	i = 0;
	while (sub_cmd[i])
	{
		ft_skip_blank(sub_cmd, &i);
		if (!sub_cmd[i])
			return (0);
		if (sub_cmd[i] == '<' || sub_cmd[i] == '>')
		{
			if (ft_parse_redirection(cmd, sub_cmd, &i))
				break ;
			continue ;
		}
		else if (ft_parse_cmd_args(cmd, sub_cmd, &i))
			return (1);
	}
	return (0);
}

int	ft_cmd_line_parsing(char *line, t_arg *arg, t_cmd **cmd)
{
	char	**cmd_list;
	int		i;

	cmd_list = ft_split_smart(line, "|");
	ft_init_arg(arg, cmd_list);
	*cmd = malloc (arg->cmd_count * sizeof(t_cmd));
	if (!cmd)
		return (free(cmd_list), 1);
	i = 0;
	while (cmd_list && cmd_list[i])
	{
		if (ft_parse_subcmd(&cmd[0][i], cmd_list[i]))
		{
			free_split(cmd_list);
			return (1);
		}
		i++;
	}
	free_split(cmd_list);
	arg->cmd = *cmd;
	get_here_doc(arg);
	return (0);
}
