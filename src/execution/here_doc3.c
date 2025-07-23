/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dirituay <dirituay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 21:10:18 by dirituay          #+#    #+#             */
/*   Updated: 2025/07/23 19:24:28 by dirituay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// lee la lineas de la terminal y las guarda en buffer
static bool	read_in_stdin(t_data *data, int fd, char *word_delimiter,
		bool expand_vars)
{
	char	*buffer_readline;
	char	*buffer_expansion;

	while (1)
	{
		buffer_readline = readline("> ");
		if (!buffer_readline)
		{
			print_eof_warning(word_delimiter);
			break ;
		}
		if (ft_strcmp(word_delimiter, buffer_readline) == 0)
		{
			free(buffer_readline);
			break ;
		}
		buffer_expansion = handle_expansion(buffer_readline, data, expand_vars);
		write_buffer_to_fd(fd, buffer_expansion);
		cleanup_buffers(buffer_readline, buffer_expansion);
	}
	close(fd);
	return (true);
}

// crea el archivo temporal y lee
int	here_doc(t_data *data, char *word, bool expand_vars)
{
	int	fd;

	fd = open(HEREDOC_TMP_FILE, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror("minishell: heredoc: failed to create temporary file");
		return (-1);
	}
	if (!read_in_stdin(data, fd, word, expand_vars))
	{
		if (fd >= 0)
			close(fd);
		unlink(HEREDOC_TMP_FILE);
		return (-1);
	}
	fd = open(HEREDOC_TMP_FILE, O_RDONLY);
	if (fd < 0)
	{
		perror("minishell: heredoc: failed to create temporary file");
		unlink(HEREDOC_TMP_FILE);
		return (-1);
	}
	unlink(HEREDOC_TMP_FILE);
	return (fd);
}
