#include "../../includes/minishell.h"

bool	add_new_node(t_env **env, char *name, char *value)
{
	t_env	*new;

	new = new_env(name, value);
	if (!new)
	{
		free(name);
		if (value)
			free(value);
		return (false);
	}
	ft_lstadd_back_env(env, new);
	return (true);
}

static bool	update_or_add(t_env **env, char *name, char *value)
{
	int		key;
	t_env	*current;

	key = key_exist(name, (*env));
	if (key >= 0)
	{
		current = *env;
		while (key--)
			current = current->next;
		update_node(current, name, value);
		return (true);
	}
	else
		return (add_new_node(env, name, value));
}

static bool	handle_export_validation(char *str, char **var_name,
		char **var_value, t_env *env)
{
	int	existing_key;

	if (!extract_name_value(str, var_name, var_value))
		return (false);
	if (!valid_id(*var_name))
	{
		ft_putstr_fd(STDERR_FILENO, "minishell: export: `");
		ft_putstr_fd(STDERR_FILENO, str);
		ft_putstr_fd(STDERR_FILENO, "': not a valid identifier\n");
		free(*var_name);
		if (*var_value)
			free(*var_value);
		return (false);
	}
	if (!*var_value)
	{
		existing_key = key_exist(*var_name, env);
		if (existing_key >= 0)
			return (true);
		*var_value = ft_strdup("");
	}
	return (true);
}

bool	env_export(char *str, t_env **env)
{
	char	*var_name;
	char	*var_value;
	bool	validation_result;

	validation_result = handle_export_validation(str, &var_name, &var_value,
			*env);
	if (!validation_result)
		return (false);
	if (!var_value)
	{
		free(var_name);
		return (true);
	}
	if (!update_or_add(env, var_name, var_value))
		return (false);
	free(var_name);
	if (var_value)
		free(var_value);
	return (true);
}

int	ft_export(char **str, t_env **env)
{
	int	exit_code;
	int	i;

	i = 1;
	exit_code = 0;
	if (!str[i])
	{
		if (!exp_no_args((*env)))
		{
			ft_putstr_fd(STDERR_FILENO, "minishell: Malloc error\n");
			return (1);
		}
		return (0);
	}
	while (str[i])
	{
		if (!env_export(str[i], env))
			exit_code = 1;
		i++;
	}
	return (exit_code);
}