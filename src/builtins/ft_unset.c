#include "../../includes/minishell.h"

static bool	rmv_head(const char *rmv_name, t_env **head)
{
	t_env	*current;

	if (!head || !*head || !rmv_name)
		return (false);
	if (ft_strcmp((*head)->name, rmv_name) == 0)
	{
		current = *head;
		*head = current->next;
		free_env_node(current);
		return (true);
	}
	return (false);
}

static bool	rmv_no_head(const char *rmv_name, t_env *head)
{
	t_env	*current;
	t_env	*prev;

	if (!head || !head->next || !rmv_name)
		return (false);
	prev = head;
	current = head->next;
	while (current && ft_strcmp(current->name, rmv_name) != 0)
	{
		prev = current;
		current = current->next;
	}
	if (current)
	{
		prev->next = current->next;
		free_env_node(current);
		return (true);
	}
	return (false);
}

static void	rmv_env_node(const char *rmv_name, t_env **head)
{
	if (!head || !*head || !rmv_name)
		return ;
	if (rmv_head(rmv_name, head))
		return ;
	rmv_no_head(rmv_name, *head);
}

static bool	env_unset(char *str, t_env **env)
{
	if (!str || !(*str))
		return (false);
	if (!valid_id(str))
	{
		ft_putstr_fd(STDERR_FILENO, "minishell: `");
		ft_putstr_fd(STDERR_FILENO, str);
		ft_putstr_fd(STDERR_FILENO, "': not a valid identifier\n");
		return (true);
	}
	rmv_env_node(str, env);
	return (false);
}

int	ft_unset(char **str, t_env **env)
{
	int	i;
	int	exit_code;

	exit_code = 0;
	i = 1;
	while (str[i])
	{
		if (env_unset(str[i], env))
			exit_code = 1;
		i++;
	}
	return (exit_code);
}