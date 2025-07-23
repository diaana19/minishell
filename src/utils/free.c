/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dirituay <dirituay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 23:25:28 by dianarituay       #+#    #+#             */
/*   Updated: 2025/07/23 22:32:24 by dirituay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// free para liberar el array de strings
void	free_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

// libera la memoria de un nodo t_env, name y value
void	free_env_node(t_env *node)
{
	if (!node)
		return ;
	if (node->name)
		free(node->name);
	if (node->value)
		free(node->value);
	free(node);
}

// limpia todo antes de salir del programa
void	free_total(t_data *data, int code)
{
	if (!data)
		exit(code);
	if (data->cmds_list)
		free_cmd_list(&data->cmds_list);
	if (data->env)
		free_env(&data->env);
	rl_clear_history();
	exit(code);
}
