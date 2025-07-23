/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_environment.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dirituay <dirituay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 11:19:36 by lellanos          #+#    #+#             */
/*   Updated: 2025/07/23 13:07:52 by dirituay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//libera toda la lista enlazada de env
void	free_env(t_env **env_list)
{
	t_env		*tmp;

	if (!env_list || !*env_list)
		return ;
	while (*env_list)
	{
		tmp = (*env_list)->next;
		free_env_node(*env_list);
		*env_list = tmp;
	}
	*env_list = NULL;
}
