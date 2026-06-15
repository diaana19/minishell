#include "../includes/minishell.h"

void	ft_copy_content(char *env_line, t_env **env_list)
{
	char	*sign;
	char	*name_str_temp;
	char	*value_str_temp;
	t_env	*new_node;

	sign = ft_strchr(env_line, '=');
	if (!sign)
		return ;
	name_str_temp = ft_strndup(env_line, sign - env_line);
	if (!name_str_temp)
		return ;
	value_str_temp = ft_strdup(sign + 1);
	if (!value_str_temp)
	{
		free(name_str_temp);
		return ;
	}
	new_node = new_env(name_str_temp, value_str_temp);
	free(name_str_temp);
	free(value_str_temp);
	if (!new_node)
		return ;
	ft_lstadd_back_env(env_list, new_node);
}

void	ft_copy_env(char **envp, t_env **env_list)
{
	int		i;

	i = 0;
	if (!env_list)
		return ;
	while (envp && envp[i])
	{
		ft_copy_content(envp[i], env_list);
		i++;
	}
}