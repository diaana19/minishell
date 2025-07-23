/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dirituay <dirituay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 16:25:36 by dirituay          #+#    #+#             */
/*   Updated: 2025/07/23 22:27:43 by dirituay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// builtins q se ejecutan en el padre cuando no son pipe
bool	handle_built_parent(t_data *data, t_cmd *cmd_node)
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
		return (exec_builtin(data, cmd_node));
}

// conecta la entrada de pipe al comando actual
static void	setup_input_pipe(t_cmd *cmd, int *prev_read_fd)
{
	if (*prev_read_fd != -1 && cmd->pipe_in == 0)
	{
		close(*prev_read_fd);
		*prev_read_fd = -1;
	}
	if (cmd->pipe_in == 1)
		cmd->pipe_read = *prev_read_fd;
	else
		cmd->pipe_read = -1;
}

// errores pipes
static bool	handle_pipe_error(t_data *data, int prev_read_fd)
{
	data->exit_code = 1;
	if (prev_read_fd != -1)
		close(prev_read_fd);
	return (false);
}

// crea el pipe para salida del comando
static bool	setup_output_pipe(t_cmd *cmd, int *pipe_container,
		int *prev_read_fd)
{
	if (cmd->pipe_out == 1)
	{
		if (pipe(pipe_container) == -1)
		{
			ft_putstr_fd(STDERR_FILENO, "minishell: pipe error\n");
			return (false);
		}
		cmd->pipe_write = pipe_container[1];
		*prev_read_fd = pipe_container[0];
	}
	else
		cmd->pipe_write = -1;
	return (true);
}

// crea los pipes y asigna los fds a cada token y cierra los
// extremos del pipe q padre no usa
bool	exec_pipe_cmds(t_data *data, t_cmd *first_cmd, int *temp_pipe_container,
		int cmd_count)
{
	t_cmd	*current_cmd;
	int		i;
	int		prev_pipe_read_end_fd;

	i = 0;
	prev_pipe_read_end_fd = -1;
	current_cmd = first_cmd;
	while (current_cmd != NULL && i < cmd_count)
	{
		setup_input_pipe(current_cmd, &prev_pipe_read_end_fd);
		if (!setup_output_pipe(current_cmd, temp_pipe_container,
				&prev_pipe_read_end_fd))
			return (handle_pipe_error(data, prev_pipe_read_end_fd));
		exec_cmds(data, current_cmd, temp_pipe_container);
		current_cmd = current_cmd->next;
		i++;
	}
	if (prev_pipe_read_end_fd != -1)
		close(prev_pipe_read_end_fd);
	wait_child(data);
	return (true);
}
