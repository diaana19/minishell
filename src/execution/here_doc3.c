#include "../includes/minishell.h"

static int	process_readline_input(char *buffer_readline, char *word_delimiter)
{
	if (g_signal_pid == 1)
	{
		if (buffer_readline)
			free(buffer_readline);
		return (-1);
	}
	if (!buffer_readline)
		return (print_eof_warning(word_delimiter), 1);
	if (ft_strcmp(word_delimiter, buffer_readline) == 0)
		return (free(buffer_readline), 1);
	return (0);
}

static void	write_expanded_buffer(char *buffer_readline, t_data *data, int fd,
		bool expand_vars)
{
	char	*buffer_expansion;

	buffer_expansion = handle_expansion(buffer_readline, data, expand_vars);
	write_buffer_to_fd(fd, buffer_expansion);
	cleanup_buffers(buffer_readline, buffer_expansion);
}

static int	read_in_stdin(t_data *data, int fd, char *word_delimiter,
		bool expand_vars)
{
	char	*buffer_readline;
	int		result;

	g_signal_pid = 0;
	while (1)
	{
		buffer_readline = readline("> ");
		result = process_readline_input(buffer_readline, word_delimiter);
		if (result == -1)
			return (-1);
		if (result == 1)
			break ;
		write_expanded_buffer(buffer_readline, data, fd, expand_vars);
	}
	return (0);
}

static int	create_and_write_heredoc(t_data *data, char *word, bool expand_vars)
{
	int	fd;
	int	read_status;

	fd = open(HEREDOC_TMP_FILE, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror("minishell: heredoc: failed to create temporary file");
		return (-1);
	}
	read_status = read_in_stdin(data, fd, word, expand_vars);
	if (read_status == -1)
	{
		close(fd);
		unlink(HEREDOC_TMP_FILE);
		return (-2);
	}
	close(fd);
	return (0);
}

int	here_doc(t_data *data, char *word, bool expand_vars)
{
	int	fd;

	setup_heredoc_signals();
	if (create_and_write_heredoc(data, word, expand_vars) != 0)
	{
		restore_default_signals();
		return (-2);
	}
	fd = open(HEREDOC_TMP_FILE, O_RDONLY);
	if (fd < 0)
	{
		perror("minishell: heredoc: failed to create temporary file");
		unlink(HEREDOC_TMP_FILE);
		restore_default_signals();
		return (-1);
	}
	unlink(HEREDOC_TMP_FILE);
	restore_default_signals();
	return (fd);
}