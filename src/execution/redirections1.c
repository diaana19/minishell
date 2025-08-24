/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dirituay <dirituay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 17:41:27 by dirituay          #+#    #+#             */
/*   Updated: 2025/08/24 19:36:31 by dirituay         ###   ########.fr       */
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

// redireccion de salida (hijo) de salida
static int	output_redirection(t_redir *current_redir, int *final_fd)
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
int	handle_output_redirec(t_cmd *cmd_node)
{
	int		final_output_fd;
	t_redir	*current_redir;

	final_output_fd = -1;
	if (cmd_node->redir == NULL)
		return (-1);
	current_redir = cmd_node->redir;
	while (current_redir)
	{
		if (output_redirection(current_redir, &final_output_fd) == -1)
			return (-1);
		current_redir = current_redir->next;
	}
	return (final_output_fd);
}

// abre un solo archivo de entrada (normal o heredoc) < <<
static int	input_redirection(t_redir *redir, t_data *data)
{
	int	fd;

	if (redir->type == REDIR_HEREDOC)
	{
		fd = here_doc(data, redir->filename, redir->heredoc_expand);
		if (fd == -2)
			return (-2);
	}
	else
		fd = open(redir->filename, O_RDONLY);
	if (fd == -1)
		perror("minishell: open input file error");
	return (fd);
}

//inicio de handle_input_redirec
int	process_input_redirect(t_redir *redir, t_data *data, int *final_fd)
{
	int	redirect_result;

	if (*final_fd != -1)
		close(*final_fd);
	redirect_result = input_redirection(redir, data);
	if (redirect_result == -2)
		return (-2);
	*final_fd = redirect_result;
	if (*final_fd == -1)
	{
		data->exit_code = 1;
		return (-1);
	}
	return (0);
}
