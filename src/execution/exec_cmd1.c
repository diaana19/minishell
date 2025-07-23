/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dirituay <dirituay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 14:05:07 by dianarituay       #+#    #+#             */
/*   Updated: 2025/07/23 22:28:02 by dirituay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// verifica si es builtin(1) o no (0)
bool	is_builtin(char *cmd)
{
	size_t		i;
	const char	*builtins[] = {"echo", "cd", "pwd", "export", "unset", "env",
		"exit", NULL};

	i = 0;
	if (!cmd)
		return (false);
	while (builtins[i])
	{
		if (ft_strncmp(cmd, builtins[i], ft_strlen(builtins[i]) + 1) == 0)
			return (true);
		i++;
	}
	return (false);
}

// gestiona los fds de los pipes en el padre
static void	parent_process(t_cmd *cmd_node, int *pipe_from_exec_cmds)
{
	(void)pipe_from_exec_cmds;
	if (cmd_node->infile_fd >= 0)
		close(cmd_node->infile_fd);
	if (cmd_node->outfile_fd >= 0)
		close(cmd_node->outfile_fd);
	if (cmd_node->pipe_write >= 0)
	{
		close(cmd_node->pipe_write);
		cmd_node->pipe_write = -1;
	}
	if (cmd_node->pipe_read >= 0)
	{
		close(cmd_node->pipe_read);
		cmd_node->pipe_read = -1;
	}
}

// fork para duplicar y dirigir la ejec. depende si estamos en padre o hijo
bool	exec_cmds(t_data *data, t_cmd *cmd_node, int *pipe)
{
	g_signal_pid = fork();
	if (g_signal_pid < 0)
	{
		ft_putstr_fd(STDERR_FILENO, "minishell: fork error\n");
		data->exit_code = 1;
		return (false);
	}
	else if (g_signal_pid == 0)
	{
		g_signal_pid = 0;
		if (cmd_node->argv && cmd_node->argv[0])
			child_process(data, cmd_node, pipe);
		else
		{
			free_total(data, 0);
			exit(0);
		}
	}
	else
		parent_process(cmd_node, pipe);
	return (true);
}

// cuenta cuantos cmds hay
int	count_cmds(t_cmd *head)
{
	int		count;
	t_cmd	*current;

	count = 0;
	current = head;
	while (current != NULL)
	{
		count++;
		current = current->next;
	}
	return (count);
}

// espera a sus hijos(procesos q ejec. cmds) y limpia lo q usaron
void	wait_child(t_data *data)
{
	int		status;
	int		pid;
	int		len;
	t_cmd	*temp_cmd;

	temp_cmd = data->cmds_list;
	len = count_cmds(temp_cmd);
	while (len--)
	{
		pid = waitpid(0, &status, 0);
		if (pid == g_signal_pid)
		{
			if (WIFEXITED(status))
				data->exit_code = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				data->exit_code = 128 + WTERMSIG(status);
		}
		temp_cmd = temp_cmd->next;
	}
	g_signal_pid = 0;
}
