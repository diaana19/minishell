#include "../../includes/minishell.h"

int	ft_env(t_env *env, char **args)
{
	t_env	*temp;
	int		ac;

	ac = count_args(args);
	if (ac > 1)
	{
		ft_putstr_fd(STDERR_FILENO, "minishell: env: '");
		ft_putstr_fd(STDERR_FILENO, args[1]);
		ft_putstr_fd(STDERR_FILENO, "': No such file or directory\n");
		return (127);
	}
	temp = env;
	while (temp != NULL)
	{
		if (temp->name && temp->value)
			printf("%s=%s\n", temp->name, temp->value);
		temp = temp->next;
	}
	return (0);
}