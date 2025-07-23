/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd5.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dirituay <dirituay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 21:02:46 by dirituay          #+#    #+#             */
/*   Updated: 2025/07/23 19:44:11 by dirituay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// maneja errores en el hijo
void	handle_error_child(t_cmd *cmd_node)
{
	if (cmd_node->has_error)
		exit(1);
	if (!cmd_node->argv || !cmd_node->argv[0])
		exit(1);
}

// ejecuta comandos externos
void	cmd_exce_child(t_data *data, t_cmd *cmd_node, int *pip)
{
	char	*cmd_path;
	char	**env_arr;

	(void)pip;
	cmd_path = NULL;
	if (!validate_cmd_path(&cmd_path, data, cmd_node->argv[0]))
	{
		free_total(data, data->exit_code);
		exit(data->exit_code);
	}
	env_arr = env_list_to_array(data->env);
	if (!env_arr)
	{
		ft_putstr_fd(STDERR_FILENO, "minishell: malloc error\n");
		free(cmd_path);
		exit(1);
	}
	execve(cmd_path, cmd_node->argv, env_arr);
	perror("minishell: execve failed");
	free(cmd_path);
	free_arr(env_arr);
	exit(127);
}

// dsp de q fork duplica el minishell, ejecuta el comando en el hijo
void	child_process(t_data *data, t_cmd *cmd_node, int *pipe)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	signal(SIGTSTP, SIG_IGN);
	handle_error_child(cmd_node);
	redirect_int_out(cmd_node, pipe);
	if (is_builtin(cmd_node->argv[0]))
		built_child(data, cmd_node, pipe);
	else
		cmd_exce_child(data, cmd_node, pipe);
	exit(data->exit_code);
}
