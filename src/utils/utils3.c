/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lellanos <lellanos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 14:32:10 by dianarituay       #+#    #+#             */
/*   Updated: 2025/07/23 21:48:14 by lellanos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//free para un array de strings hasta un length especif.
static void	free_len_arr(char **arr, int length)
{
	while (length > 0)
		free(arr[length--]);
	free(arr);
}

// crea la str NAME=VALUE o NAME y retorna el str creado
static char	*create_env_str(t_env *node)
{
	char	*temp_str;

	if (node->value)
	{
		temp_str = (char *)malloc(ft_strlen(node->name)
				+ ft_strlen(node->value) + 2);
		if (!temp_str)
			return (NULL);
		ft_strcpy(temp_str, node->name);
		ft_strcat(temp_str, "=");
		ft_strcat(temp_str, node->value);
	}
	else
	{
		temp_str = ft_strdup(node->name);
		if (!temp_str)
			return (NULL);
	}
	return (temp_str);
}

// toma una t_env *env y la convierte a char **
char	**env_list_to_array(t_env *env_list)
{
	char	**arr;
	int		i;
	int		count;

	count = length_env_list(env_list);
	arr = (char **)malloc(sizeof(char *) * (count + 1));
	if (!arr)
		return (NULL);
	i = 0;
	while (env_list)
	{
		arr[i] = create_env_str(env_list);
		if (!arr[i])
		{
			free_len_arr(arr, i);
			return (NULL);
		}
		env_list = env_list->next;
		i++;
	}
	arr[i] = NULL;
	return (arr);
}

void	close_all_pipes_in_parent(t_data *data)
{
	if (data->pipe[0] >= 0)
	{
		close(data->pipe[0]);
		data->pipe[0] = -1;
	}
	if (data->pipe[1] >= 0)
	{
		close(data->pipe[1]);
		data->pipe[1] = -1;
	}
}
