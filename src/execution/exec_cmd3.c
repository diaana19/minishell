/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dirituay <dirituay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 19:27:34 by dirituay          #+#    #+#             */
/*   Updated: 2025/07/23 22:27:06 by dirituay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	close_cmd_files(t_cmd *cmd)
{
	if (cmd->infile_fd != -1)
		close(cmd->infile_fd);
	if (cmd->outfile_fd != -1)
		close(cmd->outfile_fd);
}

static void	close_opened_files(t_data *data, int opened_count)
{
	t_cmd	*close_node;
	int		j;

	close_node = data->cmds_list;
	j = 0;
	while (j < opened_count)
	{
		close_cmd_files(close_node);
		close_node = close_node->next;
		j++;
	}
}

static bool	open_all_redirections(t_data *data, int cmd_count)
{
	t_cmd	*temp_node_for_redirs;
	int		temp_i;

	temp_node_for_redirs = data->cmds_list;
	temp_i = 0;
	while (temp_i < cmd_count)
	{
		if (!open_redirections_in_parent(temp_node_for_redirs, data))
		{
			close_opened_files(data, temp_i);
			return (false);
		}
		temp_node_for_redirs = temp_node_for_redirs->next;
		temp_i++;
	}
	return (true);
}

bool	launch_commands(t_data *data, t_cmd *current_cmd, int *pip,
		int cmd_count)
{
	if (cmd_count == 1 && current_cmd->argv && current_cmd->argv[0]
		&& is_builtin(current_cmd->argv[0]))
	{
		if (handle_built_parent(data, current_cmd))
			return (true);
	}
	return (exec_pipe_cmds(data, current_cmd, pip, cmd_count));
}

bool	execution(t_data *data)
{
	t_cmd	*current_cmd;
	t_cmd	*tmp;
	int		*pip;
	int		cmd_count;

	pip = data->pipe;
	current_cmd = data->cmds_list;
	tmp = current_cmd;
	cmd_count = count_cmds(data->cmds_list);
	if (!open_all_redirections(data, cmd_count))
		return (false);
	while (tmp)
	{
		if (!tmp->argv || !tmp->argv[0])
		{
			if (tmp->infile_fd >= 0)
				close(tmp->infile_fd);
			if (tmp->outfile_fd >= 0)
				close(tmp->outfile_fd);
			tmp->infile_fd = -1;
			tmp->outfile_fd = -1;
		}
		tmp = tmp->next;
	}
	return (launch_commands(data, current_cmd, pip, cmd_count));
}
