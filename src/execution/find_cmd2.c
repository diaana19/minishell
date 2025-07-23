/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_cmd2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lellanos <lellanos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 15:50:52 by dianarituay       #+#    #+#             */
/*   Updated: 2025/07/23 15:39:56 by lellanos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// itera sobre cada direc de PATH y verifica si el cmd existe
static char	*search_in_path(t_data *data, char **path, char *cmd_name)
{
	char	full_path[PATH_MAX];
	char	*result_path;
	int		i;

	result_path = NULL;
	i = 0;
	while (path[i])
	{
		if (ft_path_join(full_path, path[i], cmd_name, PATH_MAX) != 0)
		{
			i++;
			continue ;
		}
		result_path = check_and_dup(data, full_path);
		if (result_path)
			break ;
		i++;
	}
	return (result_path);
}

// divide el PATH y busca el comando
static char	*div_path(t_data *data, char *no_var_path, char *cmd_name)
{
	char	**path;
	char	*found_path;

	if (!cmd_name || cmd_name[0] == 0)
		return (NULL);
	path = ft_split(no_var_path, ':');
	if (!path)
	{
		ft_putstr_fd(STDERR_FILENO, "minishell: malloc error\n");
		data->exit_code = 1;
		return (NULL);
	}
	found_path = search_in_path(data, path, cmd_name);
	free_arr(path);
	if (!found_path)
	{
		cmd_error(cmd_name, 127);
		data->exit_code = 127;
	}
	return (found_path);
}

// decide si es una ruta directa (/) o debe buscarse en PATH
char	*find_cmd_path(t_data *data, char *cmd_name)
{
	char	*no_bar_path;
	char	*found_path;

	if (ft_strchr(cmd_name, '/'))
		return (handle_path(data, cmd_name));
	no_bar_path = get_path_value(data->env);
	if (!no_bar_path || *no_bar_path == '\0')
	{
		cmd_error(cmd_name, 127);
		data->exit_code = 127;
		return (NULL);
	}
	found_path = div_path(data, no_bar_path, cmd_name);
	return (found_path);
}
