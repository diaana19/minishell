/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dirituay <dirituay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 16:25:36 by dirituay          #+#    #+#             */
/*   Updated: 2025/08/24 19:48:48 by dirituay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// builtins q se ejecutan en el padre cuando no son pipe
static bool	handle_built_parent(t_data *data, t_cmd *cmd_node)
{
	if (!ft_strncmp("exit", cmd_node->argv[0], INT_MAX))
	{
		go_builtins(-1, -1, data, cmd_node);
		return (true);
	}
	else if (!cmd_node->redir)
	{
		go_builtins(-1, -1, data, cmd_node);
		return (true);
	}
	else
		return (execution_builtins(data, cmd_node));
}

// errores pipes
bool	handle_pipe_error(t_data *data, int prev_read_fd)
{
	data->exit_code = 1;
	if (prev_read_fd != -1)
		close(prev_read_fd);
	return (false);
}

// Ejecuta un solo comando dentro de un pipeline
static bool	execute_single_command(t_data *data, t_cmd *cmd, int *prev_read_fd)
{
	int	pipe_fds[2];

	pipe_fds[0] = -1;
	pipe_fds[1] = -1;
	setup_pipes_and_fork(data, cmd, prev_read_fd, pipe_fds);
	g_signal_pid = fork();
	if (g_signal_pid < 0)
		return (handle_pipe_error(data, *prev_read_fd));
	else if (g_signal_pid == 0)
		child_process(data, cmd, *prev_read_fd, pipe_fds);
	else
	{
		close_parent_pipes(*prev_read_fd, pipe_fds);
		parent_process(cmd);
	}
	*prev_read_fd = pipe_fds[0];
	return (true);
}

// crea los pipes y forkea, en un pipeline o en un solo cmd
static bool	exec_pipe_commands(t_data *data, t_cmd *first_cmd)
{
	t_cmd	*current_cmd;
	int		prev_read_fd;

	prev_read_fd = -1;
	current_cmd = first_cmd;
	if (!current_cmd->next && is_builtin(current_cmd->argv[0]))
		return (handle_built_parent(data, current_cmd));
	while (current_cmd != NULL)
	{
		if (!execute_single_command(data, current_cmd, &prev_read_fd))
			return (false);
		current_cmd = current_cmd->next;
	}
	if (prev_read_fd != -1)
		close(prev_read_fd);
	wait_child(data, count_cmds(first_cmd));
	return (true);
}

// inicia el pipeline llamando a exec_pipe_cmds
bool	execution(t_data *data)
{
	return (exec_pipe_commands(data, data->cmds_list));
}
