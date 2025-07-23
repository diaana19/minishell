/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lellanos <lellanos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 21:33:21 by dirituay          #+#    #+#             */
/*   Updated: 2025/07/23 21:49:03 by lellanos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// verifica si la ruta es un archivo q execve pueda ejecutar
bool	check_path(const char *cmd_path, const char *cmd_name, t_data *data)
{
	struct stat	path_stat;

	if (stat(cmd_path, &path_stat) == -1)
		return (false);
	if (S_ISDIR(path_stat.st_mode))
	{
		errno = EISDIR;
		cmd_error(cmd_name, 127);
		data->exit_code = 127;
		return (false);
	}
	if (!S_ISREG(path_stat.st_mode))
	{
		cmd_error(cmd_name, 127);
		data->exit_code = 127;
		return (false);
	}
	return (true);
}

// usa find_cmd_path para buscar el path y verifica q no es un directory
bool	validate_cmd_path(char **cmd_path, t_data *data, char *cmd_name)
{
	*cmd_path = find_cmd_path(data, cmd_name);
	if (!(*cmd_path))
		return (false);
	if (!check_path(*cmd_path, cmd_name, data))
	{
		free(*cmd_path);
		*cmd_path = NULL;
		return (false);
	}
	return (true);
}

// cierra fds
static void	close_inherited_pipes(int *pips_fds, t_cmd *cmd_node)
{
	if (pips_fds[0] >= 0 && pips_fds[0] != cmd_node->pipe_read)
		close(pips_fds[0]);
	if (pips_fds[1] >= 0 && pips_fds[1] != cmd_node->pipe_write)
		close(pips_fds[1]);
}

// redirige archivos, conecta pipes y cierra fds (hijo)
void	redirect_int_out(t_cmd *cmd_node, int *pip_fds_parent_inherited)
{
	close_inherited_pipes(pip_fds_parent_inherited, cmd_node);
	if (cmd_node->infile_fd >= 0)
	{
		dup2(cmd_node->infile_fd, STDIN_FILENO);
		close(cmd_node->infile_fd);
	}
	else if (cmd_node->pipe_in == 1 && cmd_node->pipe_read >= 0)
	{
		dup2(cmd_node->pipe_read, STDIN_FILENO);
		close(cmd_node->pipe_read);
	}
	if (cmd_node->outfile_fd >= 0)
	{
		dup2(cmd_node->outfile_fd, STDOUT_FILENO);
		close(cmd_node->outfile_fd);
	}
	else if (cmd_node->pipe_out == 1 && cmd_node->pipe_write >= 0)
	{
		dup2(cmd_node->pipe_write, STDOUT_FILENO);
		close(cmd_node->pipe_write);
	}
}

// maneja builtins cuando se ejecutan en el hijo(pipes)
void	built_child(t_data *data, t_cmd *cmd_node, int *pipe)
{
	(void)pipe;
	go_builtins(-1, -1, data, cmd_node);
	free_total(data, 0);
	exit(data->exit_code);
}
