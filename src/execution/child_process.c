/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dirituay <dirituay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 21:02:46 by dirituay          #+#    #+#             */
/*   Updated: 2025/08/25 21:50:50 by dirituay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// maneja builtins cuando se ejecutan en el hijo(pipes)
void	built_child(t_data *data, t_cmd *cmd_node, int *pipe)
{
	(void)pipe;
	go_builtins(-1, -1, data, cmd_node);
	free_total(data, 0);
	exit(data->exit_code);
}

void	close_inherited_pipes(int *pips_fds, t_cmd *cmd_node)
{
	if (pips_fds[0] >= 0 && pips_fds[0] != cmd_node->pipe_read)
		close(pips_fds[0]);
	if (pips_fds[1] >= 0 && pips_fds[1] != cmd_node->pipe_write)
		close(pips_fds[1]);
}

// ejecuta comandos externos
void	cmd_exce_child(t_data *data, t_cmd *cmd_node)
{
	char	*cmd_path;
	char	**env_arr;

	cmd_path = validate_and_get_path(data, cmd_node->argv[0]);
	if (!cmd_path)
	{
		free_total(data, data->exit_code);
		exit(data->exit_code);
	}
	env_arr = env_list_to_array(data->env);
	if (!env_arr)
	{
		free(cmd_path);
		free_total(data, 0);
		ft_putstr_fd(STDERR_FILENO, "minishell: malloc error\n");
		exit(1);
	}
	execve(cmd_path, cmd_node->argv, env_arr);
	ft_putstr_fd(STDERR_FILENO, "minishell: execve failed\n");
	free(cmd_path);
	free_arr(env_arr);
	free_total(data, 0);
	exit(127);
}

// dsp de q fork duplica el minishell, ejecuta el comando en el hijo
void	child_process(t_data *data, t_cmd *cmd_node, int prev_read_fd,
		int *pipe)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	signal(SIGTSTP, SIG_IGN);
	if (cmd_node->has_error)
		exit(1);
	if (!cmd_node->argv || !cmd_node->argv[0])
	{
		free_total(data, 0);
		exit(0);
	}
	cmd_node->pipe_read = prev_read_fd;
	handle_all_redirections(cmd_node, data, pipe);
	if (is_builtin(cmd_node->argv[0]))
		built_child(data, cmd_node, pipe);
	else
		cmd_exce_child(data, cmd_node);
	exit(data->exit_code);
}

//inicio de execute_single_cmd
void	setup_pipes_and_fork(t_data *data, t_cmd *cmd, int *prev_read_fd,
		int *pipe_fds)
{
	cmd->pipe_read = *prev_read_fd;
	if (*prev_read_fd != -1)
		cmd->pipe_in = 1;
	if (cmd->next)
	{
		if (pipe(pipe_fds) == -1)
		{
			handle_pipe_error(data, *prev_read_fd);
			return ;
		}
		cmd->pipe_write = pipe_fds[1];
		cmd->pipe_out = 1;
	}
}
