#include "../../includes/minishell.h"

int	ft_pwd(char **av)
{
	char	buf[PATH_MAX];
	int		ac;

	ac = 0;
	while (av && av[ac])
		ac++;
	if (ac > 1)
	{
		ft_putstr_fd(2, "minishell: pwd: no options allowed\n");
		return (2);
	}
	if (getcwd(buf, PATH_MAX))
	{
		printf("%s\n", buf);
		return (0);
	}
	return (1);
}