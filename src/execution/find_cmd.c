#include "../includes/minishell.h"

char	*join_path_and_cmd(const char *path, const char *cmd)
{
	char	*joined_path;
	size_t	path_len;
	size_t	cmd_len;

	path_len = ft_strlen(path);
	cmd_len = ft_strlen(cmd);
	joined_path = malloc(path_len + cmd_len + 2);
	if (!joined_path)
		return (NULL);
	ft_memcpy(joined_path, path, path_len);
	joined_path[path_len] = '/';
	ft_memcpy(joined_path + path_len + 1, cmd, cmd_len);
	joined_path[path_len + 1 + cmd_len] = '\0';
	return (joined_path);
}

static char	*search_in_path(t_data *data, char *cmd_name)
{
	char	**dirs;
	char	*full_path;
	char	*path_val;
	int		i;

	path_val = get_path_value(data->env);
	if (!path_val)
		return (NULL);
	dirs = ft_split(path_val, ':');
	if (!dirs)
	{
		data->exit_code = 1;
		return (NULL);
	}
	i = 0;
	while (dirs[i])
	{
		full_path = join_path_and_cmd(dirs[i], cmd_name);
		if (full_path && access(full_path, X_OK) == 0)
			return (free_arr(dirs), full_path);
		free(full_path);
		i++;
	}
	free_arr(dirs);
	return (NULL);
}

void	cmd_error(const char *cmd_name, int err_code)
{
	ft_putstr_fd(STDERR_FILENO, "minishell: ");
	if (cmd_name && *cmd_name != '\0')
	{
		ft_putstr_fd(STDERR_FILENO, cmd_name);
		ft_putstr_fd(STDERR_FILENO, ": ");
	}
	if (err_code == 126)
		ft_putstr_fd(STDERR_FILENO, "Permission denied\n");
	else if (err_code == 127)
	{
		if (ft_strchr(cmd_name, '/') != NULL)
		{
			if (errno == ENOENT || errno == ENOTDIR || errno == EISDIR
				|| errno == EACCES)
			{
				ft_putstr_fd(STDERR_FILENO, strerror(errno));
				ft_putstr_fd(STDERR_FILENO, "\n");
			}
			else
				ft_putstr_fd(STDERR_FILENO, "command not found\n");
		}
		else
			ft_putstr_fd(STDERR_FILENO, "command not found\n");
	}
}

static char	*validate_absolute_path(char *cmd_name)
{
	struct stat	path_stat;
	char		*path_to_check;

	path_to_check = ft_strdup(cmd_name);
	if (stat(path_to_check, &path_stat) == 0)
	{
		if (!S_ISDIR(path_stat.st_mode) && access(path_to_check, X_OK) == 0)
			return (path_to_check);
	}
	free(path_to_check);
	return (NULL);
}

char	*validate_and_get_path(t_data *data, char *cmd_name)
{
	char	*path_to_check;
	int		status_code;

	if (ft_strchr(cmd_name, '/'))
	{
		path_to_check = validate_absolute_path(cmd_name);
		if (path_to_check)
			return (path_to_check);
		if (access(cmd_name, F_OK) != 0)
			status_code = 127;
		else if (access(cmd_name, X_OK) != 0)
			status_code = 126;
		else
			status_code = 126;
	}
	else
	{
		path_to_check = search_in_path(data, cmd_name);
		if (path_to_check)
			return (path_to_check);
		status_code = 127;
	}
	return (data->exit_code = status_code, cmd_error(cmd_name, status_code),
		NULL);
}