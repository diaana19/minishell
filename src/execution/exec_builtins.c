/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dirituay <dirituay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 20:48:47 by dirituay          #+#    #+#             */
/*   Updated: 2025/08/25 22:21:08 by dirituay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// crea una copia de stdin
int	input_builtin_parent(t_cmd *cmd_node)
{
	int	sav_fd_stdin;

	sav_fd_stdin = -1;
	if (cmd_node->infile_fd != -1)
	{
		sav_fd_stdin = dup(STDIN_FILENO);
		if (sav_fd_stdin == -1)
		{
			perror("minishell: dup stdin error");
			return (-2);
		}
		dup2(cmd_node->infile_fd, STDIN_FILENO);
		close(cmd_node->infile_fd);
		cmd_node->infile_fd = -1;
	}
	return (sav_fd_stdin);
}

// crea una copia de stdout
int	output_builtin_parent(t_cmd *cmd_node)
{
	int	sav_fd_stdout;

	sav_fd_stdout = -1;
	if (cmd_node->outfile_fd != -1)
	{
		sav_fd_stdout = dup(STDOUT_FILENO);
		if (sav_fd_stdout == -1)
		{
			perror("minishell: dup stdout error");
			return (-2);
		}
		dup2(cmd_node->outfile_fd, STDOUT_FILENO);
		close(cmd_node->outfile_fd);
		cmd_node->outfile_fd = -1;
	}
	return (sav_fd_stdout);
}

// restaura los fds dsp de un builtin con redirecciones
void	restore_fds_parent(int sav_fd_stdin, int sav_fd_stdout)
{
	if (sav_fd_stdin != -1)
	{
		dup2(sav_fd_stdin, STDIN_FILENO);
		close(sav_fd_stdin);
	}
	if (sav_fd_stdout != -1)
	{
		dup2(sav_fd_stdout, STDOUT_FILENO);
		close(sav_fd_stdout);
	}
}

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
		restore_fds_parent(save_stdin, save_stdout);
		ft_exit(data, cmd->argv);
	}
	else
	{
		printf("minishell: %s: command not found\n", cmd->argv[0]);
		data->exit_code = 127;
	}
}

// ejecuta los builtins en el padre y restaura
bool	execution_builtins(t_data *data, t_cmd *cmd_node)
{
	int	sav_fd_stdin;
	int	sav_fd_stdout;

	if (!is_builtin(cmd_node->argv[0]))
		return (false);
	if (has_input_redir(cmd_node->redir))
		cmd_node->infile_fd = handle_input_redirec(cmd_node, data);
	if (has_output_redir(cmd_node->redir))
		cmd_node->outfile_fd = handle_output_redirec(cmd_node);
	sav_fd_stdin = input_builtin_parent(cmd_node);
	sav_fd_stdout = output_builtin_parent(cmd_node);
	if (sav_fd_stdin == -2 || sav_fd_stdout == -2)
		data->exit_code = 1;
	else
		go_builtins(sav_fd_stdin, sav_fd_stdout, data, cmd_node);
	restore_fds_parent(sav_fd_stdin, sav_fd_stdout);
	return (true);
}
