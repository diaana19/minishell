/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dirituay <dirituay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 13:52:51 by dirituay          #+#    #+#             */
/*   Updated: 2025/07/14 22:27:32 by dirituay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// verifica las variables validas en bash VAR=hola, no 1VAR
bool	valid_id(char *str)
{
	int	i;

	i = 0;
	if (!str[0] || (str[0] != '_' && !ft_isalpha(str[0])))
		return (false);
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (false);
		i++;
	}
	return (true);
}

// convierte v. de entorno a array e imprime el env ordenado (sin args)
bool	exp_no_args(t_env *env)
{
	int		i;
	int		j;
	char	**arr;

	arr = env_list_to_array(env);
	if (!arr)
		return (false);
	sort_array(arr, length_env_list(env));
	i = 0;
	while (arr[i])
	{
		printf("declare -x ");
		j = 0;
		while (arr[i][j] && arr[i][j] != '=')
			printf("%c", arr[i][j++]);
		if (arr[i][j] && arr[i][j] == '=')
			printf("=\"%s\"\n", &arr[i][j + 1]);
		else
			printf("\n");
		i++;
	}
	free_arr(arr);
	return (true);
}

// verifica si alguna variable ya existe y retorna la posicion(j)
int	key_exist(char *str, t_env *env)
{
	t_env	*temp;
	int		i;
	int		j;

	if (!env)
		return (-1);
	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	j = 0;
	temp = env;
	while (temp)
	{
		if (strlen1(temp->name) == i && ft_strncmp(temp->name, str, i) == 0)
			return (j);
		temp = temp->next;
		j++;
	}
	return (-1);
}

// parsea key=value y divide name y value, key=value
bool	extract_name_value(char *str, char **var_name, char **var_value)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	*var_name = ft_strndup(str, i);
	if (!*var_name)
		return (false);
	*var_value = NULL;
	if (str[i] == '=')
	{
		*var_value = ft_strdup(&str[i + 1]);
		if (!*var_value)
		{
			free(*var_name);
			return (false);
		}
	}
	return (true);
}

// duplica y actu. name y value de t_env *node con new_name y new_value
void	update_node(t_env *node, char *new_name, char *new_value)
{
	char	*temp_value;
	char	*temp_name;

	temp_name = NULL;
	temp_value = NULL;
	if (new_name)
	{
		temp_name = duplicated_str(node, new_name, true);
		if (!temp_name)
			return ;
	}
	if (new_value)
	{
		temp_value = duplicated_str(node, new_value, false);
		if (!temp_value)
			return ;
	}
	free(node->name);
	free(node->value);
	node->name = temp_name;
	node->value = temp_value;
}
