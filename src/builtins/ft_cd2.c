#include "../../includes/minishell.h"

int	ft_cd(t_data *data, char **params)
{
	int	ac;
	int	status;

	ac = count_args(params);
	status = 1;
	if (ac > 2)
	{
		ft_putstr_fd(STDERR_FILENO, "minishell: cd: too many arguments\n");
		return (1);
	}
	if (ac == 1 || (ac == 2 && ft_strcmp(params[1], "~") == 0))
		status = handle_cd_home(data);
	else if (ac == 2)
		status = chdir_and_error(params[1]);
	else
		return (1);
	if (status == 0)
		update_pwd(data);
	return (status);
}