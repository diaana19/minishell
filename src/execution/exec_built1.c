/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_built1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dirituay <dirituay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 17:41:27 by dirituay          #+#    #+#             */
/*   Updated: 2025/07/24 09:23:17 by dirituay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// banderas de open
static int	get_output_flags(t_redir_type type)
{
	int	flags;

	flags = O_WRONLY | O_CREAT;
	if (type == REDIR_APPEND)
		flags |= O_APPEND;
	else
		flags |= O_TRUNC;
	return (flags);
}

// redireccion de salida
static int	process_output_redir(t_redir *current_redir, int *final_fd)
{
	int	flags;
	int	new_fd;

	if (current_redir->type != REDIR_OUT && current_redir->type != REDIR_APPEND)
		return (0);
	if (*final_fd != -1)
		close(*final_fd);
	flags = get_output_flags(current_redir->type);
	new_fd = open(current_redir->filename, flags, 0644);
	if (new_fd == -1)
	{
		perror("minishell: open output file error");
		return (-1);
	}
	*final_fd = new_fd;
	return (0);
}

// abre archivos de salida para un comando > >>
int	open_output_files_in_parent(t_cmd *cmd_node)
{
	int		final_output_fd;
	t_redir	*current_redir;

	final_output_fd = -1;
	if (cmd_node->redir == NULL)
		return (-1);
	current_redir = cmd_node->redir;
	while (current_redir)
	{
		if (process_output_redir(current_redir, &final_output_fd) == -1)
			return (-1);
		current_redir = current_redir->next;
	}
	return (final_output_fd);
}

// abre un solo archivo de entrada (normal o heredoc) < <<
static int	open_input_file(t_redir *redir, t_data *data)
{
	int	fd;

	if (redir->type == REDIR_HEREDOC)
	{
		printf("DEBUG: heredoc delimitador: '%s'\n", redir->filename);
		fd = here_doc(data, redir->filename, redir->heredoc_expand);
	}
	else
		fd = open(redir->filename, O_RDONLY);
	if (fd == -1)
		//perror("minishell: open input file error");
		return (-1);
	return (fd);
}

// procesa TODAS las redirecciones de entrada de t_redir
bool	process_input_redirs(t_cmd *cmd_node, t_data *data, int *temp_out_fd)
{
	t_redir	*current_redir;
	int		temp_infile_fd;

	temp_infile_fd = -1;
	current_redir = cmd_node->redir;
	while (current_redir)
	{
		if (current_redir->type == REDIR_IN
			|| current_redir->type == REDIR_HEREDOC)
		{
			if (temp_infile_fd != -1)
				close(temp_infile_fd);
			temp_infile_fd = open_input_file(current_redir, data);
			if (temp_infile_fd == -1)
			{
				data->exit_code = 1;
				if (*temp_out_fd != -1)
					close(*temp_out_fd);
				return (false);
			}
		}
		current_redir = current_redir->next;
	}
	cmd_node->infile_fd = temp_infile_fd;
	return (true);
}
