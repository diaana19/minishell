#include "../../includes/minishell.h"

void	free_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	free_env_node(t_env *node)
{
	if (!node)
		return ;
	if (node->name)
		free(node->name);
	if (node->value)
		free(node->value);
	free(node);
}

void	free_total(t_data *data, int code)
{
	if (!data)
		exit(code);
	if (data->cmds_list)
		free_cmd_list(&data->cmds_list);
	if (data->env)
		free_env(&data->env);
	rl_clear_history();
	exit(code);
}