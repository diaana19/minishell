#include "../../includes/minishell.h"

static void	swap_array(int i, int j, char **tab)
{
	char	*temp;

	temp = tab[i];
	tab[i] = tab[j];
	tab[j] = temp;
}

void	sort_array(char **arr, int length)
{
	int	i;
	int	j;
	int	result;

	i = 0;
	while (i < length)
	{
		j = i + 1;
		while (j < length)
		{
			result = ft_strncmp(arr[i], arr[j], INT_MAX);
			if (result > 0)
			{
				swap_array(i, j, arr);
				continue ;
			}
			j++;
		}
		i++;
	}
}

char	*get_env_value(const char *name, t_env *env)
{
	t_env	*current;

	if (!name || !env)
		return (NULL);
	current = env;
	while (current)
	{
		if (ft_strcmp(current->name, name) == 0)
		{
			if (!current->value)
				return (NULL);
			return (ft_strdup(current->value));
		}
		current = current->next;
	}
	return (NULL);
}

size_t	length_env_list(t_env *env_list)
{
	t_env	*temp;
	size_t	i;

	i = 0;
	temp = env_list;
	while (temp)
	{
		i++;
		temp = temp->next;
	}
	return (i);
}

char	*get_path_value(t_env *env)
{
	while (env)
	{
		if (ft_strcmp(env->name, "PATH") == 0)
		{
			if (env->value && *env->value != '\0')
				return (env->value);
			return (NULL);
		}
		env = env->next;
	}
	return (NULL);
}