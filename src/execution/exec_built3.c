/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_built3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dirituay <dirituay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 20:48:47 by dirituay          #+#    #+#             */
/*   Updated: 2025/07/23 19:45:09 by dirituay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// ejecuta los builtins, identifica y llama al q corresponde
void	go_builtins(int save_stdin, int save_stdout, t_data *data, t_cmd *cmd)
{
	if (!ft_strncmp("echo", cmd->argv[0], INT_MAX))
		data->exit_code = ft_echo(cmd->argv);
	else if (!ft_strncmp("cd", cmd->argv[0], INT_MAX))
		data->exit_code = ft_cd(data, cmd->argv);
	else if (!ft_strncmp("env", cmd->argv[0], INT_MAX))
		data->exit_code = ft_env(data->env, cmd->argv);
	else if (!ft_strncmp("pwd", cmd->argv[0], INT_MAX))
		data->exit_code = ft_pwd(cmd->argv);
	else if (!ft_strncmp("export", cmd->argv[0], INT_MAX))
		data->exit_code = ft_export(cmd->argv, &data->env);
	else if (!ft_strncmp("unset", cmd->argv[0], INT_MAX))
		data->exit_code = ft_unset(cmd->argv, &data->env);
	else if (!ft_strncmp("exit", cmd->argv[0], INT_MAX))
	{
		restore_std_fds(save_stdin, save_stdout);
		ft_exit(data, cmd->argv);
	}
	else
	{
		printf("minishell: %s: command not found\n", cmd->argv[0]);
		data->exit_code = 127;
	}
}

// errores de redirecciones
static bool	handle_redirec_error(int fd_status, int sav_fd_stdin, t_data *data)
{
	if (fd_status == -2)
	{
		if (sav_fd_stdin != -1)
			restore_std_fds(sav_fd_stdin, -1);
		data->exit_code = 1;
		return (true);
	}
	return (false);
}

// ejecuta los builtins en el padre y restaura
bool	exec_builtin(t_data *data, t_cmd *cmd_node)
{
	int	sav_fd_stdin;
	int	sav_fd_stdout;

	sav_fd_stdin = -1;
	sav_fd_stdout = -1;
	sav_fd_stdin = input_builtin_parent(cmd_node);
	if (sav_fd_stdin == -2)
	{
		handle_redirec_error(sav_fd_stdin, sav_fd_stdin, data);
		return (false);
	}
	sav_fd_stdout = output_builtin_parent(cmd_node);
	if (sav_fd_stdout == -2)
	{
		handle_redirec_error(sav_fd_stdout, sav_fd_stdin, data);
		return (false);
	}
	go_builtins(sav_fd_stdin, sav_fd_stdout, data, cmd_node);
	restore_std_fds(sav_fd_stdin, sav_fd_stdout);
	return (true);
}
