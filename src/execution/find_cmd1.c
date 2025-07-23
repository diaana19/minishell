/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_cmd1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lellanos <lellanos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 15:09:45 by dianarituay       #+#    #+#             */
/*   Updated: 2025/07/23 15:48:08 by lellanos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// une PATH + /bin/ls, con el comando
int	ft_path_join(char *dest, const char *path, const char *cmd,
		size_t dest_size)
{
	size_t	path_len;
	size_t	cmd_len;

	path_len = ft_strlen(path);
	cmd_len = ft_strlen(cmd);
	if (path_len + 1 + cmd_len + 1 > dest_size)
		return (1);
	ft_strcpy(dest, path);
	dest[path_len] = '/';
	ft_strcpy(dest + path_len + 1, cmd);
	dest[path_len + 1 + cmd_len] = '\0';
	return (0);
}

// encuentra PATH en la lista de entorno y devuelve su valor

char	*get_path_value(t_env *env)
{
	t_env	*current;

	current = env;
	while (current)
	{
		if (ft_strcmp(current->name, "PATH") == 0)
		{
			if (ft_strcmp(current->value, "") == 0)
				return (NULL);
			else
				return (current->value);
		}
		current = current->next;
	}
	return (NULL);
}

// imprime errores
void	cmd_error(const char *cmd_name, int err_code)
{
	ft_putstr_fd(STDERR_FILENO, "minishell: ");
	if (!cmd_name || *cmd_name != '\0')
	{
		ft_putstr_fd(STDERR_FILENO, cmd_name);
		ft_putstr_fd(STDERR_FILENO, ": ");
	}
	if (err_code == 126)
		ft_putstr_fd(STDERR_FILENO, ": Permission denied \n");
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

// verifica si path es ejecutable y lo duplica
char	*check_and_dup(t_data *data, char *cmd_name)
{
	char	*result_path;

	if (access(cmd_name, X_OK) == 0)
	{
		result_path = ft_strdup(cmd_name);
		if (!result_path)
		{
			ft_putstr_fd(STDERR_FILENO, "minishell: malloc error\n");
			data->exit_code = 1;
		}
		return (result_path);
	}
	return (NULL);
}

// maneja cmd /bin/ls o ./cmd, retorna la ruta duplicada si es ejec.
char	*handle_path(t_data *data, char *cmd_name)
{
	char	*result_path;

	if (access(cmd_name, F_OK) != 0)
	{
		cmd_error(cmd_name, 127);
		data->exit_code = 127;
		return (NULL);
	}
	result_path = check_and_dup(data, cmd_name);
	if (result_path)
	{
		if (!check_path(result_path, cmd_name, data))
		{
			free(result_path);
			return (NULL);
		}
		return (result_path);
	}
	if (data->exit_code == 1)
		return (NULL);
	cmd_error(cmd_name, 126);
	data->exit_code = 126;
	return (NULL);
}
