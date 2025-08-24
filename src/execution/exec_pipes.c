/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dirituay <dirituay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 14:05:07 by dianarituay       #+#    #+#             */
/*   Updated: 2025/08/24 19:27:40 by dirituay         ###   ########.fr       */
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

void	close_parent_pipes(int prev_read_fd, int *pipe_fds)
{
	if (prev_read_fd != -1)
		close(prev_read_fd);
	if (pipe_fds[1] != -1)
		close(pipe_fds[1]);
}

// cierra fds de file y fds de pipes
void	parent_process(t_cmd *cmd_node)
{
	if (cmd_node->infile_fd != -1)
		close(cmd_node->infile_fd);
	if (cmd_node->outfile_fd != -1)
		close(cmd_node->outfile_fd);
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

// espera a sus hijos y agarra el exit code del ultimo cmd
void	wait_child(t_data *data, int num_cmds)
{
	int		status;
	int		waited;
	pid_t	pid;

	waited = 0;
	if (num_cmds > 0)
	{
		while (waited < num_cmds)
		{
			pid = wait(&status);
			if (pid > 0)
			{
				waited++;
				if (WIFEXITED(status))
					data->exit_code = WEXITSTATUS(status);
				else if (WIFSIGNALED(status))
					data->exit_code = 128 + WTERMSIG(status);
			}
			else
				break ;
		}
	}
	g_signal_pid = 0;
}
