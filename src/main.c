#include "../includes/minishell.h"

static void	init_data(t_data *data, char **envp)
{
	data->cmds_list = NULL;
	data->env = NULL;
	data->pipe[0] = -1;
	data->pipe[1] = -1;
	data->exit_code = 0;
	ft_copy_env(envp, &data->env);
	setup_signals();
}

int	main(int ac, char **av, char **envp)
{
	t_data	data;

	(void)ac;
	(void)av;
	if (!isatty(0))
	{
		printf("minishell: tty required\n");
		return (1);
	}
	init_data(&data, envp);
	run_shell(&data);
	free_total(&data, data.exit_code);
	return (data.exit_code);
}