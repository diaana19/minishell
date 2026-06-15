#include "../includes/minishell.h"

static void	handle_exit(t_data *data, t_lex_token **lex_token_list)
{
	free_cmd_list(&data->cmds_list);
	free_lex_token(lex_token_list);
	ft_putstr_fd(STDOUT_FILENO, "exit\n");
	free_total(data, data->exit_code);
	exit(data->exit_code);
}

static int	process_line(t_data *data, char *input_line,
		t_lex_token **lex_token_list)
{
	*lex_token_list = NULL;
	lexer(input_line, lex_token_list, *data);
	if (!*lex_token_list)
		return (free(input_line), 0);
	data->cmds_list = NULL;
	parser(*lex_token_list, &data->cmds_list);
	free_lex_token(lex_token_list);
	if (!data->cmds_list || data->cmds_list->has_error)
	{
		data->exit_code = 2;
		free_cmd_list(&data->cmds_list);
		free(input_line);
		return (0);
	}
	return (1);
}

static void	reset_loop_state(t_data *data, t_lex_token **lex_token_list)
{
	free_cmd_list(&data->cmds_list);
	free_lex_token(lex_token_list);
}

static bool	handle_signal_interrupt(t_data *data, char **input_line)
{
	if (g_signal_pid == -1)
	{
		data->exit_code = 130;
		g_signal_pid = 0;
		return (true);
	}
	if (g_signal_pid == -2)
	{
		g_signal_pid = 0;
		if (*input_line)
		{
			free(*input_line);
			*input_line = NULL;
		}
		return (true);
	}
	return (false);
}

void	run_shell(t_data *data)
{
	char		*input_line;
	t_lex_token	*lex_token_list;

	input_line = NULL;
	lex_token_list = NULL;
	while (1)
	{
		if (g_signal_pid < 0)
			g_signal_pid = 0;
		reset_loop_state(data, &lex_token_list);
		input_line = readline("minishell$ ");
		if (!input_line)
			handle_exit(data, &lex_token_list);
		if (*input_line == '\0' || handle_signal_interrupt(data, &input_line))
		{
			free(input_line);
			continue ;
		}
		add_history(input_line);
		if (!process_line(data, input_line, &lex_token_list))
			continue ;
		execution(data);
	}
}