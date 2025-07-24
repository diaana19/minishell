/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dirituay <dirituay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 21:10:18 by dirituay          #+#    #+#             */
/*   Updated: 2025/07/24 09:52:44 by dirituay         ###   ########.fr       */
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
		if (g_signal_pid == -3)
		{
			close (fd);
			free(buffer_readline);
			break ;
		}
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
	int		fd;
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid < 0)
	{
		perror("minishell: fork");
		return (-1);
	}
	else if (pid == 0)
	{
		setup_heredoc_signals();
		fd = open(HEREDOC_TMP_FILE, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (fd < 0)
		{
			perror("minishell: heredoc: failed to create temporary file");
			exit (1);
		}
		if (!read_in_stdin(data, fd, word, expand_vars))
		{
			close (fd);
			unlink(HEREDOC_TMP_FILE);
			exit (1);
		}
		close (fd);
		exit (0);
	}
	else
	{
		setup_signals(); // padre configura signals normales
		waitpid(pid, &status, 0);
		if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
		{
			unlink(HEREDOC_TMP_FILE);
			return (-1);
		}
		else if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
		{
			unlink(HEREDOC_TMP_FILE);
			return (-1);
		}
		fd = open(HEREDOC_TMP_FILE, O_RDONLY);
		if (fd < 0)
		{
			perror("minishell: heredoc: failed to open temporary file");
			unlink(HEREDOC_TMP_FILE);
			return (-1);
		}
		unlink(HEREDOC_TMP_FILE);
		return (fd);
	}
}
