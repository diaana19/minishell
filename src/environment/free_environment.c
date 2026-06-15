#include "../includes/minishell.h"

void	free_env(t_env **env_list)
{
	t_env		*tmp;

	if (!env_list || !*env_list)
		return ;
	while (*env_list)
	{
		tmp = (*env_list)->next;
		free_env_node(*env_list);
		*env_list = tmp;
	}
	*env_list = NULL;
}