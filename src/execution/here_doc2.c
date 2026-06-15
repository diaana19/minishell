#include "../includes/minishell.h"

char	*replace_dollar(const char *line, t_data *data)
{
	char	*new_line_result;
	char	*current_i;

	if (!line || !*line)
		return (handle_empty_line(line));
	current_i = (char *)line;
	new_line_result = ft_strdup("");
	if (!new_line_result)
		return (NULL);
	return (process_dollar_loop(new_line_result, current_i, data));
}

void	print_eof_warning(char *word_delimiter)
{
	ft_putstr_fd(STDERR_FILENO,
		"warning: here-document delimited by end-of-file (wanted  '");
	ft_putstr_fd(STDERR_FILENO, word_delimiter);
	ft_putstr_fd(STDERR_FILENO, "')\n");
}

char	*handle_expansion(char *buffer, t_data *data, bool expand_vars)
{
	char	*expanded;

	if (expand_vars)
	{
		expanded = replace_dollar(buffer, data);
		if (!expanded)
		{
			free(buffer);
			free_total(data, 1);
		}
		return (expanded);
	}
	return (buffer);
}

void	write_buffer_to_fd(int fd, char *buffer)
{
	write(fd, buffer, ft_strlen(buffer));
	write(fd, "\n", 1);
}

void	cleanup_buffers(char *readline_buf, char *expansion_buf)
{
	free(readline_buf);
	if (expansion_buf != readline_buf)
		free(expansion_buf);
}