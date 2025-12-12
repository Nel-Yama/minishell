/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_helper_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-yama <nassr.elyamani@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 16:35:56 by nel-yama          #+#    #+#             */
/*   Updated: 2025/12/11 08:56:27 by nel-yama         ###   ########.fr       */
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

/*
 * Checks if the file specified in the redirection can be opened/created.
 * If successful, the file is closed immediately as we only need the last
 * descriptor open for execution.
 * Returns 0 on success, 1 on error.
 */
int	check_file_access(int type, int redir, char *file_name)
{
	int	fd;

	fd = -1;
	if (type == 0 && redir == 1)
		fd = open(file_name, O_RDONLY);
	else if (type == 1 && redir == 1)
		fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (type == 1 && redir == 2)
		fd = open(file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
	{
		perror(file_name);
		return (1);
	}
	if (fd > 0)
		close(fd);
	return (0);
}

/*
 * Determines the redirection type, parses the filename token,
 * performs the necessary file access check, and returns the filename string.
 * Returns NULL on error or if the filename is missing.
 
static char	*get_and_check_redir_file(char *sub_cmd, int *i, int *type_out)
{
	char	*file_name;
	int		tmp;
	int		type;

	type = 0;
	if (sub_cmd[*i] == '<')
		type = 1;
	else if (sub_cmd[*i] == '>')
		type = 3;
	if (sub_cmd[*i] == sub_cmd[*i + 1])
	{
		type++;
		(*i)++;
	}
	(*i)++;
	ft_skip_blank(sub_cmd, i);
	tmp = *i;
	while (sub_cmd[*i] && sub_cmd[*i] != '<' && sub_cmd[*i] != '>')
		ft_increment_char(sub_cmd, i);
	if (*i == tmp)
		return (NULL);
	file_name = ft_strdup_smart(&sub_cmd[tmp], *i - tmp);
	if (!file_name)
		return (NULL);
	if (check_file_access(type, file_name))
	{
		free(file_name);
		return (NULL);
	}
	*type_out = type;
	return (file_name);
}**/
