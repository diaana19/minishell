/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dirituay <dirituay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 19:44:12 by dirituay          #+#    #+#             */
/*   Updated: 2025/07/12 16:22:19 by dirituay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//intercambia 2 elementos en un char **tab
static void	swap_array(int i, int j, char **tab)
{
	char	*temp;

	temp = tab[i];
	tab[i] = tab[j];
	tab[j] = temp;
}

//ordena alfab. un **arr, muestra las env en orden(export)
void	sort_array(char **arr, int length)
{
	int	i;
	int	j;
	int	result;

	i = 0;
	while (i < length)
	{
		j = i + 1;
		while (j < length)
		{
			result = ft_strncmp(arr[i], arr[j], INT_MAX);
			if (result > 0)
			{
				swap_array(i, j, arr);
				continue ;
			}
			j++;
		}
		i++;
	}
}

//busca una v. de entorno por su nombre y devuelve una copia de su valor
char	*get_env_value(const char *name, t_env *env)
{
	t_env	*current;

	if (!name || !env)
		return (NULL);
	current = env;
	while (current)
	{
		if (ft_strcmp(current->name, name) == 0)
		{
			if (!current->value)
				return (NULL);
			return (ft_strdup(current->value));
		}
		current = current->next;
	}
	return (NULL);
}

// calcula el numero de nodos
size_t	length_env_list(t_env *env_list)
{
	t_env	*temp;
	size_t	i;

	i = 0;
	temp = env_list;
	while (temp)
	{
		i++;
		temp = temp->next;
	}
	return (i);
}
