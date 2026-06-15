#include "../../includes/minishell.h"

int	count_args(char **args)
{
	int	count;

	count = 0;
	while (args[count])
		count++;
	return (count);
}

static void	update_oldpwd(t_data *data)
{
	char	*old_value;
	char	*new_oldpwd;

	old_value = get_env_value("PWD", data->env);
	if (!old_value)
	{
		env_export("OLDPWD", &data->env);
		return ;
	}
	new_oldpwd = ft_strjoin("OLDPWD=	", old_value);
	if (!new_oldpwd)
	{
		ft_putstr_fd(STDERR_FILENO, "Malloc error\n");
		free(old_value);
		return ;
	}
	env_export(new_oldpwd, &data->env);
	free(new_oldpwd);
	free(old_value);
}

void	update_pwd(t_data *data)
{
	char	buf[PATH_MAX];
	char	*pwd;

	update_oldpwd(data);
	if (!getcwd(buf, PATH_MAX))
	{
		perror("minishell: cd: ");
		return ;
	}
	pwd = ft_strjoin("PWD=", buf);
	if (!pwd)
	{
		ft_putstr_fd(STDERR_FILENO, "Malloc error\n");
		return ;
	}
	env_export(pwd, &data->env);
	free(pwd);
}

int	chdir_and_error(char *path)
{
	if (chdir(path) == -1)
	{
		perror("minishell: cd");
		return (1);
	}
	return (0);
}

int	handle_cd_home(t_data *data)
{
	char		*home_path;
	int			status;

	home_path = get_env_value("HOME", data->env);
	if (!home_path)
	{
		ft_putstr_fd(STDERR_FILENO, "minishell: cd: HOME not set\n");
		return (1);
	}
	status = chdir_and_error(home_path);
	free(home_path);
	return (status);
}