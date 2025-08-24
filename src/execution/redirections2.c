/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dirituay <dirituay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 18:11:14 by dianarituay       #+#    #+#             */
/*   Updated: 2025/08/24 19:37:20 by dirituay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// procesa TODAS las redirecciones de entrada de t_redir
int	handle_input_redirec(t_cmd *cmd_node, t_data *data)
{
	t_redir	*current_redir;
	int		final_infile_fd;
	int		result;

	final_infile_fd = -1;
	current_redir = cmd_node->redir;
	while (current_redir)
	{
		if (current_redir->type == REDIR_IN
			|| current_redir->type == REDIR_HEREDOC)
		{
			result = process_input_redirect(current_redir, data,
					&final_infile_fd);
			if (result != 0)
				return (result);
		}
		current_redir = current_redir->next;
	}
	return (final_infile_fd);
}

// verifica si hay alguna redireccion de salida
bool	has_output_redir(t_redir *redir)
{
	while (redir)
	{
		if (redir->type == REDIR_OUT || redir->type == REDIR_APPEND)
			return (true);
		redir = redir->next;
	}
	return (false);
}

// verifica si hay alguna redireccion de entrada
bool	has_input_redir(t_redir *redir)
{
	while (redir)
	{
		if (redir->type == REDIR_IN || redir->type == REDIR_HEREDOC)
			return (true);
		redir = redir->next;
	}
	return (false);
}

static void	setup_stdin_stdout(t_cmd *cmd_node, int final_input_fd,
		int final_output_fd)
{
	if (final_input_fd != -1)
	{
		dup2(final_input_fd, STDIN_FILENO);
		close(final_input_fd);
	}
	else if (cmd_node->pipe_in == 1 && cmd_node->pipe_read >= 0)
	{
		dup2(cmd_node->pipe_read, STDIN_FILENO);
		close(cmd_node->pipe_read);
	}
	if (final_output_fd != -1)
	{
		dup2(final_output_fd, STDOUT_FILENO);
		close(final_output_fd);
	}
	else if (cmd_node->pipe_out == 1 && cmd_node->pipe_write >= 0)
	{
		dup2(cmd_node->pipe_write, STDOUT_FILENO);
		close(cmd_node->pipe_write);
	}
}

// procesa las redirecciones de salida y de entrada
int	handle_all_redirections(t_cmd *cmd_node, t_data *data, int *pipe_fds)
{
	int	final_input_fd;
	int	final_output_fd;

	close_inherited_pipes(pipe_fds, cmd_node);
	final_input_fd = handle_input_redirec(cmd_node, data);
	if (final_input_fd == -2)
	{
		data->exit_code = 130;
		return (-1);
	}
	else if (final_input_fd == -1 && has_input_redir(cmd_node->redir))
		return (-1);
	final_output_fd = handle_output_redirec(cmd_node);
	if (final_output_fd == -1 && has_output_redir(cmd_node->redir))
		return (-1);
	setup_stdin_stdout(cmd_node, final_input_fd, final_output_fd);
	return (0);
}
