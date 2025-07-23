/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_built2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dirituay <dirituay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 18:11:14 by dianarituay       #+#    #+#             */
/*   Updated: 2025/07/23 22:27:31 by dirituay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// verifica si hay alguna redireccion de salida
static bool	has_output_redir(t_redir *redir)
{
	while (redir)
	{
		if (redir->type != REDIR_IN && redir->type != REDIR_HEREDOC)
			return (true);
		redir = redir->next;
	}
	return (false);
}

// abre todos los fds
bool	open_redirections_in_parent(t_cmd *cmd_node, t_data *data)
{
	int	temp_outfile_fd;

	cmd_node->infile_fd = -1;
	cmd_node->outfile_fd = -1;
	if (cmd_node->redir == NULL)
		return (true);
	temp_outfile_fd = -1;
	if (!process_input_redirs(cmd_node, data, &temp_outfile_fd))
	{
		if (temp_outfile_fd != -1)
			close(temp_outfile_fd);
	}
	temp_outfile_fd = open_output_files_in_parent(cmd_node);
	if (temp_outfile_fd == -1 && has_output_redir(cmd_node->redir))
	{
		data->exit_code = 1;
		if (cmd_node->infile_fd != -1)
			close(cmd_node->infile_fd);
		return (false);
	}
	cmd_node->outfile_fd = temp_outfile_fd;
	return (true);
}

// hace dup, dup2
int	input_builtin_parent(t_cmd *cmd_node)
{
	int	sav_fd_stdin;

	sav_fd_stdin = -1;
	if (cmd_node->infile_fd != -1)
	{
		sav_fd_stdin = dup(STDIN_FILENO);
		if (sav_fd_stdin == -1)
		{
			perror("minishell: dup stdin error");
			return (-2);
		}
		dup2(cmd_node->infile_fd, STDIN_FILENO);
		close(cmd_node->infile_fd);
		cmd_node->infile_fd = -1;
	}
	return (sav_fd_stdin);
}

// hace dup, dup2
int	output_builtin_parent(t_cmd *cmd_node)
{
	int	sav_fd_stdout;

	sav_fd_stdout = -1;
	if (cmd_node->outfile_fd != -1)
	{
		sav_fd_stdout = dup(STDOUT_FILENO);
		if (sav_fd_stdout == -1)
		{
			perror("minishell: dup stdout error");
			return (-2);
		}
		dup2(cmd_node->outfile_fd, STDOUT_FILENO);
		close(cmd_node->outfile_fd);
		cmd_node->outfile_fd = -1;
	}
	return (sav_fd_stdout);
}

// restaura los fds a sus valores originales si fueron utilizados
void	restore_std_fds(int sav_fd_stdin, int sav_fd_stdout)
{
	if (sav_fd_stdin != -1)
	{
		dup2(sav_fd_stdin, STDIN_FILENO);
		close(sav_fd_stdin);
	}
	if (sav_fd_stdout != -1)
	{
		dup2(sav_fd_stdout, STDOUT_FILENO);
		close(sav_fd_stdout);
	}
}
